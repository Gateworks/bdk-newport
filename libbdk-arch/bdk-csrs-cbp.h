#ifndef __BDK_CSRS_CBP_H__
#define __BDK_CSRS_CBP_H__
/* This file is auto-generated. Do not edit */

/***********************license start***********************************
* Copyright (C) 2019 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * OcteonTX CBP.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RSL32b) cbp#_ap_dtap
 *
 * CBP Ap Dtap Register
 */
union bdk_cbpx_ap_dtap
{
    uint32_t u;
    struct bdk_cbpx_ap_dtap_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ap                    : 3;  /**< [  2:  0](R/W) TCM Access Protection. */
#else /* Word 0 - Little Endian */
        uint32_t ap                    : 3;  /**< [  2:  0](R/W) TCM Access Protection. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ap_dtap_s cn; */
};
typedef union bdk_cbpx_ap_dtap bdk_cbpx_ap_dtap_t;

static inline uint64_t BDK_CBPX_AP_DTAP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_AP_DTAP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482324cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_AP_DTAP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_AP_DTAP(a) bdk_cbpx_ap_dtap_t
#define bustype_BDK_CBPX_AP_DTAP(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_AP_DTAP(a) "CBPX_AP_DTAP"
#define busnum_BDK_CBPX_AP_DTAP(a) (a)
#define arguments_BDK_CBPX_AP_DTAP(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ap_mapar
 *
 * CBP Ap Mapar Register
 */
union bdk_cbpx_ap_mapar
{
    uint32_t u;
    struct bdk_cbpx_ap_mapar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t mapa                  : 32; /**< [ 31:  0](RO) Memory Access Protection Address
                                                                 Written by hardware during a memory access protection violation. If an
                                                                 instruction access protection occurred, contains the instruction address that
                                                                 caused the violation. If a data access protection occurred, contains the data
                                                                 address that caused the violation. */
#else /* Word 0 - Little Endian */
        uint32_t mapa                  : 32; /**< [ 31:  0](RO) Memory Access Protection Address
                                                                 Written by hardware during a memory access protection violation. If an
                                                                 instruction access protection occurred, contains the instruction address that
                                                                 caused the violation. If a data access protection occurred, contains the data
                                                                 address that caused the violation. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ap_mapar_s cn; */
};
typedef union bdk_cbpx_ap_mapar bdk_cbpx_ap_mapar_t;

static inline uint64_t BDK_CBPX_AP_MAPAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_AP_MAPAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823244ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_AP_MAPAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_AP_MAPAR(a) bdk_cbpx_ap_mapar_t
#define bustype_BDK_CBPX_AP_MAPAR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_AP_MAPAR(a) "CBPX_AP_MAPAR"
#define busnum_BDK_CBPX_AP_MAPAR(a) (a)
#define arguments_BDK_CBPX_AP_MAPAR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ap_mapsr
 *
 * CBP Ap Mapsr Register
 */
union bdk_cbpx_ap_mapsr
{
    uint32_t u;
    struct bdk_cbpx_ap_mapsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t at                    : 2;  /**< [  7:  6](RO) Access Type
                                                                 01  Data Read
                                                                 10  Data Write
                                                                 11  Reserved
                                                                 If two data access protection violations occur simultaneously, the LS0 access
                                                                 violation is written to the MAPAR and MAPSR registers. */
        uint32_t ap                    : 3;  /**< [  5:  3](RO) Access Protection type when the violation occur . */
        uint32_t om                    : 2;  /**< [  2:  1](RO) Operation Mode
                                                                 00  Supervisor Mode
                                                                 01  User0 Mode
                                                                 10  Reserved
                                                                 11  User1 Mode */
        uint32_t mapv                  : 1;  /**< [  0:  0](R/W/H) Memory Access Protection Violation occurred, MAPAR and MAPSR registers valid
                                                                 0  Not valid (no protection violation)
                                                                 1  Valid (protection violation occurred)
                                                                 During an access protection violation, the MAPAR and MAPSR registers are written
                                                                 by hardware with the address and status of the violation. These registers cannot
                                                                 be written by hardware unless the valid bit is cleared, and therefore, software
                                                                 is responsible for clearing this bit after a protection violation occurs. */
#else /* Word 0 - Little Endian */
        uint32_t mapv                  : 1;  /**< [  0:  0](R/W/H) Memory Access Protection Violation occurred, MAPAR and MAPSR registers valid
                                                                 0  Not valid (no protection violation)
                                                                 1  Valid (protection violation occurred)
                                                                 During an access protection violation, the MAPAR and MAPSR registers are written
                                                                 by hardware with the address and status of the violation. These registers cannot
                                                                 be written by hardware unless the valid bit is cleared, and therefore, software
                                                                 is responsible for clearing this bit after a protection violation occurs. */
        uint32_t om                    : 2;  /**< [  2:  1](RO) Operation Mode
                                                                 00  Supervisor Mode
                                                                 01  User0 Mode
                                                                 10  Reserved
                                                                 11  User1 Mode */
        uint32_t ap                    : 3;  /**< [  5:  3](RO) Access Protection type when the violation occur . */
        uint32_t at                    : 2;  /**< [  7:  6](RO) Access Type
                                                                 01  Data Read
                                                                 10  Data Write
                                                                 11  Reserved
                                                                 If two data access protection violations occur simultaneously, the LS0 access
                                                                 violation is written to the MAPAR and MAPSR registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ap_mapsr_s cn; */
};
typedef union bdk_cbpx_ap_mapsr bdk_cbpx_ap_mapsr_t;

static inline uint64_t BDK_CBPX_AP_MAPSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_AP_MAPSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823248ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_AP_MAPSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_AP_MAPSR(a) bdk_cbpx_ap_mapsr_t
#define bustype_BDK_CBPX_AP_MAPSR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_AP_MAPSR(a) "CBPX_AP_MAPSR"
#define busnum_BDK_CBPX_AP_MAPSR(a) (a)
#define arguments_BDK_CBPX_AP_MAPSR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b#_full_empty_ctl_reg
 *
 * CBP Buffermanager B Full Empty Ctl Reg Register
 */
union bdk_cbpx_buffermanager_bx_full_empty_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_bx_full_empty_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t bx_empty_wptr_sel     : 1;  /**< [ 29: 29](R/W) Selects the use of actual or expected write pointer for the production of the
                                                                 bmanX_empty and bmanX_aempty signals
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t bx_empty_rptr_sel     : 1;  /**< [ 28: 28](R/W) Selects the use of actual or expected read pointer for the production of the
                                                                 bmanx_empty and bmanX_aempty signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_26_27        : 2;
        uint32_t bx_empty_thld         : 10; /**< [ 25: 16](R/W) Almost empty threshold
                                                                 The bmanX_aempty signal is set when the number of bytes in the buffer is below this threshold
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_14_15        : 2;
        uint32_t bx_full_wptr_sel      : 1;  /**< [ 13: 13](R/W) Selects the use of actual or expected write pointer for the production of the bmanX_afull signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t bx_full_rptr_sel      : 1;  /**< [ 12: 12](R/W) Selects the use of actual or expected read pointer for the production of the bmanX_afull signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_full_thld          : 10; /**< [  9:  0](R/W) Almost full threshold
                                                                 The bmanX_afull full signal is set when the number of available bytes in the
                                                                 buffer is below this threshold
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_full_thld          : 10; /**< [  9:  0](R/W) Almost full threshold
                                                                 The bmanX_afull full signal is set when the number of available bytes in the
                                                                 buffer is below this threshold
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_full_rptr_sel      : 1;  /**< [ 12: 12](R/W) Selects the use of actual or expected read pointer for the production of the bmanX_afull signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t bx_full_wptr_sel      : 1;  /**< [ 13: 13](R/W) Selects the use of actual or expected write pointer for the production of the bmanX_afull signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_14_15        : 2;
        uint32_t bx_empty_thld         : 10; /**< [ 25: 16](R/W) Almost empty threshold
                                                                 The bmanX_aempty signal is set when the number of bytes in the buffer is below this threshold
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_26_27        : 2;
        uint32_t bx_empty_rptr_sel     : 1;  /**< [ 28: 28](R/W) Selects the use of actual or expected read pointer for the production of the
                                                                 bmanx_empty and bmanX_aempty signal
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t bx_empty_wptr_sel     : 1;  /**< [ 29: 29](R/W) Selects the use of actual or expected write pointer for the production of the
                                                                 bmanX_empty and bmanX_aempty signals
                                                                 Actual pointer
                                                                 Expected pointer
                                                                 Changing the value of this field is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_bx_full_empty_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_bx_full_empty_ctl_reg bdk_cbpx_buffermanager_bx_full_empty_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822c10ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(a,b) bdk_cbpx_buffermanager_bx_full_empty_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(a,b) "CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(a,b) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_BX_FULL_EMPTY_CTL_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b#_rptr_reg
 *
 * CBP Buffermanager B Rptr Reg Register
 */
union bdk_cbpx_buffermanager_bx_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_bx_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_afull              : 1;  /**< [ 31: 31](RO/H) Buffer almost full.
                                                                 Reflects the status of the bX_afull output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_rptr               : 18; /**< [ 17:  0](R/W/H) Read pointer for buffer X
                                                                 This register points to the next valid byte in the buffer.
                                                                 This register gets the value of 0 after BX_RST is set.
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_rptr               : 18; /**< [ 17:  0](R/W/H) Read pointer for buffer X
                                                                 This register points to the next valid byte in the buffer.
                                                                 This register gets the value of 0 after BX_RST is set.
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_afull              : 1;  /**< [ 31: 31](RO/H) Buffer almost full.
                                                                 Reflects the status of the bX_afull output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_bx_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_bx_rptr_reg bdk_cbpx_buffermanager_bx_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822c1cll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_BX_RPTR_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(a,b) bdk_cbpx_buffermanager_bx_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(a,b) "CBPX_BUFFERMANAGER_BX_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(a,b) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_BX_RPTR_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b#_size_reg
 *
 * CBP Buffermanager B Size Reg Register
 */
union bdk_cbpx_buffermanager_bx_size_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_bx_size_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_size               : 18; /**< [ 17:  0](R/W) Size of buffer X in bytes
                                                                 A buffer must not cross the IDM block boundary.
                                                                 Defining a buffer that starts at one block and ends at the other will result
                                                                 with the actual pointers out of sync.
                                                                 The six LSBs of this register are always replaced with 6h0 (buffer size is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_size               : 18; /**< [ 17:  0](R/W) Size of buffer X in bytes
                                                                 A buffer must not cross the IDM block boundary.
                                                                 Defining a buffer that starts at one block and ends at the other will result
                                                                 with the actual pointers out of sync.
                                                                 The six LSBs of this register are always replaced with 6h0 (buffer size is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_bx_size_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_bx_size_reg bdk_cbpx_buffermanager_bx_size_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822c04ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_BX_SIZE_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(a,b) bdk_cbpx_buffermanager_bx_size_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(a,b) "CBPX_BUFFERMANAGER_BX_SIZE_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(a,b) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_BX_SIZE_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b#_snifer_out_acc_reg
 *
 * CBP Buffermanager B Snifer Out Acc Reg Register
 */
union bdk_cbpx_buffermanager_bx_snifer_out_acc_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_bx_snifer_out_acc_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t bx_snifer_out_acc     : 10; /**< [  9:  0](RO) Sniffer accumulator */
#else /* Word 0 - Little Endian */
        uint32_t bx_snifer_out_acc     : 10; /**< [  9:  0](RO) Sniffer accumulator */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_bx_snifer_out_acc_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_bx_snifer_out_acc_reg bdk_cbpx_buffermanager_bx_snifer_out_acc_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822c28ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(a,b) bdk_cbpx_buffermanager_bx_snifer_out_acc_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(a,b) "CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(a,b) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_BX_SNIFER_OUT_ACC_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_e0pctd_rptr_reg
 *
 * CBP Buffermanager B0 E0pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c24ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b0_e0pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_e0pctd_wptr_reg
 *
 * CBP Buffermanager B0 E0pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c20ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b0_e0pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_E0PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_e0t_inc_dir_reg
 *
 * CBP Buffermanager B0 E0t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c0cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b0_e0t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_E0T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B0 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c08ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b0_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_start_addr_reg
 *
 * CBP Buffermanager B0 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b0_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_start_addr_reg bdk_cbpx_buffermanager_b0_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c00ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(a) bdk_cbpx_buffermanager_b0_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B0_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b0_wptr_reg
 *
 * CBP Buffermanager B0 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b0_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b0_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W/H) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W/H) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b0_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b0_wptr_reg bdk_cbpx_buffermanager_b0_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c18ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B0_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(a) bdk_cbpx_buffermanager_b0_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(a) "CBPX_BUFFERMANAGER_B0_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B0_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_e1pctd_rptr_reg
 *
 * CBP Buffermanager B1 E1pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c64ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b1_e1pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_e1pctd_wptr_reg
 *
 * CBP Buffermanager B1 E1pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c60ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b1_e1pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_E1PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_e1t_inc_dir_reg
 *
 * CBP Buffermanager B1 E1t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c4cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b1_e1t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_E1T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B1 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c48ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b1_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_start_addr_reg
 *
 * CBP Buffermanager B1 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b1_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_start_addr_reg bdk_cbpx_buffermanager_b1_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c40ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(a) bdk_cbpx_buffermanager_b1_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B1_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b1_wptr_reg
 *
 * CBP Buffermanager B1 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b1_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b1_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b1_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b1_wptr_reg bdk_cbpx_buffermanager_b1_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c58ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B1_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(a) bdk_cbpx_buffermanager_b1_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(a) "CBPX_BUFFERMANAGER_B1_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B1_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_e2pctd_rptr_reg
 *
 * CBP Buffermanager B2 E2pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822ca4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b2_e2pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_e2pctd_wptr_reg
 *
 * CBP Buffermanager B2 E2pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822ca0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b2_e2pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_E2PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_e2t_inc_dir_reg
 *
 * CBP Buffermanager B2 E2t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c8cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b2_e2t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_E2T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B2 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c88ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b2_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_start_addr_reg
 *
 * CBP Buffermanager B2 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b2_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_start_addr_reg bdk_cbpx_buffermanager_b2_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c80ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(a) bdk_cbpx_buffermanager_b2_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B2_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b2_wptr_reg
 *
 * CBP Buffermanager B2 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b2_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b2_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b2_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b2_wptr_reg bdk_cbpx_buffermanager_b2_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822c98ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B2_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(a) bdk_cbpx_buffermanager_b2_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(a) "CBPX_BUFFERMANAGER_B2_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B2_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_e3pctd_rptr_reg
 *
 * CBP Buffermanager B3 E3pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822ce4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b3_e3pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_e3pctd_wptr_reg
 *
 * CBP Buffermanager B3 E3pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822ce0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b3_e3pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_E3PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_e3t_inc_dir_reg
 *
 * CBP Buffermanager B3 E3t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822cccll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b3_e3t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_E3T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B3 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822cc8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b3_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_start_addr_reg
 *
 * CBP Buffermanager B3 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b3_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_start_addr_reg bdk_cbpx_buffermanager_b3_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822cc0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(a) bdk_cbpx_buffermanager_b3_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B3_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b3_wptr_reg
 *
 * CBP Buffermanager B3 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b3_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b3_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b3_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b3_wptr_reg bdk_cbpx_buffermanager_b3_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822cd8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B3_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(a) bdk_cbpx_buffermanager_b3_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(a) "CBPX_BUFFERMANAGER_B3_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B3_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_e4pctd_rptr_reg
 *
 * CBP Buffermanager B4 E4pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d24ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b4_e4pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_e4pctd_wptr_reg
 *
 * CBP Buffermanager B4 E4pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d20ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b4_e4pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_E4PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_e4t_inc_dir_reg
 *
 * CBP Buffermanager B4 E4t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d0cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b4_e4t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_E4T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B4 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d08ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b4_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_start_addr_reg
 *
 * CBP Buffermanager B4 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b4_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always 6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_start_addr_reg bdk_cbpx_buffermanager_b4_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d00ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(a) bdk_cbpx_buffermanager_b4_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B4_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b4_wptr_reg
 *
 * CBP Buffermanager B4 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b4_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b4_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b4_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b4_wptr_reg bdk_cbpx_buffermanager_b4_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d18ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B4_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(a) bdk_cbpx_buffermanager_b4_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(a) "CBPX_BUFFERMANAGER_B4_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B4_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_e5pctd_rptr_reg
 *
 * CBP Buffermanager B5 E5pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d64ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b5_e5pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_e5pctd_wptr_reg
 *
 * CBP Buffermanager B5 E5pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d60ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b5_e5pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_E5PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_e5t_inc_dir_reg
 *
 * CBP Buffermanager B5 E5t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d4cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b5_e5t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_E5T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B5 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d48ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b5_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_start_addr_reg
 *
 * CBP Buffermanager B5 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b5_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_start_addr_reg bdk_cbpx_buffermanager_b5_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d40ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(a) bdk_cbpx_buffermanager_b5_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B5_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b5_wptr_reg
 *
 * CBP Buffermanager B5 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b5_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b5_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b5_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b5_wptr_reg bdk_cbpx_buffermanager_b5_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d58ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B5_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(a) bdk_cbpx_buffermanager_b5_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(a) "CBPX_BUFFERMANAGER_B5_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B5_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_e6pctd_rptr_reg
 *
 * CBP Buffermanager B6 E6pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822da4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b6_e6pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_e6pctd_wptr_reg
 *
 * CBP Buffermanager B6 E6pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822da0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b6_e6pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_E6PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_e6t_inc_dir_reg
 *
 * CBP Buffermanager B6 E6t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d8cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b6_e6t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_E6T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B6 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d88ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b6_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_start_addr_reg
 *
 * CBP Buffermanager B6 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b6_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_start_addr_reg bdk_cbpx_buffermanager_b6_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d80ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(a) bdk_cbpx_buffermanager_b6_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B6_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b6_wptr_reg
 *
 * CBP Buffermanager B6 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b6_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b6_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b6_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b6_wptr_reg bdk_cbpx_buffermanager_b6_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822d98ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B6_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(a) bdk_cbpx_buffermanager_b6_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(a) "CBPX_BUFFERMANAGER_B6_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B6_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_e7pctd_rptr_reg
 *
 * CBP Buffermanager B7 E7pctd Rptr Reg Register
 */
union bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_rptr        : 18; /**< [ 17:  0](R/W/H) Expected read pointer for buffer X
                                                                 This register reflects the status of the BMANN_RPTR register after all DMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant write pointer (actual
                                                                 or expected) indicates buffer is empty.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822de4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(a) bdk_cbpx_buffermanager_b7_e7pctd_rptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(a) "CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_RPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_e7pctd_wptr_reg
 *
 * CBP Buffermanager B7 E7pctd Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t bx_expctd_wptr        : 18; /**< [ 17:  0](R/W/H) Expected write pointer for buffer X
                                                                 This register reflects the status of the BMANN_WPTR register after all DDMA
                                                                 outstanding transactions complete.
                                                                 Updating this pointer with a value equal to the relevant read pointer (actual or
                                                                 expected) indicates buffer is full.
                                                                 This register gets the value of 0 after BX_RST is set. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822de0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(a) bdk_cbpx_buffermanager_b7_e7pctd_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(a) "CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_E7PCTD_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_e7t_inc_dir_reg
 *
 * CBP Buffermanager B7 E7t Inc Dir Reg Register
 */
union bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#else /* Word 0 - Little Endian */
        uint32_t bx_ext_inc_dir        : 1;  /**< [  0:  0](R/W) Direction of the external sniffer.
                                                                 This register indicates the direction of pointer increment input signal (bmanX_ext_ptr_inc).
                                                                 0-bmanX_ext_ptr_inc is used to increment the write pointer
                                                                 1-bmanX_ext_ptr_inc is used to increment the read pointer
                                                                 This register also indicates the direction of the IDM sniffer output signal
                                                                 (bmanX_sniffer_ext_inc).
                                                                 0-bmanX_sniffer_ext_inc is used to indicate buffer writes ware detected
                                                                 1-bmanX_sniffer_ext_inc is used to indicate that buffer reads were detected
                                                                 A buffer located at the IDM is not expected to use the bmanX_ext_ptr_inc signal.
                                                                 A buffer located at external memory is not expected to use the bmanX_sniffer_ext_inc signal.
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822dccll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(a) bdk_cbpx_buffermanager_b7_e7t_inc_dir_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(a) "CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_E7T_INC_DIR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_inc_ptr_ctl_reg
 *
 * CBP Buffermanager B7 Inc Ptr Ctl Reg Register
 */
union bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
#else /* Word 0 - Little Endian */
        uint32_t bx_ptr_inc_val        : 10; /**< [  9:  0](R/W) Increment value of the read/write pointer when external increment signal is set
                                                                 or when BX_PTR_INC is written with 1
                                                                 This register is also user for setting the number of bytes read/write from/to
                                                                 the buffer before setting the bmanX_sniffer_ext_inc output signal
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_10_11        : 2;
        uint32_t bx_ptr_inc            : 1;  /**< [ 12: 12](WO) Increment request to read/write expected pointer of buffer X
                                                                 The functionality of this bit is defined by the BX_PTR_INC_DIR configuration register.
                                                                 Writing the value of 1 to this field is restricted when bmanX_sniffer_ext_inc is
                                                                 used by external device or when bmanX_ext_ptr_inc is connected to a sniffer at
                                                                 external memory */
        uint32_t bx_ptr_inc_dir        : 1;  /**< [ 13: 13](R/W) Select functionality of BX_PTR_INC
                                                                 0  BX_PTR_INC is used for incrementing expected write pointer
                                                                 1  BX_PTR_INC is used for incrementing expected read pointer
                                                                 Changing the value of this field is restricted when BMAN is active and
                                                                 bmanX_sniffer_ext_inc is used by external device or bmanX_ext_ptr_inc is
                                                                 connected to a sniffer at external memory */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822dc8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(a) bdk_cbpx_buffermanager_b7_inc_ptr_ctl_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(a) "CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_INC_PTR_CTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_start_addr_reg
 *
 * CBP Buffermanager B7 Start Addr Reg Register
 */
union bdk_cbpx_buffermanager_b7_start_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_start_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
        uint32_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_5          : 6;
        uint32_t bx_start_addr         : 26; /**< [ 31:  6](R/W) Start address of buffer X
                                                                 The six LSBs of this register are always  6h0 (buffer is 64 bytes aligned)
                                                                 Writing to this register is restricted when BMAN is active  (see BMAN_RST_REG ) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_start_addr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_start_addr_reg bdk_cbpx_buffermanager_b7_start_addr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822dc0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_START_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(a) bdk_cbpx_buffermanager_b7_start_addr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(a) "CBPX_BUFFERMANAGER_B7_START_ADDR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_START_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_buffermanager_b7_wptr_reg
 *
 * CBP Buffermanager B7 Wptr Reg Register
 */
union bdk_cbpx_buffermanager_b7_wptr_reg
{
    uint32_t u;
    struct bdk_cbpx_buffermanager_b7_wptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
#else /* Word 0 - Little Endian */
        uint32_t bx_wptr               : 18; /**< [ 17:  0](R/W) Write pointer for buffer X
                                                                 This register gets the value of 0 after BX_RST is set
                                                                 Writing to this register is prohibited and is reserved for future use. */
        uint32_t reserved_18_30        : 13;
        uint32_t bx_aempty             : 1;  /**< [ 31: 31](RO/H) Buffer almost empty.
                                                                 Reflects the status of the bX_aempty output signal. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_buffermanager_b7_wptr_reg_s cn; */
};
typedef union bdk_cbpx_buffermanager_b7_wptr_reg bdk_cbpx_buffermanager_b7_wptr_reg_t;

static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822dd8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_BUFFERMANAGER_B7_WPTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(a) bdk_cbpx_buffermanager_b7_wptr_reg_t
#define bustype_BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(a) "CBPX_BUFFERMANAGER_B7_WPTR_REG"
#define busnum_BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(a) (a)
#define arguments_BDK_CBPX_BUFFERMANAGER_B7_WPTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_coreextid_core_id
 *
 * CBP Coreextid Core Id Register
 */
union bdk_cbpx_coreextid_core_id
{
    uint32_t u;
    struct bdk_cbpx_coreextid_core_id_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t core_id               : 32; /**< [ 31:  0](RO/H) The value of this register is sampled at reset from the core_id input bus.
                                                                 This register is read only.
                                                                 For EDAP or FICSR ports the CORE_ID register can be  accessed using address 0x40_1004 . */
#else /* Word 0 - Little Endian */
        uint32_t core_id               : 32; /**< [ 31:  0](RO/H) The value of this register is sampled at reset from the core_id input bus.
                                                                 This register is read only.
                                                                 For EDAP or FICSR ports the CORE_ID register can be  accessed using address 0x40_1004 . */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_coreextid_core_id_s cn; */
};
typedef union bdk_cbpx_coreextid_core_id bdk_cbpx_coreextid_core_id_t;

static inline uint64_t BDK_CBPX_COREEXTID_CORE_ID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_COREEXTID_CORE_ID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044821004ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_COREEXTID_CORE_ID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_COREEXTID_CORE_ID(a) bdk_cbpx_coreextid_core_id_t
#define bustype_BDK_CBPX_COREEXTID_CORE_ID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_COREEXTID_CORE_ID(a) "CBPX_COREEXTID_CORE_ID"
#define busnum_BDK_CBPX_COREEXTID_CORE_ID(a) (a)
#define arguments_BDK_CBPX_COREEXTID_CORE_ID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_coreextid_core_version
 *
 * CBP Coreextid Core Version Register
 */
union bdk_cbpx_coreextid_core_version
{
    uint32_t u;
    struct bdk_cbpx_coreextid_core_version_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t core_version          : 32; /**< [ 31:  0](RO) Bits [31:16]: DSP core type
                                                                 Reset value: Core Version. */
#else /* Word 0 - Little Endian */
        uint32_t core_version          : 32; /**< [ 31:  0](RO) Bits [31:16]: DSP core type
                                                                 Reset value: Core Version. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_coreextid_core_version_s cn; */
};
typedef union bdk_cbpx_coreextid_core_version bdk_cbpx_coreextid_core_version_t;

static inline uint64_t BDK_CBPX_COREEXTID_CORE_VERSION(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_COREEXTID_CORE_VERSION(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044821000ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_COREEXTID_CORE_VERSION", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_COREEXTID_CORE_VERSION(a) bdk_cbpx_coreextid_core_version_t
#define bustype_BDK_CBPX_COREEXTID_CORE_VERSION(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_COREEXTID_CORE_VERSION(a) "CBPX_COREEXTID_CORE_VERSION"
#define busnum_BDK_CBPX_COREEXTID_CORE_VERSION(a) (a)
#define arguments_BDK_CBPX_COREEXTID_CORE_VERSION(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_ddam
 *
 * CBP Dma Dbg Ddam Register
 * * If the DDMA is configured to use bursts for the external AXI, only the start address of the burst is matched.
 */
union bdk_cbpx_dma_dbg_ddam
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_ddam_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dmadam                : 32; /**< [ 31:  0](R/W) DMA data address match.*
                                                                 Sets the address value for the address match breakpoint.
                                                                 A breakpoint is generated by the DMA when a transfer occurs to/from an address
                                                                 with the DMADAM value. */
#else /* Word 0 - Little Endian */
        uint32_t dmadam                : 32; /**< [ 31:  0](R/W) DMA data address match.*
                                                                 Sets the address value for the address match breakpoint.
                                                                 A breakpoint is generated by the DMA when a transfer occurs to/from an address
                                                                 with the DMADAM value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_ddam_s cn; */
};
typedef union bdk_cbpx_dma_dbg_ddam bdk_cbpx_dma_dbg_ddam_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DDAM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DDAM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822204ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DDAM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DDAM(a) bdk_cbpx_dma_dbg_ddam_t
#define bustype_BDK_CBPX_DMA_DBG_DDAM(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DDAM(a) "CBPX_DMA_DBG_DDAM"
#define busnum_BDK_CBPX_DMA_DBG_DDAM(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DDAM(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_ddc
 *
 * CBP Dma Dbg Ddc Register
 * Notes:
 * 1.	If both the DMADAMDE and DMADAMUE bits are set to 0, the DMA address match is disabled.
 * 2.	It is restricted to write 2b11 to the DAS field.
 */
union bdk_cbpx_dma_dbg_ddc
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_ddc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t das                   : 2;  /**< [  7:  6](R/W) DMA internal/external address select.
                                                                 Selects whether the data address match is performed on an internal memory
                                                                 address or an external memory address:
                                                                 00: DMA address match is disabled.
                                                                 01: Internal addresses.
                                                                 10: External addresses.
                                                                 11: Reserved . */
        uint32_t dmadamue              : 1;  /**< [  5:  5](R/W) DMA data address match upload enable.
                                                                 Enables the data address match breakpoint mechanism in upload transactions :
                                                                 0: Disabled.
                                                                 1: Enabled. */
        uint32_t dmadamde              : 1;  /**< [  4:  4](R/W) DMA data address match download enable.
                                                                 Enables the data address match breakpoint mechanism in download transactions :
                                                                 0: Disabled.
                                                                 1: Enabled. */
        uint32_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_3          : 4;
        uint32_t dmadamde              : 1;  /**< [  4:  4](R/W) DMA data address match download enable.
                                                                 Enables the data address match breakpoint mechanism in download transactions :
                                                                 0: Disabled.
                                                                 1: Enabled. */
        uint32_t dmadamue              : 1;  /**< [  5:  5](R/W) DMA data address match upload enable.
                                                                 Enables the data address match breakpoint mechanism in upload transactions :
                                                                 0: Disabled.
                                                                 1: Enabled. */
        uint32_t das                   : 2;  /**< [  7:  6](R/W) DMA internal/external address select.
                                                                 Selects whether the data address match is performed on an internal memory
                                                                 address or an external memory address:
                                                                 00: DMA address match is disabled.
                                                                 01: Internal addresses.
                                                                 10: External addresses.
                                                                 11: Reserved . */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_ddc_s cn; */
};
typedef union bdk_cbpx_dma_dbg_ddc bdk_cbpx_dma_dbg_ddc_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DDC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DDC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482220cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DDC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DDC(a) bdk_cbpx_dma_dbg_ddc_t
#define bustype_BDK_CBPX_DMA_DBG_DDC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DDC(a) "CBPX_DMA_DBG_DDC"
#define busnum_BDK_CBPX_DMA_DBG_DDC(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DDC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_dds
 *
 * CBP Dma Dbg Dds Register
 * Notes:
 * 1.      A dedicated indication is issued to the OCEM indicating the occurrence of a
 * data address match (upload or download). This indication is also observed off-core
 * via a dedicated port.
 */
union bdk_cbpx_dma_dbg_dds
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_dds_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t dam                   : 2;  /**< [  5:  4](R/W/H) DMA internal/external address match.
                                                                 Indicates whether a data address match occurred on an internal memory address,
                                                                 external memory address or none. Writing 00 to these bits clears them:
                                                                 00: No address match occurred
                                                                 01: Internal address
                                                                 10: External address
                                                                 11: Reserved */
        uint32_t dmaddam               : 1;  /**< [  3:  3](R/W/H) DMA data upload address match.
                                                                 When set, indicates a DMA data upload address match occurrence. Writing 0 to this bit clears it. */
        uint32_t dmaduam               : 1;  /**< [  2:  2](R/W/H) DMA data upload address match.
                                                                 When set, indicates a DMA data upload address match occurrence. Writing 0 to this bit clears it. */
        uint32_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_1          : 2;
        uint32_t dmaduam               : 1;  /**< [  2:  2](R/W/H) DMA data upload address match.
                                                                 When set, indicates a DMA data upload address match occurrence. Writing 0 to this bit clears it. */
        uint32_t dmaddam               : 1;  /**< [  3:  3](R/W/H) DMA data upload address match.
                                                                 When set, indicates a DMA data upload address match occurrence. Writing 0 to this bit clears it. */
        uint32_t dam                   : 2;  /**< [  5:  4](R/W/H) DMA internal/external address match.
                                                                 Indicates whether a data address match occurred on an internal memory address,
                                                                 external memory address or none. Writing 00 to these bits clears them:
                                                                 00: No address match occurred
                                                                 01: Internal address
                                                                 10: External address
                                                                 11: Reserved */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_dds_s cn; */
};
typedef union bdk_cbpx_dma_dbg_dds bdk_cbpx_dma_dbg_dds_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DDS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DDS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822210ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DDS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DDS(a) bdk_cbpx_dma_dbg_dds_t
#define bustype_BDK_CBPX_DMA_DBG_DDS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DDS(a) "CBPX_DMA_DBG_DDS"
#define busnum_BDK_CBPX_DMA_DBG_DDS(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DDS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_dunmpd0
 *
 * CBP Dma Dbg Dunmpd0 Register
 */
union bdk_cbpx_dma_dbg_dunmpd0
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_dunmpd0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dexcptn_unmapd        : 32; /**< [ 31:  0](RO) Set of each bit indicates that the corresponding region in data address space is
                                                                 un-mapped and has been accessed by the core.
                                                                 Regions 1-32 */
#else /* Word 0 - Little Endian */
        uint32_t dexcptn_unmapd        : 32; /**< [ 31:  0](RO) Set of each bit indicates that the corresponding region in data address space is
                                                                 un-mapped and has been accessed by the core.
                                                                 Regions 1-32 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_dunmpd0_s cn; */
};
typedef union bdk_cbpx_dma_dbg_dunmpd0 bdk_cbpx_dma_dbg_dunmpd0_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482222cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DUNMPD0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DUNMPD0(a) bdk_cbpx_dma_dbg_dunmpd0_t
#define bustype_BDK_CBPX_DMA_DBG_DUNMPD0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DUNMPD0(a) "CBPX_DMA_DBG_DUNMPD0"
#define busnum_BDK_CBPX_DMA_DBG_DUNMPD0(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DUNMPD0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_dunmpd1
 *
 * CBP Dma Dbg Dunmpd1 Register
 */
union bdk_cbpx_dma_dbg_dunmpd1
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_dunmpd1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dexcptn_unmapd        : 32; /**< [ 31:  0](RO) Set of each bit indicates that the corresponding region in data address space is
                                                                 un-mapped and has been accessed by the core.
                                                                 This register corresponds to regions 33-64. When only 32 regions are configured
                                                                 at hardware installation this register is not implemented. */
#else /* Word 0 - Little Endian */
        uint32_t dexcptn_unmapd        : 32; /**< [ 31:  0](RO) Set of each bit indicates that the corresponding region in data address space is
                                                                 un-mapped and has been accessed by the core.
                                                                 This register corresponds to regions 33-64. When only 32 regions are configured
                                                                 at hardware installation this register is not implemented. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_dunmpd1_s cn; */
};
typedef union bdk_cbpx_dma_dbg_dunmpd1 bdk_cbpx_dma_dbg_dunmpd1_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822230ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DUNMPD1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DUNMPD1(a) bdk_cbpx_dma_dbg_dunmpd1_t
#define bustype_BDK_CBPX_DMA_DBG_DUNMPD1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DUNMPD1(a) "CBPX_DMA_DBG_DUNMPD1"
#define busnum_BDK_CBPX_DMA_DBG_DUNMPD1(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DUNMPD1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_dunmpd_msk0
 *
 * CBP Dma Dbg Dunmpd Msk0 Register
 */
union bdk_cbpx_dma_dbg_dunmpd_msk0
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_dunmpd_msk0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dexcptn_unmapd_mask   : 32; /**< [ 31:  0](R/W) Set of each bit indicates that the corresponding region un-mapped indication is
                                                                 masked and will not cause an un-mapped exception indication in GVI register.
                                                                 Regions 1-32 */
#else /* Word 0 - Little Endian */
        uint32_t dexcptn_unmapd_mask   : 32; /**< [ 31:  0](R/W) Set of each bit indicates that the corresponding region un-mapped indication is
                                                                 masked and will not cause an un-mapped exception indication in GVI register.
                                                                 Regions 1-32 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_dunmpd_msk0_s cn; */
};
typedef union bdk_cbpx_dma_dbg_dunmpd_msk0 bdk_cbpx_dma_dbg_dunmpd_msk0_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD_MSK0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD_MSK0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822234ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DUNMPD_MSK0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DUNMPD_MSK0(a) bdk_cbpx_dma_dbg_dunmpd_msk0_t
#define bustype_BDK_CBPX_DMA_DBG_DUNMPD_MSK0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DUNMPD_MSK0(a) "CBPX_DMA_DBG_DUNMPD_MSK0"
#define busnum_BDK_CBPX_DMA_DBG_DUNMPD_MSK0(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DUNMPD_MSK0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_dunmpd_msk1
 *
 * CBP Dma Dbg Dunmpd Msk1 Register
 */
union bdk_cbpx_dma_dbg_dunmpd_msk1
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_dunmpd_msk1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dexcptn_unmapd_mask   : 32; /**< [ 31:  0](R/W) Set of each bit indicates that the corresponding region un-mapped indication is
                                                                 masked and will not cause an un-mapped exception indication in GVI register.
                                                                 This register corresponds to regions 33-64. When only 32 regions are configured
                                                                 at hardware installation this register is not implemented. */
#else /* Word 0 - Little Endian */
        uint32_t dexcptn_unmapd_mask   : 32; /**< [ 31:  0](R/W) Set of each bit indicates that the corresponding region un-mapped indication is
                                                                 masked and will not cause an un-mapped exception indication in GVI register.
                                                                 This register corresponds to regions 33-64. When only 32 regions are configured
                                                                 at hardware installation this register is not implemented. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_dunmpd_msk1_s cn; */
};
typedef union bdk_cbpx_dma_dbg_dunmpd_msk1 bdk_cbpx_dma_dbg_dunmpd_msk1_t;

static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD_MSK1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_DUNMPD_MSK1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822238ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_DUNMPD_MSK1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_DUNMPD_MSK1(a) bdk_cbpx_dma_dbg_dunmpd_msk1_t
#define bustype_BDK_CBPX_DMA_DBG_DUNMPD_MSK1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_DUNMPD_MSK1(a) "CBPX_DMA_DBG_DUNMPD_MSK1"
#define busnum_BDK_CBPX_DMA_DBG_DUNMPD_MSK1(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_DUNMPD_MSK1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_gen
 *
 * CBP Dma Dbg Gen Register
 * Note: when the user clear a bit in the GVI register and a new one is set in the same
 * cycle this bit will remain set
 */
union bdk_cbpx_dma_dbg_gen
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_gen_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t vcu_c                 : 1;  /**< [ 31: 31](R/W/H) This bit is set when the VCU attempt to access cacheable region.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t reserved_30           : 1;
        uint32_t bkrep_excptn          : 1;  /**< [ 29: 29](R/W/H) This bit is set when there is use of more than four nesting levels in BKREP.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ovrflw_excptn         : 1;  /**< [ 28: 28](R/W/H) This bit is set when there is calculation overflow in one of the MACs.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t stack_viol_excptn     : 1;  /**< [ 27: 27](R/W/H) This bit is set when there is stack violation detection when the stack address
                                                                 fall outside the pre-configured start and end addresses.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t unmapped_excptn       : 1;  /**< [ 26: 26](R/W/H) This bit is set when one of the DBG_xUNMPD0/1 registers is asserted and its
                                                                 corresponding mask bit is cleared in DBG_UNMPD_MASK0/1; this indicates that an
                                                                 un-mapped violation occurred in one of the configured regions in IACU or DACU.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_bman_pktsize       : 1;  /**< [ 25: 25](R/W/H) Error indication BMAN packet size is zero while access to the buffer in use continues.
                                                                 This bit is set when the BMAN_IRQ_SEL field is configured to interrupt when DSP
                                                                 reads from an almost empty buffer and the number of bytes being read from the
                                                                 buffer exceeds the configured packet size ().
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t qman_idm_cros         : 1;  /**< [ 24: 24](R/W/H) Error indication QMAN internal access crossed IDM last address.
                                                                 This bit is set when one of the bits at the QMAN_IDM_CROS register is set.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_align_err          : 1;  /**< [ 23: 23](R/W) Error indication Write Buffer access with full bandwidth and address not aligned to DW.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_idm_cros           : 1;  /**< [ 22: 22](R/W/H) Error indication Write Buffer internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t lsu_idm_cros          : 1;  /**< [ 21: 21](R/W/H) Error indication LSU internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ddma_idm_cros         : 1;  /**< [ 20: 20](R/W/H) Error indication DDMA internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_rg_cros            : 1;  /**< [ 19: 19](R/W/H) Error indication Write Buffer external access crossed external data access port
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t lsu_rg_cros           : 1;  /**< [ 18: 18](R/W/H) Error indication LSU external access crossed external data access port.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ddma_rg_cros          : 1;  /**< [ 17: 17](R/W/H) Error indication DDMA external access crossed external data access port.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_rows_oor           : 1;  /**< [ 16: 16](R/W/H) Error indication access to external port using row stride.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics7_oor             : 1;  /**< [ 15: 15](R/W/H) Error indication FICS7 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics6_oor             : 1;  /**< [ 14: 14](R/W/H) Error indication FICS6 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics5_oor             : 1;  /**< [ 13: 13](R/W/H) Error indication FICS5 read/ write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics4_oor             : 1;  /**< [ 12: 12](R/W/H) Error indication FICS4 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics3_oor             : 1;  /**< [ 11: 11](R/W/H) Error indication FICS3 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics2_oor             : 1;  /**< [ 10: 10](R/W/H) Error indication FICS2 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics1_oor             : 1;  /**< [  9:  9](R/W/H) Error indication FICS1read/ write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics0_oor             : 1;  /**< [  8:  8](R/W/H) Error indication FICS0 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t edap_w_oor            : 1;  /**< [  7:  7](R/W/H) Error indication EDAP write to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t edap_r_oor            : 1;  /**< [  6:  6](R/W/H) Error indication EDAP read from an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_exok               : 1;  /**< [  5:  5](R/W/H) Error indication slave not support exclusive accesses.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_wrc                : 1;  /**< [  4:  4](R/W/H) Error indication is received when WRC reaches 0x3FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_edp                : 1;  /**< [  3:  3](R/W/H) Error indication is received from EDP access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_epp                : 1;  /**< [  2:  2](R/W/H) Error indication is received from EPP access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_iop                : 1;  /**< [  1:  1](R/W/H) Error indication is received from I/O APB access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t gvi                   : 1;  /**< [  0:  0](R/W/H) General violation.
                                                                 This bit is set whenever one of the bits in the general DBG_GEN register or
                                                                 DBG_GEN_2 register is set.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
#else /* Word 0 - Little Endian */
        uint32_t gvi                   : 1;  /**< [  0:  0](R/W/H) General violation.
                                                                 This bit is set whenever one of the bits in the general DBG_GEN register or
                                                                 DBG_GEN_2 register is set.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_iop                : 1;  /**< [  1:  1](R/W/H) Error indication is received from I/O APB access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_epp                : 1;  /**< [  2:  2](R/W/H) Error indication is received from EPP access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_edp                : 1;  /**< [  3:  3](R/W/H) Error indication is received from EDP access.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_wrc                : 1;  /**< [  4:  4](R/W/H) Error indication is received when WRC reaches 0x3FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_exok               : 1;  /**< [  5:  5](R/W/H) Error indication slave not support exclusive accesses.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t edap_r_oor            : 1;  /**< [  6:  6](R/W/H) Error indication EDAP read from an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t edap_w_oor            : 1;  /**< [  7:  7](R/W/H) Error indication EDAP write to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics0_oor             : 1;  /**< [  8:  8](R/W/H) Error indication FICS0 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics1_oor             : 1;  /**< [  9:  9](R/W/H) Error indication FICS1read/ write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics2_oor             : 1;  /**< [ 10: 10](R/W/H) Error indication FICS2 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics3_oor             : 1;  /**< [ 11: 11](R/W/H) Error indication FICS3 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics4_oor             : 1;  /**< [ 12: 12](R/W/H) Error indication FICS4 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics5_oor             : 1;  /**< [ 13: 13](R/W/H) Error indication FICS5 read/ write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics6_oor             : 1;  /**< [ 14: 14](R/W/H) Error indication FICS6 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t fics7_oor             : 1;  /**< [ 15: 15](R/W/H) Error indication FICS7 read/write from/to an address out of range.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_rows_oor           : 1;  /**< [ 16: 16](R/W/H) Error indication access to external port using row stride.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ddma_rg_cros          : 1;  /**< [ 17: 17](R/W/H) Error indication DDMA external access crossed external data access port.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t lsu_rg_cros           : 1;  /**< [ 18: 18](R/W/H) Error indication LSU external access crossed external data access port.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_rg_cros            : 1;  /**< [ 19: 19](R/W/H) Error indication Write Buffer external access crossed external data access port
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ddma_idm_cros         : 1;  /**< [ 20: 20](R/W/H) Error indication DDMA internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t lsu_idm_cros          : 1;  /**< [ 21: 21](R/W/H) Error indication LSU internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_idm_cros           : 1;  /**< [ 22: 22](R/W/H) Error indication Write Buffer internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t wb_align_err          : 1;  /**< [ 23: 23](R/W) Error indication Write Buffer access with full bandwidth and address not aligned to DW.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t qman_idm_cros         : 1;  /**< [ 24: 24](R/W/H) Error indication QMAN internal access crossed IDM last address.
                                                                 This bit is set when one of the bits at the QMAN_IDM_CROS register is set.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_bman_pktsize       : 1;  /**< [ 25: 25](R/W/H) Error indication BMAN packet size is zero while access to the buffer in use continues.
                                                                 This bit is set when the BMAN_IRQ_SEL field is configured to interrupt when DSP
                                                                 reads from an almost empty buffer and the number of bytes being read from the
                                                                 buffer exceeds the configured packet size ().
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t unmapped_excptn       : 1;  /**< [ 26: 26](R/W/H) This bit is set when one of the DBG_xUNMPD0/1 registers is asserted and its
                                                                 corresponding mask bit is cleared in DBG_UNMPD_MASK0/1; this indicates that an
                                                                 un-mapped violation occurred in one of the configured regions in IACU or DACU.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t stack_viol_excptn     : 1;  /**< [ 27: 27](R/W/H) This bit is set when there is stack violation detection when the stack address
                                                                 fall outside the pre-configured start and end addresses.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t ovrflw_excptn         : 1;  /**< [ 28: 28](R/W/H) This bit is set when there is calculation overflow in one of the MACs.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t bkrep_excptn          : 1;  /**< [ 29: 29](R/W/H) This bit is set when there is use of more than four nesting levels in BKREP.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t reserved_30           : 1;
        uint32_t vcu_c                 : 1;  /**< [ 31: 31](R/W/H) This bit is set when the VCU attempt to access cacheable region.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_gen_s cn; */
};
typedef union bdk_cbpx_dma_dbg_gen bdk_cbpx_dma_dbg_gen_t;

static inline uint64_t BDK_CBPX_DMA_DBG_GEN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_GEN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822214ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_GEN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_GEN(a) bdk_cbpx_dma_dbg_gen_t
#define bustype_BDK_CBPX_DMA_DBG_GEN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_GEN(a) "CBPX_DMA_DBG_GEN"
#define busnum_BDK_CBPX_DMA_DBG_GEN(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_GEN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_gen2_mask
 *
 * CBP Dma Dbg Gen2 Mask Register
 */
union bdk_cbpx_dma_dbg_gen2_mask
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_gen2_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t m_er_fic1_outs        : 1;  /**< [  8:  8](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_er_fic0_outs        : 1;  /**< [  7:  7](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t reserved_6            : 1;
        uint32_t m_exc_e               : 1;  /**< [  5:  5](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_qman_blank_acc      : 1;  /**< [  4:  4](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_ddma_blank_acc      : 1;  /**< [  3:  3](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t reserved_2            : 1;
        uint32_t m_st_blank_acc        : 1;  /**< [  1:  1](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_ld_blank_acc        : 1;  /**< [  0:  0](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit.
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
#else /* Word 0 - Little Endian */
        uint32_t m_ld_blank_acc        : 1;  /**< [  0:  0](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit.
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_st_blank_acc        : 1;  /**< [  1:  1](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t reserved_2            : 1;
        uint32_t m_ddma_blank_acc      : 1;  /**< [  3:  3](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_qman_blank_acc      : 1;  /**< [  4:  4](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_exc_e               : 1;  /**< [  5:  5](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t reserved_6            : 1;
        uint32_t m_er_fic0_outs        : 1;  /**< [  7:  7](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t m_er_fic1_outs        : 1;  /**< [  8:  8](R/W) This bit is a mask for the corresponding GVI DBG_GEN_2 register bit..
                                                                 0: this bit is not masked in the DBG_GEN_2 register
                                                                 1: this bit is masked in the DBG_GEN_2 register */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_gen2_mask_s cn; */
};
typedef union bdk_cbpx_dma_dbg_gen2_mask bdk_cbpx_dma_dbg_gen2_mask_t;

static inline uint64_t BDK_CBPX_DMA_DBG_GEN2_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_GEN2_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822224ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_GEN2_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_GEN2_MASK(a) bdk_cbpx_dma_dbg_gen2_mask_t
#define bustype_BDK_CBPX_DMA_DBG_GEN2_MASK(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_GEN2_MASK(a) "CBPX_DMA_DBG_GEN2_MASK"
#define busnum_BDK_CBPX_DMA_DBG_GEN2_MASK(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_GEN2_MASK(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_gen_2
 *
 * CBP Dma Dbg Gen 2 Register
 * Note: when the user clear a bit in the GVI register and a new one is set in the same
 * cycle this bit will remain set
 */
union bdk_cbpx_dma_dbg_gen_2
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_gen_2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t er_fic1_outs          : 1;  /**< [  8:  8](R/W/H) Error indication is received when FIC1 outstanding counter reaches 0x1FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_fic0_outs          : 1;  /**< [  7:  7](R/W/H) Error indication is received when FIC0 outstanding counter reaches 0x1FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t reserved_6            : 1;
        uint32_t exc_e                 : 1;  /**< [  5:  5](R/W) Error indication when Exclusive transaction accesses a restricted region. */
        uint32_t qman_blank_acc        : 1;  /**< [  4:  4](R/W) Error indication QMAN access a blank region.
                                                                 This bit is set when an access to a blank region is executed by the QMAN.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t ddma_blank_acc        : 1;  /**< [  3:  3](R/W/H) Error indication DDMA access a blank region.
                                                                 This bit is set when the DDMA detects a task with external address (DDEA) that
                                                                 resides at a blank region.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t reserved_2            : 1;
        uint32_t st_blank_acc          : 1;  /**< [  1:  1](R/W/H) Error indication core store access to a blank region.
                                                                 This bit is set when a store access to a blank region is executed.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t ld_blank_acc          : 1;  /**< [  0:  0](R/W/H) Error indication core load access to a blank region.
                                                                 This bit is set when a load access to a blank region is executed by the core.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
#else /* Word 0 - Little Endian */
        uint32_t ld_blank_acc          : 1;  /**< [  0:  0](R/W/H) Error indication core load access to a blank region.
                                                                 This bit is set when a load access to a blank region is executed by the core.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t st_blank_acc          : 1;  /**< [  1:  1](R/W/H) Error indication core store access to a blank region.
                                                                 This bit is set when a store access to a blank region is executed.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t reserved_2            : 1;
        uint32_t ddma_blank_acc        : 1;  /**< [  3:  3](R/W/H) Error indication DDMA access a blank region.
                                                                 This bit is set when the DDMA detects a task with external address (DDEA) that
                                                                 resides at a blank region.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t qman_blank_acc        : 1;  /**< [  4:  4](R/W) Error indication QMAN access a blank region.
                                                                 This bit is set when an access to a blank region is executed by the QMAN.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit */
        uint32_t exc_e                 : 1;  /**< [  5:  5](R/W) Error indication when Exclusive transaction accesses a restricted region. */
        uint32_t reserved_6            : 1;
        uint32_t er_fic0_outs          : 1;  /**< [  7:  7](R/W/H) Error indication is received when FIC0 outstanding counter reaches 0x1FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t er_fic1_outs          : 1;  /**< [  8:  8](R/W/H) Error indication is received when FIC1 outstanding counter reaches 0x1FF.
                                                                 This bit is a sticky bit and is cleared by writing 0 to this register bit. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_gen_2_s cn; */
};
typedef union bdk_cbpx_dma_dbg_gen_2 bdk_cbpx_dma_dbg_gen_2_t;

static inline uint64_t BDK_CBPX_DMA_DBG_GEN_2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_GEN_2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482221cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_GEN_2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_GEN_2(a) bdk_cbpx_dma_dbg_gen_2_t
#define bustype_BDK_CBPX_DMA_DBG_GEN_2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_GEN_2(a) "CBPX_DMA_DBG_GEN_2"
#define busnum_BDK_CBPX_DMA_DBG_GEN_2(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_GEN_2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_gen_mask
 *
 * CBP Dma Dbg Gen Mask Register
 */
union bdk_cbpx_dma_dbg_gen_mask
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_gen_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t m_vcu_c               : 1;  /**< [ 31: 31](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t reserved_30           : 1;
        uint32_t m_bkrep_excptn        : 1;  /**< [ 29: 29](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ovrflw_excptn       : 1;  /**< [ 28: 28](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_stack_viol_excptn   : 1;  /**< [ 27: 27](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_unmapped_excptn     : 1;  /**< [ 26: 26](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_bman_pktsize     : 1;  /**< [ 25: 25](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_qman_idm_cros       : 1;  /**< [ 24: 24](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_align_err        : 1;  /**< [ 23: 23](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_idm_cros         : 1;  /**< [ 22: 22](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_lsu_idm_cros        : 1;  /**< [ 21: 21](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ddma_idm_cros       : 1;  /**< [ 20: 20](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_rg_cros          : 1;  /**< [ 19: 19](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_lsu_rg_cros         : 1;  /**< [ 18: 18](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ddma_rg_cros        : 1;  /**< [ 17: 17](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_rows_oor         : 1;  /**< [ 16: 16](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics7_oor           : 1;  /**< [ 15: 15](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics6_oor           : 1;  /**< [ 14: 14](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics5_oor           : 1;  /**< [ 13: 13](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics4_oor           : 1;  /**< [ 12: 12](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics3_oor           : 1;  /**< [ 11: 11](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics2_oor           : 1;  /**< [ 10: 10](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics1_oor           : 1;  /**< [  9:  9](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics0_oor           : 1;  /**< [  8:  8](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_edap_w_oor          : 1;  /**< [  7:  7](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_edap_r_oor          : 1;  /**< [  6:  6](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_exok             : 1;  /**< [  5:  5](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_wrc              : 1;  /**< [  4:  4](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_edp              : 1;  /**< [  3:  3](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_epp              : 1;  /**< [  2:  2](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_iop              : 1;  /**< [  1:  1](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_gvi                 : 1;  /**< [  0:  0](R/W) This bit will mask all the General violation registers.
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
#else /* Word 0 - Little Endian */
        uint32_t m_gvi                 : 1;  /**< [  0:  0](R/W) This bit will mask all the General violation registers.
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_iop              : 1;  /**< [  1:  1](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_epp              : 1;  /**< [  2:  2](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_edp              : 1;  /**< [  3:  3](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_wrc              : 1;  /**< [  4:  4](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_exok             : 1;  /**< [  5:  5](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_edap_r_oor          : 1;  /**< [  6:  6](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_edap_w_oor          : 1;  /**< [  7:  7](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics0_oor           : 1;  /**< [  8:  8](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics1_oor           : 1;  /**< [  9:  9](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics2_oor           : 1;  /**< [ 10: 10](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics3_oor           : 1;  /**< [ 11: 11](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics4_oor           : 1;  /**< [ 12: 12](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics5_oor           : 1;  /**< [ 13: 13](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics6_oor           : 1;  /**< [ 14: 14](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_fics7_oor           : 1;  /**< [ 15: 15](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_rows_oor         : 1;  /**< [ 16: 16](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ddma_rg_cros        : 1;  /**< [ 17: 17](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_lsu_rg_cros         : 1;  /**< [ 18: 18](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_rg_cros          : 1;  /**< [ 19: 19](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ddma_idm_cros       : 1;  /**< [ 20: 20](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_lsu_idm_cros        : 1;  /**< [ 21: 21](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_idm_cros         : 1;  /**< [ 22: 22](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_wb_align_err        : 1;  /**< [ 23: 23](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_qman_idm_cros       : 1;  /**< [ 24: 24](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_er_bman_pktsize     : 1;  /**< [ 25: 25](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_unmapped_excptn     : 1;  /**< [ 26: 26](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_stack_viol_excptn   : 1;  /**< [ 27: 27](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_ovrflw_excptn       : 1;  /**< [ 28: 28](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t m_bkrep_excptn        : 1;  /**< [ 29: 29](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
        uint32_t reserved_30           : 1;
        uint32_t m_vcu_c               : 1;  /**< [ 31: 31](R/W) This bit is a mask for the corresponding GVI DBG_GEN register bit..
                                                                 0: this bit is not masked in the DBG_GEN register
                                                                 1: this bit is masked in the DBG_GEN register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_gen_mask_s cn; */
};
typedef union bdk_cbpx_dma_dbg_gen_mask bdk_cbpx_dma_dbg_gen_mask_t;

static inline uint64_t BDK_CBPX_DMA_DBG_GEN_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_GEN_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822220ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_GEN_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_GEN_MASK(a) bdk_cbpx_dma_dbg_gen_mask_t
#define bustype_BDK_CBPX_DMA_DBG_GEN_MASK(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_GEN_MASK(a) "CBPX_DMA_DBG_GEN_MASK"
#define busnum_BDK_CBPX_DMA_DBG_GEN_MASK(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_GEN_MASK(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_stack_end
 *
 * CBP Dma Dbg Stack End Register
 */
union bdk_cbpx_dma_dbg_stack_end
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_stack_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t stack_violtn_end_add  : 32; /**< [ 31:  0](R/W) Defines the stack violation END address, any access outside region defined by
                                                                 stack start and end addresses issues stack violation exception */
#else /* Word 0 - Little Endian */
        uint32_t stack_violtn_end_add  : 32; /**< [ 31:  0](R/W) Defines the stack violation END address, any access outside region defined by
                                                                 stack start and end addresses issues stack violation exception */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_stack_end_s cn; */
};
typedef union bdk_cbpx_dma_dbg_stack_end bdk_cbpx_dma_dbg_stack_end_t;

static inline uint64_t BDK_CBPX_DMA_DBG_STACK_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_STACK_END(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822248ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_STACK_END", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_STACK_END(a) bdk_cbpx_dma_dbg_stack_end_t
#define bustype_BDK_CBPX_DMA_DBG_STACK_END(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_STACK_END(a) "CBPX_DMA_DBG_STACK_END"
#define busnum_BDK_CBPX_DMA_DBG_STACK_END(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_STACK_END(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_stack_start
 *
 * CBP Dma Dbg Stack Start Register
 */
union bdk_cbpx_dma_dbg_stack_start
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_stack_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t stk_violtn_start_add  : 32; /**< [ 31:  0](R/W) Defines the outside region defined by stack start and end addresses issues stack
                                                                 violation exception */
#else /* Word 0 - Little Endian */
        uint32_t stk_violtn_start_add  : 32; /**< [ 31:  0](R/W) Defines the outside region defined by stack start and end addresses issues stack
                                                                 violation exception */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_stack_start_s cn; */
};
typedef union bdk_cbpx_dma_dbg_stack_start bdk_cbpx_dma_dbg_stack_start_t;

static inline uint64_t BDK_CBPX_DMA_DBG_STACK_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_STACK_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822244ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_STACK_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_STACK_START(a) bdk_cbpx_dma_dbg_stack_start_t
#define bustype_BDK_CBPX_DMA_DBG_STACK_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_STACK_START(a) "CBPX_DMA_DBG_STACK_START"
#define busnum_BDK_CBPX_DMA_DBG_STACK_START(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_STACK_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dma_dbg_wrc
 *
 * CBP Dma Dbg Wrc Register
 */
union bdk_cbpx_dma_dbg_wrc
{
    uint32_t u;
    struct bdk_cbpx_dma_dbg_wrc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t wrc                   : 10; /**< [  9:  0](R/W/H) Write response counter.
                                                                 Status indication for the write response.
                                                                 Any write to this register clears its value. */
#else /* Word 0 - Little Endian */
        uint32_t wrc                   : 10; /**< [  9:  0](R/W/H) Write response counter.
                                                                 Status indication for the write response.
                                                                 Any write to this register clears its value. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dma_dbg_wrc_s cn; */
};
typedef union bdk_cbpx_dma_dbg_wrc bdk_cbpx_dma_dbg_wrc_t;

static inline uint64_t BDK_CBPX_DMA_DBG_WRC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMA_DBG_WRC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822218ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMA_DBG_WRC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMA_DBG_WRC(a) bdk_cbpx_dma_dbg_wrc_t
#define bustype_BDK_CBPX_DMA_DBG_WRC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMA_DBG_WRC(a) "CBPX_DMA_DBG_WRC"
#define busnum_BDK_CBPX_DMA_DBG_WRC(a) (a)
#define arguments_BDK_CBPX_DMA_DBG_WRC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_dacc
 *
 * CBP Dmss Mss Dacc Register
 */
union bdk_cbpx_dmss_mss_dacc
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_dacc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_11_31        : 21;
        uint32_t dauol                 : 3;  /**< [ 10:  8](R/W) DDMA Upload Outstanding Limit when using EDP
                                                                 000: DDMA Can issue up to 4 outstanding AXI write bursts
                                                                 001: DDMA Can issue up to 8 outstanding AXI write bursts
                                                                 010: DDMA Can issue up to 16 outstanding AXI write bursts
                                                                 011: DDMA Can issue up to 32 outstanding AXI write bursts
                                                                 100-111: Reserved */
        uint32_t dadol                 : 4;  /**< [  7:  4](R/W) DDMA AXI Download Outstanding Limit:
                                                                 0000  DDMA Can issue up to 4 outstanding AXI read bursts
                                                                 0001  DDMA Can issue up to 5 outstanding AXI read bursts
                                                                 0010  DDMA Can issue up to 6 outstanding AXI read bursts
                                                                 0011  DDMA Can issue up to 7 outstanding AXI read bursts
                                                                 0100  DDMA Can issue up to 8 outstanding AXI read bursts
                                                                 0101  DDMA Can issue up to 9 outstanding AXI read bursts
                                                                 0110  DDMA Can issue up to 10 outstanding AXI read bursts
                                                                 0111  DDMA Can issue up to 11 outstanding AXI read bursts
                                                                 1000  DDMA Can issue up to 12 outstanding AXI read bursts
                                                                 1001  DDMA Can issue up to 13 outstanding AXI read bursts
                                                                 1010  DDMA Can issue up to 14 outstanding AXI read bursts
                                                                 1011  DDMA Can issue up to 15 outstanding AXI read bursts
                                                                 1100  DDMA Can issue up to 16 outstanding AXI read bursts
                                                                 1101..1111  Reserved
                                                                 The number of outstanding DDMA transactions is unlimited when the DDMA is
                                                                 downloading using a FIC port for accessing external memory. */
        uint32_t reserved_2_3          : 2;
        uint32_t dpri                  : 1;  /**< [  1:  1](R/W) DMA LRUA priority bit:
                                                                 0  DMA gets first phase arbitration priority using priority region
                                                                 1  DMA gets Highest priority at the first phase arbitration */
        uint32_t dpraw                 : 1;  /**< [  0:  0](R/W) Data protection RAW/SO indication. This bit should not be modified during AXI
                                                                 write or read transfers.
                                                                 Note: this option must be set when using the ACE interface */
#else /* Word 0 - Little Endian */
        uint32_t dpraw                 : 1;  /**< [  0:  0](R/W) Data protection RAW/SO indication. This bit should not be modified during AXI
                                                                 write or read transfers.
                                                                 Note: this option must be set when using the ACE interface */
        uint32_t dpri                  : 1;  /**< [  1:  1](R/W) DMA LRUA priority bit:
                                                                 0  DMA gets first phase arbitration priority using priority region
                                                                 1  DMA gets Highest priority at the first phase arbitration */
        uint32_t reserved_2_3          : 2;
        uint32_t dadol                 : 4;  /**< [  7:  4](R/W) DDMA AXI Download Outstanding Limit:
                                                                 0000  DDMA Can issue up to 4 outstanding AXI read bursts
                                                                 0001  DDMA Can issue up to 5 outstanding AXI read bursts
                                                                 0010  DDMA Can issue up to 6 outstanding AXI read bursts
                                                                 0011  DDMA Can issue up to 7 outstanding AXI read bursts
                                                                 0100  DDMA Can issue up to 8 outstanding AXI read bursts
                                                                 0101  DDMA Can issue up to 9 outstanding AXI read bursts
                                                                 0110  DDMA Can issue up to 10 outstanding AXI read bursts
                                                                 0111  DDMA Can issue up to 11 outstanding AXI read bursts
                                                                 1000  DDMA Can issue up to 12 outstanding AXI read bursts
                                                                 1001  DDMA Can issue up to 13 outstanding AXI read bursts
                                                                 1010  DDMA Can issue up to 14 outstanding AXI read bursts
                                                                 1011  DDMA Can issue up to 15 outstanding AXI read bursts
                                                                 1100  DDMA Can issue up to 16 outstanding AXI read bursts
                                                                 1101..1111  Reserved
                                                                 The number of outstanding DDMA transactions is unlimited when the DDMA is
                                                                 downloading using a FIC port for accessing external memory. */
        uint32_t dauol                 : 3;  /**< [ 10:  8](R/W) DDMA Upload Outstanding Limit when using EDP
                                                                 000: DDMA Can issue up to 4 outstanding AXI write bursts
                                                                 001: DDMA Can issue up to 8 outstanding AXI write bursts
                                                                 010: DDMA Can issue up to 16 outstanding AXI write bursts
                                                                 011: DDMA Can issue up to 32 outstanding AXI write bursts
                                                                 100-111: Reserved */
        uint32_t reserved_11_31        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_dacc_s cn; */
};
typedef union bdk_cbpx_dmss_mss_dacc bdk_cbpx_dmss_mss_dacc_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DACC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DACC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482203cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DACC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DACC(a) bdk_cbpx_dmss_mss_dacc_t
#define bustype_BDK_CBPX_DMSS_MSS_DACC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DACC(a) "CBPX_DMSS_MSS_DACC"
#define busnum_BDK_CBPX_DMSS_MSS_DACC(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DACC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_ddea
 *
 * CBP Dmss Mss Ddea Register
 * When WBE, EWBE and EDPE are set, all write transactions have been issued to the
 * external bus, and are not delayed anywhere in the MSS/port/bridge.
 * Bits [31:18] are ignored if IDM is configured to 256KB.
 * Bits [31:19] are ignored if IDM is configured to 512KB.
 */
union bdk_cbpx_dmss_mss_ddea
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_ddea_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ddea                  : 32; /**< [ 31:  0](R/W/H) Data DMA external address used as source/destination address for DMA download/upload.
                                                                 The DDEA register is also used for holding a 32-bit message when BSZ==41111 and DDIR==0 (download).
                                                                 Reading from this register will return the current external address used by the DDMA. */
#else /* Word 0 - Little Endian */
        uint32_t ddea                  : 32; /**< [ 31:  0](R/W/H) Data DMA external address used as source/destination address for DMA download/upload.
                                                                 The DDEA register is also used for holding a 32-bit message when BSZ==41111 and DDIR==0 (download).
                                                                 Reading from this register will return the current external address used by the DDMA. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_ddea_s cn; */
};
typedef union bdk_cbpx_dmss_mss_ddea bdk_cbpx_dmss_mss_ddea_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DDEA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DDEA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482201cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DDEA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DDEA(a) bdk_cbpx_dmss_mss_ddea_t
#define bustype_BDK_CBPX_DMSS_MSS_DDEA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DDEA(a) "CBPX_DMSS_MSS_DDEA"
#define busnum_BDK_CBPX_DMSS_MSS_DDEA(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DDEA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_ddia
 *
 * CBP Dmss Mss Ddia Register
 * Note: 	When used as IDM address:
 */
union bdk_cbpx_dmss_mss_ddia
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_ddia_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ddia                  : 32; /**< [ 31:  0](R/W/H) IDM address used by the DMA as source/destination address for DMA upload/download.
                                                                 The DDIA register is also used for holding a 32 bit message when BSZ==41111 and DDIR==1 (upload)
                                                                 Reading from this register will return the current internal address used by the DDMA. */
#else /* Word 0 - Little Endian */
        uint32_t ddia                  : 32; /**< [ 31:  0](R/W/H) IDM address used by the DMA as source/destination address for DMA upload/download.
                                                                 The DDIA register is also used for holding a 32 bit message when BSZ==41111 and DDIR==1 (upload)
                                                                 Reading from this register will return the current internal address used by the DDMA. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_ddia_s cn; */
};
typedef union bdk_cbpx_dmss_mss_ddia bdk_cbpx_dmss_mss_ddia_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DDIA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DDIA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822020ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DDIA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DDIA(a) bdk_cbpx_dmss_mss_ddia_t
#define bustype_BDK_CBPX_DMSS_MSS_DDIA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DDIA(a) "CBPX_DMSS_MSS_DDIA"
#define busnum_BDK_CBPX_DMSS_MSS_DDIA(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DDIA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_ddqs
 *
 * CBP Dmss Mss Ddqs Register
 * * The QEMPTY, QFULL, QCOUNT and QOVFL are updated two cycles after DDTC is written with a value other than zero. Any In command reading from these fields must be placed at least two cycles from the Out command that is writing to the DDTC.
 */
union bdk_cbpx_dmss_mss_ddqs
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_ddqs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t qovfl                 : 1;  /**< [  7:  7](R/W/H) A new request cannot be added to the queue (queue over flow)
                                                                 1: queue overflow
                                                                 0: queue not in overflow
                                                                 This bit is clear by written 0 */
        uint32_t qauto                 : 1;  /**< [  6:  6](R/W) Queue request transferred to Data DMA automatically or by NEXT_DDMA signal:
                                                                 1: according to the NEXT_DDMA
                                                                 0: automatically
                                                                 (read/write) */
        uint32_t qcount                : 4;  /**< [  5:  2](RO/H) Data DMA request count: indicates the number of DMA requests pending and ongoing in the Q.
                                                                 Note: The ongoing transaction is included
                                                                 0000: no requests on the Queue
                                                                 0001-1000: number of requests on the Queue */
        uint32_t qfull                 : 1;  /**< [  1:  1](RO/H) Data DMA request queue is full */
        uint32_t qempty                : 1;  /**< [  0:  0](RO) Data DMA request queue is empty */
#else /* Word 0 - Little Endian */
        uint32_t qempty                : 1;  /**< [  0:  0](RO) Data DMA request queue is empty */
        uint32_t qfull                 : 1;  /**< [  1:  1](RO/H) Data DMA request queue is full */
        uint32_t qcount                : 4;  /**< [  5:  2](RO/H) Data DMA request count: indicates the number of DMA requests pending and ongoing in the Q.
                                                                 Note: The ongoing transaction is included
                                                                 0000: no requests on the Queue
                                                                 0001-1000: number of requests on the Queue */
        uint32_t qauto                 : 1;  /**< [  6:  6](R/W) Queue request transferred to Data DMA automatically or by NEXT_DDMA signal:
                                                                 1: according to the NEXT_DDMA
                                                                 0: automatically
                                                                 (read/write) */
        uint32_t qovfl                 : 1;  /**< [  7:  7](R/W/H) A new request cannot be added to the queue (queue over flow)
                                                                 1: queue overflow
                                                                 0: queue not in overflow
                                                                 This bit is clear by written 0 */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_ddqs_s cn; */
};
typedef union bdk_cbpx_dmss_mss_ddqs bdk_cbpx_dmss_mss_ddqs_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DDQS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DDQS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822028ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DDQS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DDQS(a) bdk_cbpx_dmss_mss_ddqs_t
#define bustype_BDK_CBPX_DMSS_MSS_DDQS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DDQS(a) "CBPX_DMSS_MSS_DDQS"
#define busnum_BDK_CBPX_DMSS_MSS_DDQS(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DDQS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_ddrs
 *
 * CBP Dmss Mss Ddrs Register
 * * The STSX and LSID fields are updated two cycles after DDTC is written with a value other than zero. Any in command reading from these fields must be placed at least two cycles from the Out command writing to the DDTC.
 */
union bdk_cbpx_dmss_mss_ddrs
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_ddrs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_19_31        : 13;
        uint32_t lsid                  : 3;  /**< [ 18: 16](RO/H) The last DMA configuration entered into the queue ID number */
        uint32_t sts7                  : 2;  /**< [ 15: 14](RO/H) ID7 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts6                  : 2;  /**< [ 13: 12](RO/H) ID6 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts5                  : 2;  /**< [ 11: 10](RO/H) ID5 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts4                  : 2;  /**< [  9:  8](RO/H) ID4 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts3                  : 2;  /**< [  7:  6](RO/H) ID3 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts2                  : 2;  /**< [  5:  4](RO/H) ID2 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts1                  : 2;  /**< [  3:  2](RO/H) ID1 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts0                  : 2;  /**< [  1:  0](RO/H) ID0 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
#else /* Word 0 - Little Endian */
        uint32_t sts0                  : 2;  /**< [  1:  0](RO/H) ID0 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts1                  : 2;  /**< [  3:  2](RO/H) ID1 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts2                  : 2;  /**< [  5:  4](RO/H) ID2 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts3                  : 2;  /**< [  7:  6](RO/H) ID3 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts4                  : 2;  /**< [  9:  8](RO/H) ID4 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts5                  : 2;  /**< [ 11: 10](RO/H) ID5 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts6                  : 2;  /**< [ 13: 12](RO/H) ID6 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t sts7                  : 2;  /**< [ 15: 14](RO/H) ID7 statuses:
                                                                 00: never used
                                                                 01: pending
                                                                 10: ongoing (used by the DMA)
                                                                 11: done */
        uint32_t lsid                  : 3;  /**< [ 18: 16](RO/H) The last DMA configuration entered into the queue ID number */
        uint32_t reserved_19_31        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_ddrs_s cn; */
};
typedef union bdk_cbpx_dmss_mss_ddrs bdk_cbpx_dmss_mss_ddrs_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DDRS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DDRS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482202cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DDRS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DDRS(a) bdk_cbpx_dmss_mss_ddrs_t
#define bustype_BDK_CBPX_DMSS_MSS_DDRS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DDRS(a) "CBPX_DMSS_MSS_DDRS"
#define busnum_BDK_CBPX_DMSS_MSS_DDRS(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DDRS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_ddtc
 *
 * CBP Dmss Mss Ddtc Register
 * Note: It is illegal for (DDTC + MSS_DDIA) to exceed the internal memory boundary.
 */
union bdk_cbpx_dmss_mss_ddtc
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_ddtc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ddie                  : 1;  /**< [ 31: 31](R/W) Data DMA interrupt enable:
                                                                 0: The data DMA interrupt at the end of the transfer is disabled.
                                                                 1: The data DMA interrupt at the end of the transfer is enabled. */
        uint32_t ddir                  : 1;  /**< [ 30: 30](R/W) DMA direction:
                                                                 0: The DMA downloads from the external memory to the IDM.
                                                                 1: The DMA uploads from the IDM to the external memory. */
        uint32_t ddst                  : 1;  /**< [ 29: 29](RO/H) Data DMA status:
                                                                 This read-only bit indicates the data DMA status. When set, the data DMA is busy
                                                                 meaning, a frame is currently being transferred. When cleared, the DMA is not
                                                                 busy. This bit is automatically set by hardware when a frame transfer starts,
                                                                 and is cleared when the frame transfer has been completed. */
        uint32_t bsz                   : 4;  /**< [ 28: 25](R/W) Data DMA maximum burst length:
                                                                 0000: Single (1) transfers with incrementing addresses (INCR)
                                                                 0001: Single transfers with fixed address (FIXED)
                                                                 0010: 4 transfers FIXED
                                                                 0011: 8 transfers FIXED
                                                                 0100: 16 transfers FIXED
                                                                 0101: 32 transfers INCR
                                                                 0110: 4 transfers INCR
                                                                 0111: 64 transfers INCR (AXI4 only)
                                                                 1000: 128 transfers INCR (AXI4 only)
                                                                 1001: 256 transfers INCR (AXI4 only)
                                                                 1010: 8 transfers INCR
                                                                 1110: 16 transfers INCR
                                                                 1111: Message
                                                                 Other values are reserved.
                                                                 Only Single transfer sizes are allowed when using a FICM port. */
        uint32_t trid                  : 3;  /**< [ 24: 22](RO/H) Transaction queue ID (read only) */
        uint32_t reserved_21           : 1;
        uint32_t ddtc                  : 21; /**< [ 20:  0](R/W/H) Data DMA transfer counts indicates the number of data bytes to transfer.
                                                                 Reading from this field will return the current transfer count used by the DDMA.
                                                                 When using BSZ==4b1111 (message transfer) the DDTC must be set to 0.
                                                                 Note: when using 64 Byte boundary configuration the bursts length cannot exceed four */
#else /* Word 0 - Little Endian */
        uint32_t ddtc                  : 21; /**< [ 20:  0](R/W/H) Data DMA transfer counts indicates the number of data bytes to transfer.
                                                                 Reading from this field will return the current transfer count used by the DDMA.
                                                                 When using BSZ==4b1111 (message transfer) the DDTC must be set to 0.
                                                                 Note: when using 64 Byte boundary configuration the bursts length cannot exceed four */
        uint32_t reserved_21           : 1;
        uint32_t trid                  : 3;  /**< [ 24: 22](RO/H) Transaction queue ID (read only) */
        uint32_t bsz                   : 4;  /**< [ 28: 25](R/W) Data DMA maximum burst length:
                                                                 0000: Single (1) transfers with incrementing addresses (INCR)
                                                                 0001: Single transfers with fixed address (FIXED)
                                                                 0010: 4 transfers FIXED
                                                                 0011: 8 transfers FIXED
                                                                 0100: 16 transfers FIXED
                                                                 0101: 32 transfers INCR
                                                                 0110: 4 transfers INCR
                                                                 0111: 64 transfers INCR (AXI4 only)
                                                                 1000: 128 transfers INCR (AXI4 only)
                                                                 1001: 256 transfers INCR (AXI4 only)
                                                                 1010: 8 transfers INCR
                                                                 1110: 16 transfers INCR
                                                                 1111: Message
                                                                 Other values are reserved.
                                                                 Only Single transfer sizes are allowed when using a FICM port. */
        uint32_t ddst                  : 1;  /**< [ 29: 29](RO/H) Data DMA status:
                                                                 This read-only bit indicates the data DMA status. When set, the data DMA is busy
                                                                 meaning, a frame is currently being transferred. When cleared, the DMA is not
                                                                 busy. This bit is automatically set by hardware when a frame transfer starts,
                                                                 and is cleared when the frame transfer has been completed. */
        uint32_t ddir                  : 1;  /**< [ 30: 30](R/W) DMA direction:
                                                                 0: The DMA downloads from the external memory to the IDM.
                                                                 1: The DMA uploads from the IDM to the external memory. */
        uint32_t ddie                  : 1;  /**< [ 31: 31](R/W) Data DMA interrupt enable:
                                                                 0: The data DMA interrupt at the end of the transfer is disabled.
                                                                 1: The data DMA interrupt at the end of the transfer is enabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_ddtc_s cn; */
};
typedef union bdk_cbpx_dmss_mss_ddtc bdk_cbpx_dmss_mss_ddtc_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DDTC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DDTC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822024ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DDTC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DDTC(a) bdk_cbpx_dmss_mss_ddtc_t
#define bustype_BDK_CBPX_DMSS_MSS_DDTC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DDTC(a) "CBPX_DMSS_MSS_DDTC"
#define busnum_BDK_CBPX_DMSS_MSS_DDTC(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DDTC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_dmba
 *
 * CBP Dmss Mss Dmba Register
 * Note: The number of bits used for DMBA depends on the IDM size.
 */
union bdk_cbpx_dmss_mss_dmba
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_dmba_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dmba                  : 32; /**< [ 31:  0](R/W) Data memory base address of the IDM.
                                                                 For 4 and 8 blocks IDM the mapping resolution is the IDM size, in bytes
                                                                 (128KB/256KB/512KB/1024KB). In the 1024KB configuration, the 20 LSBs are written
                                                                 as 0. In the 512KB configuration, the 19 LSBs are written as 0. In the 256KB
                                                                 configuration, the 18 LSBs are written as 0. In the 128KB configuration, the 17
                                                                 LSBs are written as 0. */
#else /* Word 0 - Little Endian */
        uint32_t dmba                  : 32; /**< [ 31:  0](R/W) Data memory base address of the IDM.
                                                                 For 4 and 8 blocks IDM the mapping resolution is the IDM size, in bytes
                                                                 (128KB/256KB/512KB/1024KB). In the 1024KB configuration, the 20 LSBs are written
                                                                 as 0. In the 512KB configuration, the 19 LSBs are written as 0. In the 256KB
                                                                 configuration, the 18 LSBs are written as 0. In the 128KB configuration, the 17
                                                                 LSBs are written as 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_dmba_s cn; */
};
typedef union bdk_cbpx_dmss_mss_dmba bdk_cbpx_dmss_mss_dmba_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DMBA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DMBA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822014ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DMBA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DMBA(a) bdk_cbpx_dmss_mss_dmba_t
#define bustype_BDK_CBPX_DMSS_MSS_DMBA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DMBA(a) "CBPX_DMSS_MSS_DMBA"
#define busnum_BDK_CBPX_DMSS_MSS_DMBA(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DMBA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_dmbe
 *
 * CBP Dmss Mss Dmbe Register
 * When WBE, EWBE and EDPE are set, all write transactions have been issued to the
 * external bus, and are not delayed anywhere in the MSS/port/bridge.
 */
union bdk_cbpx_dmss_mss_dmbe
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_dmbe_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_19_31        : 13;
        uint32_t csoub                 : 1;  /**< [ 18: 18](RO) Cache Software Operation Busy:
                                                                 1: Not busy
                                                                 0: Busy */
        uint32_t ewbb                  : 1;  /**< [ 17: 17](RO) 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t l1wbb                 : 1;  /**< [ 16: 16](RO) L1WB queue  Busy:
                                                                 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t reserved_14_15        : 2;
        uint32_t fic1r                 : 1;  /**< [ 13: 13](RO) FIC read  Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic1w                 : 1;  /**< [ 12: 12](RO) FIC write Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic0r                 : 1;  /**< [ 11: 11](RO) FIC read Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic0w                 : 1;  /**< [ 10: 10](RO) FIC write Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t qman                  : 1;  /**< [  9:  9](RO) QMAN Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the QMEN has a pending or ongoing request. */
        uint32_t dma                   : 1;  /**< [  8:  8](RO) DMA Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the DMA has a pending or ongoing request. */
        uint32_t axip                  : 1;  /**< [  7:  7](RO) This read-only bit indicates that the AXI write (RAW) protection registers are empty. */
        uint32_t bf                    : 1;  /**< [  6:  6](RO) Cache line fill Busy :
                                                                 1: Not busy (no cache line fills)
                                                                 0: Busy
                                                                 Written to by hardware. */
        uint32_t reserved_5            : 1;
        uint32_t adlb                  : 1;  /**< [  4:  4](RO) ADL Busy:
                                                                 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t dmss_idle             : 1;  /**< [  3:  3](RO/H) This read-only bit indicates DMSS is in idle state. This means the following status:
                                                                 ADLB is set
                                                                 WBE is set
                                                                 EWBE  is set
                                                                 EDPE is set */
        uint32_t edpe                  : 1;  /**< [  2:  2](RO) This read-only indicates that there are no pending transactions (from any
                                                                 source) inside the External data port. */
        uint32_t ewbe                  : 1;  /**< [  1:  1](RO/H) This read-only bit indicates the External Data Port core write transaction
                                                                 status. When set, the External Data Port has no pending write originated by the
                                                                 write buffer transactions. */
        uint32_t wbe                   : 1;  /**< [  0:  0](RO/H) This read-only bit indicates the write buffer status. When set, the write buffer
                                                                 is empty (address delay lines and queue are all empty). */
#else /* Word 0 - Little Endian */
        uint32_t wbe                   : 1;  /**< [  0:  0](RO/H) This read-only bit indicates the write buffer status. When set, the write buffer
                                                                 is empty (address delay lines and queue are all empty). */
        uint32_t ewbe                  : 1;  /**< [  1:  1](RO/H) This read-only bit indicates the External Data Port core write transaction
                                                                 status. When set, the External Data Port has no pending write originated by the
                                                                 write buffer transactions. */
        uint32_t edpe                  : 1;  /**< [  2:  2](RO) This read-only indicates that there are no pending transactions (from any
                                                                 source) inside the External data port. */
        uint32_t dmss_idle             : 1;  /**< [  3:  3](RO/H) This read-only bit indicates DMSS is in idle state. This means the following status:
                                                                 ADLB is set
                                                                 WBE is set
                                                                 EWBE  is set
                                                                 EDPE is set */
        uint32_t adlb                  : 1;  /**< [  4:  4](RO) ADL Busy:
                                                                 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t reserved_5            : 1;
        uint32_t bf                    : 1;  /**< [  6:  6](RO) Cache line fill Busy :
                                                                 1: Not busy (no cache line fills)
                                                                 0: Busy
                                                                 Written to by hardware. */
        uint32_t axip                  : 1;  /**< [  7:  7](RO) This read-only bit indicates that the AXI write (RAW) protection registers are empty. */
        uint32_t dma                   : 1;  /**< [  8:  8](RO) DMA Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the DMA has a pending or ongoing request. */
        uint32_t qman                  : 1;  /**< [  9:  9](RO) QMAN Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the QMEN has a pending or ongoing request. */
        uint32_t fic0w                 : 1;  /**< [ 10: 10](RO) FIC write Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic0r                 : 1;  /**< [ 11: 11](RO) FIC read Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic1w                 : 1;  /**< [ 12: 12](RO) FIC write Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t fic1r                 : 1;  /**< [ 13: 13](RO) FIC read  Busy:
                                                                 1: Not busy
                                                                 0: Busy
                                                                 Written to by hardware. Indicates whether the FIC has an ongoing request. */
        uint32_t reserved_14_15        : 2;
        uint32_t l1wbb                 : 1;  /**< [ 16: 16](RO) L1WB queue  Busy:
                                                                 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t ewbb                  : 1;  /**< [ 17: 17](RO) 1: Not busy (empty)
                                                                 0: Busy (not empty)
                                                                 Written to by hardware. */
        uint32_t csoub                 : 1;  /**< [ 18: 18](RO) Cache Software Operation Busy:
                                                                 1: Not busy
                                                                 0: Busy */
        uint32_t reserved_19_31        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_dmbe_s cn; */
};
typedef union bdk_cbpx_dmss_mss_dmbe bdk_cbpx_dmss_mss_dmbe_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_DMBE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_DMBE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822018ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_DMBE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_DMBE(a) bdk_cbpx_dmss_mss_dmbe_t
#define bustype_BDK_CBPX_DMSS_MSS_DMBE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_DMBE(a) "CBPX_DMSS_MSS_DMBE"
#define busnum_BDK_CBPX_DMSS_MSS_DMBE(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_DMBE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_gpin
 *
 * CBP Dmss Mss Gpin Register
 * Note: This register is read-only.
 */
union bdk_cbpx_dmss_mss_gpin
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_gpin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gpin                  : 32; /**< [ 31:  0](RO) General-purpose inputs.
                                                                 The 32-bit general-purpose input bus is captured in this register. */
#else /* Word 0 - Little Endian */
        uint32_t gpin                  : 32; /**< [ 31:  0](RO) General-purpose inputs.
                                                                 The 32-bit general-purpose input bus is captured in this register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_gpin_s cn; */
};
typedef union bdk_cbpx_dmss_mss_gpin bdk_cbpx_dmss_mss_gpin_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_GPIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_GPIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822034ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_GPIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_GPIN(a) bdk_cbpx_dmss_mss_gpin_t
#define bustype_BDK_CBPX_DMSS_MSS_GPIN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_GPIN(a) "CBPX_DMSS_MSS_GPIN"
#define busnum_BDK_CBPX_DMSS_MSS_GPIN(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_GPIN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_gpout
 *
 * CBP Dmss Mss Gpout Register
 */
union bdk_cbpx_dmss_mss_gpout
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_gpout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gpout                 : 32; /**< [ 31:  0](R/W) General-purpose outputs.
                                                                 The 32-bit general-purpose output bus is connected to this register. */
#else /* Word 0 - Little Endian */
        uint32_t gpout                 : 32; /**< [ 31:  0](R/W) General-purpose outputs.
                                                                 The 32-bit general-purpose output bus is connected to this register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_gpout_s cn; */
};
typedef union bdk_cbpx_dmss_mss_gpout bdk_cbpx_dmss_mss_gpout_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_GPOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_GPOUT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822038ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_GPOUT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_GPOUT(a) bdk_cbpx_dmss_mss_gpout_t
#define bustype_BDK_CBPX_DMSS_MSS_GPOUT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_GPOUT(a) "CBPX_DMSS_MSS_GPOUT"
#define busnum_BDK_CBPX_DMSS_MSS_GPOUT(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_GPOUT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_hdcfg
 *
 * CBP Dmss Mss Hdcfg Register
 */
union bdk_cbpx_dmss_mss_hdcfg
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_hdcfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_25_31        : 7;
        uint32_t axi_b                 : 1;  /**< [ 24: 24](RO) AXI  access boundary crossing (this bit is set by the AXI_B pin)
                                                                 0  4KB  boundary
                                                                 1  64B  boundary */
        uint32_t reserved_22_23        : 2;
        uint32_t l1dca                 : 2;  /**< [ 21: 20](RO) Way Set-Associative
                                                                 00  Reserved
                                                                 01  Two-way
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t l1dcs                 : 3;  /**< [ 19: 17](RO) L1 Data Cache Size
                                                                 000  Not present
                                                                 001  Reserved
                                                                 010  16KB
                                                                 011  32KB
                                                                 100  64KB */
        uint32_t paxi_wid              : 2;  /**< [ 16: 15](RO) Program AXI port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t cac_sze               : 3;  /**< [ 14: 12](RO) Program Cache memory size:
                                                                 000  No cache
                                                                 001  Reserved
                                                                 010  32KB cache
                                                                 011  Reserved
                                                                 1xx  Reserved */
        uint32_t ptcm_sze              : 3;  /**< [ 11:  9](RO) Program TCM memory size:
                                                                               000  32 KB
                                                                               001  64 KB
                                                                               010  128 KB
                                                                               011  256 KB
                                                                               100  512 KB
                                                                               101-111  Reserved */
        uint32_t axi_mwid              : 2;  /**< [  8:  7](RO) AXI master port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t axi_swid              : 2;  /**< [  6:  5](RO) AXI slave port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t tcm_size              : 3;  /**< [  4:  2](RO) IDM size:
                                                                 000  Reserved
                                                                 001  128 KB
                                                                 010  Reserved
                                                                 011  256 KB
                                                                 100  512 KB
                                                                 101  1024 KB
                                                                 110-111  Reserved */
        uint32_t blk_num               : 2;  /**< [  1:  0](RO) IDM number of blocks:
                                                                 00  Eight blocks
                                                                 01  Reserved
                                                                 10  Reserved
                                                                 11  Four blocks */
#else /* Word 0 - Little Endian */
        uint32_t blk_num               : 2;  /**< [  1:  0](RO) IDM number of blocks:
                                                                 00  Eight blocks
                                                                 01  Reserved
                                                                 10  Reserved
                                                                 11  Four blocks */
        uint32_t tcm_size              : 3;  /**< [  4:  2](RO) IDM size:
                                                                 000  Reserved
                                                                 001  128 KB
                                                                 010  Reserved
                                                                 011  256 KB
                                                                 100  512 KB
                                                                 101  1024 KB
                                                                 110-111  Reserved */
        uint32_t axi_swid              : 2;  /**< [  6:  5](RO) AXI slave port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t axi_mwid              : 2;  /**< [  8:  7](RO) AXI master port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t ptcm_sze              : 3;  /**< [ 11:  9](RO) Program TCM memory size:
                                                                               000  32 KB
                                                                               001  64 KB
                                                                               010  128 KB
                                                                               011  256 KB
                                                                               100  512 KB
                                                                               101-111  Reserved */
        uint32_t cac_sze               : 3;  /**< [ 14: 12](RO) Program Cache memory size:
                                                                 000  No cache
                                                                 001  Reserved
                                                                 010  32KB cache
                                                                 011  Reserved
                                                                 1xx  Reserved */
        uint32_t paxi_wid              : 2;  /**< [ 16: 15](RO) Program AXI port width:
                                                                 00  Reserved
                                                                 01  128 bits
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t l1dcs                 : 3;  /**< [ 19: 17](RO) L1 Data Cache Size
                                                                 000  Not present
                                                                 001  Reserved
                                                                 010  16KB
                                                                 011  32KB
                                                                 100  64KB */
        uint32_t l1dca                 : 2;  /**< [ 21: 20](RO) Way Set-Associative
                                                                 00  Reserved
                                                                 01  Two-way
                                                                 10  Reserved
                                                                 11  Reserved */
        uint32_t reserved_22_23        : 2;
        uint32_t axi_b                 : 1;  /**< [ 24: 24](RO) AXI  access boundary crossing (this bit is set by the AXI_B pin)
                                                                 0  4KB  boundary
                                                                 1  64B  boundary */
        uint32_t reserved_25_31        : 7;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_hdcfg_s cn; */
};
typedef union bdk_cbpx_dmss_mss_hdcfg bdk_cbpx_dmss_mss_hdcfg_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_HDCFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_HDCFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822030ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_HDCFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_HDCFG(a) bdk_cbpx_dmss_mss_hdcfg_t
#define bustype_BDK_CBPX_DMSS_MSS_HDCFG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_HDCFG(a) "CBPX_DMSS_MSS_HDCFG"
#define busnum_BDK_CBPX_DMSS_MSS_HDCFG(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_HDCFG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_dmss_mss_sdcfg
 *
 * CBP Dmss Mss Sdcfg Register
 */
union bdk_cbpx_dmss_mss_sdcfg
{
    uint32_t u;
    struct bdk_cbpx_dmss_mss_sdcfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_27_31        : 5;
        uint32_t fic_s_ds              : 1;  /**< [ 26: 26](R/W) Enable and disabled all the FIC Slaves access to the core
                                                                 0: FIC Slave ports can accesses are enabled the core
                                                                 1: FIC Slave ports accesses are disabled
                                                                 All FIC slave ports are affected by this field and .cannot access the core */
        uint32_t edap_ds               : 1;  /**< [ 25: 25](R/W) Enable and disabled the all EDAP port  accesses to the core
                                                                 0: EDAP port can accesses are enabled access the core
                                                                 1: EDAP port accesses are disabled cannot access the core */
        uint32_t snoop_ds              : 1;  /**< [ 24: 24](R/W) Enable and disabled all the snoop port accesses to the core
                                                                 0: snoop port can accesses are enabled the core
                                                                 1: snoop port accesses are disabled cannot access the core */
        uint32_t hwpr                  : 1;  /**< [ 23: 23](R/W) Hardware pre-fetch Enable
                                                                 0  Hardware pre-fetch disabled */
        uint32_t dape                  : 1;  /**< [ 22: 22](R/W) Data Access Protection Enable
                                                                 0  Access protection checking disabled */
        uint32_t reserved_0_21         : 22;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_21         : 22;
        uint32_t dape                  : 1;  /**< [ 22: 22](R/W) Data Access Protection Enable
                                                                 0  Access protection checking disabled */
        uint32_t hwpr                  : 1;  /**< [ 23: 23](R/W) Hardware pre-fetch Enable
                                                                 0  Hardware pre-fetch disabled */
        uint32_t snoop_ds              : 1;  /**< [ 24: 24](R/W) Enable and disabled all the snoop port accesses to the core
                                                                 0: snoop port can accesses are enabled the core
                                                                 1: snoop port accesses are disabled cannot access the core */
        uint32_t edap_ds               : 1;  /**< [ 25: 25](R/W) Enable and disabled the all EDAP port  accesses to the core
                                                                 0: EDAP port can accesses are enabled access the core
                                                                 1: EDAP port accesses are disabled cannot access the core */
        uint32_t fic_s_ds              : 1;  /**< [ 26: 26](R/W) Enable and disabled all the FIC Slaves access to the core
                                                                 0: FIC Slave ports can accesses are enabled the core
                                                                 1: FIC Slave ports accesses are disabled
                                                                 All FIC slave ports are affected by this field and .cannot access the core */
        uint32_t reserved_27_31        : 5;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_dmss_mss_sdcfg_s cn; */
};
typedef union bdk_cbpx_dmss_mss_sdcfg bdk_cbpx_dmss_mss_sdcfg_t;

static inline uint64_t BDK_CBPX_DMSS_MSS_SDCFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_DMSS_MSS_SDCFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822040ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_DMSS_MSS_SDCFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_DMSS_MSS_SDCFG(a) bdk_cbpx_dmss_mss_sdcfg_t
#define bustype_BDK_CBPX_DMSS_MSS_SDCFG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_DMSS_MSS_SDCFG(a) "CBPX_DMSS_MSS_SDCFG"
#define busnum_BDK_CBPX_DMSS_MSS_SDCFG(a) (a)
#define arguments_BDK_CBPX_DMSS_MSS_SDCFG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ecc_ecadd
 *
 * CBP Ecc Ecadd Register
 */
union bdk_cbpx_ecc_ecadd
{
    uint32_t u;
    struct bdk_cbpx_ecc_ecadd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ecadd                 : 27; /**< [ 31:  5](RO) Address of last 512 bits (two code fetch line) containing an ECC error */
        uint32_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_4          : 5;
        uint32_t ecadd                 : 27; /**< [ 31:  5](RO) Address of last 512 bits (two code fetch line) containing an ECC error */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ecc_ecadd_s cn; */
};
typedef union bdk_cbpx_ecc_ecadd bdk_cbpx_ecc_ecadd_t;

static inline uint64_t BDK_CBPX_ECC_ECADD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_ECC_ECADD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822050ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_ECC_ECADD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_ECC_ECADD(a) bdk_cbpx_ecc_ecadd_t
#define bustype_BDK_CBPX_ECC_ECADD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_ECC_ECADD(a) "CBPX_ECC_ECADD"
#define busnum_BDK_CBPX_ECC_ECADD(a) (a)
#define arguments_BDK_CBPX_ECC_ECADD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ecc_ectadd
 *
 * CBP Ecc Ectadd Register
 */
union bdk_cbpx_ecc_ectadd
{
    uint32_t u;
    struct bdk_cbpx_ecc_ectadd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ectadd                : 27; /**< [ 31:  5](RO) Latest TAG ECC error address; this includes the
                                                                 [14:5]    10 bit index
                                                                 [31:15]  17 bit tag */
        uint32_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_4          : 5;
        uint32_t ectadd                : 27; /**< [ 31:  5](RO) Latest TAG ECC error address; this includes the
                                                                 [14:5]    10 bit index
                                                                 [31:15]  17 bit tag */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ecc_ectadd_s cn; */
};
typedef union bdk_cbpx_ecc_ectadd bdk_cbpx_ecc_ectadd_t;

static inline uint64_t BDK_CBPX_ECC_ECTADD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_ECC_ECTADD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822054ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_ECC_ECTADD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_ECC_ECTADD(a) bdk_cbpx_ecc_ectadd_t
#define bustype_BDK_CBPX_ECC_ECTADD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_ECC_ECTADD(a) "CBPX_ECC_ECTADD"
#define busnum_BDK_CBPX_ECC_ECTADD(a) (a)
#define arguments_BDK_CBPX_ECC_ECTADD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add0_att
 *
 * CBP Iacu P Add0 Att Register
 */
union bdk_cbpx_iacu_p_add0_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add0_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add0_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add0_att bdk_cbpx_iacu_p_add0_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD0_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD0_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823474ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD0_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD0_ATT(a) bdk_cbpx_iacu_p_add0_att_t
#define bustype_BDK_CBPX_IACU_P_ADD0_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD0_ATT(a) "CBPX_IACU_P_ADD0_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD0_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD0_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add0_start
 *
 * CBP Iacu P Add0 Start Register
 */
union bdk_cbpx_iacu_p_add0_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add0_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](RO) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](RO) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add0_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add0_start bdk_cbpx_iacu_p_add0_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD0_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD0_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823470ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD0_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD0_START(a) bdk_cbpx_iacu_p_add0_start_t
#define bustype_BDK_CBPX_IACU_P_ADD0_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD0_START(a) "CBPX_IACU_P_ADD0_START"
#define busnum_BDK_CBPX_IACU_P_ADD0_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD0_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add1_att
 *
 * CBP Iacu P Add1 Att Register
 */
union bdk_cbpx_iacu_p_add1_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add1_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add1_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add1_att bdk_cbpx_iacu_p_add1_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD1_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD1_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823484ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD1_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD1_ATT(a) bdk_cbpx_iacu_p_add1_att_t
#define bustype_BDK_CBPX_IACU_P_ADD1_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD1_ATT(a) "CBPX_IACU_P_ADD1_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD1_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD1_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add1_start
 *
 * CBP Iacu P Add1 Start Register
 */
union bdk_cbpx_iacu_p_add1_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add1_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add1_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add1_start bdk_cbpx_iacu_p_add1_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD1_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD1_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823480ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD1_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD1_START(a) bdk_cbpx_iacu_p_add1_start_t
#define bustype_BDK_CBPX_IACU_P_ADD1_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD1_START(a) "CBPX_IACU_P_ADD1_START"
#define busnum_BDK_CBPX_IACU_P_ADD1_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD1_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add2_att
 *
 * CBP Iacu P Add2 Att Register
 */
union bdk_cbpx_iacu_p_add2_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add2_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add2_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add2_att bdk_cbpx_iacu_p_add2_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD2_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD2_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823494ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD2_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD2_ATT(a) bdk_cbpx_iacu_p_add2_att_t
#define bustype_BDK_CBPX_IACU_P_ADD2_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD2_ATT(a) "CBPX_IACU_P_ADD2_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD2_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD2_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add2_start
 *
 * CBP Iacu P Add2 Start Register
 */
union bdk_cbpx_iacu_p_add2_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add2_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add2_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add2_start bdk_cbpx_iacu_p_add2_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD2_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD2_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823490ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD2_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD2_START(a) bdk_cbpx_iacu_p_add2_start_t
#define bustype_BDK_CBPX_IACU_P_ADD2_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD2_START(a) "CBPX_IACU_P_ADD2_START"
#define busnum_BDK_CBPX_IACU_P_ADD2_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD2_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add3_att
 *
 * CBP Iacu P Add3 Att Register
 */
union bdk_cbpx_iacu_p_add3_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add3_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add3_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add3_att bdk_cbpx_iacu_p_add3_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD3_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD3_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234a4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD3_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD3_ATT(a) bdk_cbpx_iacu_p_add3_att_t
#define bustype_BDK_CBPX_IACU_P_ADD3_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD3_ATT(a) "CBPX_IACU_P_ADD3_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD3_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD3_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add3_start
 *
 * CBP Iacu P Add3 Start Register
 */
union bdk_cbpx_iacu_p_add3_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add3_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add3_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add3_start bdk_cbpx_iacu_p_add3_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD3_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD3_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234a0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD3_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD3_START(a) bdk_cbpx_iacu_p_add3_start_t
#define bustype_BDK_CBPX_IACU_P_ADD3_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD3_START(a) "CBPX_IACU_P_ADD3_START"
#define busnum_BDK_CBPX_IACU_P_ADD3_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD3_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add4_att
 *
 * CBP Iacu P Add4 Att Register
 */
union bdk_cbpx_iacu_p_add4_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add4_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add4_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add4_att bdk_cbpx_iacu_p_add4_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD4_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD4_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234b4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD4_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD4_ATT(a) bdk_cbpx_iacu_p_add4_att_t
#define bustype_BDK_CBPX_IACU_P_ADD4_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD4_ATT(a) "CBPX_IACU_P_ADD4_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD4_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD4_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add4_start
 *
 * CBP Iacu P Add4 Start Register
 */
union bdk_cbpx_iacu_p_add4_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add4_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add4_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add4_start bdk_cbpx_iacu_p_add4_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD4_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD4_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234b0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD4_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD4_START(a) bdk_cbpx_iacu_p_add4_start_t
#define bustype_BDK_CBPX_IACU_P_ADD4_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD4_START(a) "CBPX_IACU_P_ADD4_START"
#define busnum_BDK_CBPX_IACU_P_ADD4_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD4_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add5_att
 *
 * CBP Iacu P Add5 Att Register
 */
union bdk_cbpx_iacu_p_add5_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add5_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add5_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add5_att bdk_cbpx_iacu_p_add5_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD5_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD5_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234c4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD5_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD5_ATT(a) bdk_cbpx_iacu_p_add5_att_t
#define bustype_BDK_CBPX_IACU_P_ADD5_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD5_ATT(a) "CBPX_IACU_P_ADD5_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD5_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD5_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add5_start
 *
 * CBP Iacu P Add5 Start Register
 */
union bdk_cbpx_iacu_p_add5_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add5_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add5_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add5_start bdk_cbpx_iacu_p_add5_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD5_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD5_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234c0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD5_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD5_START(a) bdk_cbpx_iacu_p_add5_start_t
#define bustype_BDK_CBPX_IACU_P_ADD5_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD5_START(a) "CBPX_IACU_P_ADD5_START"
#define busnum_BDK_CBPX_IACU_P_ADD5_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD5_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add6_att
 *
 * CBP Iacu P Add6 Att Register
 */
union bdk_cbpx_iacu_p_add6_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add6_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add6_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add6_att bdk_cbpx_iacu_p_add6_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD6_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD6_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234d4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD6_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD6_ATT(a) bdk_cbpx_iacu_p_add6_att_t
#define bustype_BDK_CBPX_IACU_P_ADD6_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD6_ATT(a) "CBPX_IACU_P_ADD6_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD6_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD6_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add6_start
 *
 * CBP Iacu P Add6 Start Register
 */
union bdk_cbpx_iacu_p_add6_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add6_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add6_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add6_start bdk_cbpx_iacu_p_add6_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD6_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD6_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234d0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD6_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD6_START(a) bdk_cbpx_iacu_p_add6_start_t
#define bustype_BDK_CBPX_IACU_P_ADD6_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD6_START(a) "CBPX_IACU_P_ADD6_START"
#define busnum_BDK_CBPX_IACU_P_ADD6_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD6_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add7_att
 *
 * CBP Iacu P Add7 Att Register
 */
union bdk_cbpx_iacu_p_add7_att
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add7_att_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_12_23        : 12;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_7          : 8;
        uint32_t l2a_p                 : 4;  /**< [ 11:  8](R/W) AXI ARCACHE[3:0]
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_12_23        : 12;
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add7_att_s cn; */
};
typedef union bdk_cbpx_iacu_p_add7_att bdk_cbpx_iacu_p_add7_att_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD7_ATT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD7_ATT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234e4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD7_ATT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD7_ATT(a) bdk_cbpx_iacu_p_add7_att_t
#define bustype_BDK_CBPX_IACU_P_ADD7_ATT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD7_ATT(a) "CBPX_IACU_P_ADD7_ATT"
#define busnum_BDK_CBPX_IACU_P_ADD7_ATT(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD7_ATT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_iacu_p_add7_start
 *
 * CBP Iacu P Add7 Start Register
 */
union bdk_cbpx_iacu_p_add7_start
{
    uint32_t u;
    struct bdk_cbpx_iacu_p_add7_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t p_region_start        : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START; this field is read-only, and is hardcoded to the value of 0x0_0000 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_iacu_p_add7_start_s cn; */
};
typedef union bdk_cbpx_iacu_p_add7_start bdk_cbpx_iacu_p_add7_start_t;

static inline uint64_t BDK_CBPX_IACU_P_ADD7_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_IACU_P_ADD7_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448234e0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_IACU_P_ADD7_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_IACU_P_ADD7_START(a) bdk_cbpx_iacu_p_add7_start_t
#define bustype_BDK_CBPX_IACU_P_ADD7_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_IACU_P_ADD7_START(a) "CBPX_IACU_P_ADD7_START"
#define busnum_BDK_CBPX_IACU_P_ADD7_START(a) (a)
#define arguments_BDK_CBPX_IACU_P_ADD7_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add#_att0
 *
 * CBP Interfaceconfiguration Add Att0 Register
 */
union bdk_cbpx_interfaceconfiguration_addx_att0
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_addx_att0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t wqos                  : 4;  /**< [ 31: 28](R/W) Write transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t domain_f              : 2;  /**< [ 23: 22](R/W) This signal indicates the share-ability domain of read and write transactions
                                                                 Used only if AXI4-ACE is supported */
        uint32_t reserved_21           : 1;
        uint32_t bar                   : 1;  /**< [ 20: 20](R/W) This signal indicates the barrier transaction for read and write
                                                                 0: respecting barriers
                                                                 1: ignoring barriers
                                                                 Used only if AXI4-ACE is supported */
        uint32_t ap                    : 3;  /**< [ 19: 17](R/W) Access Protection. */
        uint32_t mom                   : 1;  /**< [ 16: 16](R/W) Memory Ordering Model:
                                                                 0: Total Store Ordering
                                                                 1: Strong Ordering */
        uint32_t l2a_swop              : 4;  /**< [ 15: 12](R/W) L2 Cache Policy for software operations accesses:  (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate */
        uint32_t l2a_c_rd              : 4;  /**< [ 11:  8](R/W) L2 Cache Policy for read accesses: (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t l2a_c_wr              : 4;  /**< [  7:  4](R/W) L2 Cache Policy for write accesses: (AXI AWCACHE[3:0])
                                                                 0000              Device Non-bufferable
                                                                 0001              Device Bufferable
                                                                 0010              Normal Non-cacheable Non-bufferable
                                                                 0011              Normal Non-cacheable Bufferable
                                                                 0110              Write-through No-allocate
                                                                 0110             Write-through Read-allocate
                                                                 1110 (1010) Write-through Write-allocate
                                                                 1110              Write-through Read and Write-allocate
                                                                 0111              Write-back No-allocate
                                                                 0111             Write-back Read-allocate
                                                                 1111 (1011) Write-back Write-allocate
                                                                 1111              Write-back Read and Write-allocate */
        uint32_t l1w                   : 1;  /**< [  3:  3](R/W) L1DC Write Policy:
                                                                 0: Write-through
                                                                 1: Copy-back */
        uint32_t reserved_2            : 1;
        uint32_t sh                    : 1;  /**< [  1:  1](R/W) Shareable:
                                                                 0: Not shareable with other caches in the system
                                                                 1: Shareable with other caches in the system
                                                                 Used only if AXI4-ACE is supported */
        uint32_t l1dc                  : 1;  /**< [  0:  0](R/W) L1DC Cacheable:
                                                                 0: Not cacheable in L1DC
                                                                 1: L1DC-cacheable
                                                                 This bit is tie to 0 if cache not installed */
#else /* Word 0 - Little Endian */
        uint32_t l1dc                  : 1;  /**< [  0:  0](R/W) L1DC Cacheable:
                                                                 0: Not cacheable in L1DC
                                                                 1: L1DC-cacheable
                                                                 This bit is tie to 0 if cache not installed */
        uint32_t sh                    : 1;  /**< [  1:  1](R/W) Shareable:
                                                                 0: Not shareable with other caches in the system
                                                                 1: Shareable with other caches in the system
                                                                 Used only if AXI4-ACE is supported */
        uint32_t reserved_2            : 1;
        uint32_t l1w                   : 1;  /**< [  3:  3](R/W) L1DC Write Policy:
                                                                 0: Write-through
                                                                 1: Copy-back */
        uint32_t l2a_c_wr              : 4;  /**< [  7:  4](R/W) L2 Cache Policy for write accesses: (AXI AWCACHE[3:0])
                                                                 0000              Device Non-bufferable
                                                                 0001              Device Bufferable
                                                                 0010              Normal Non-cacheable Non-bufferable
                                                                 0011              Normal Non-cacheable Bufferable
                                                                 0110              Write-through No-allocate
                                                                 0110             Write-through Read-allocate
                                                                 1110 (1010) Write-through Write-allocate
                                                                 1110              Write-through Read and Write-allocate
                                                                 0111              Write-back No-allocate
                                                                 0111             Write-back Read-allocate
                                                                 1111 (1011) Write-back Write-allocate
                                                                 1111              Write-back Read and Write-allocate */
        uint32_t l2a_c_rd              : 4;  /**< [ 11:  8](R/W) L2 Cache Policy for read accesses: (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t l2a_swop              : 4;  /**< [ 15: 12](R/W) L2 Cache Policy for software operations accesses:  (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate */
        uint32_t mom                   : 1;  /**< [ 16: 16](R/W) Memory Ordering Model:
                                                                 0: Total Store Ordering
                                                                 1: Strong Ordering */
        uint32_t ap                    : 3;  /**< [ 19: 17](R/W) Access Protection. */
        uint32_t bar                   : 1;  /**< [ 20: 20](R/W) This signal indicates the barrier transaction for read and write
                                                                 0: respecting barriers
                                                                 1: ignoring barriers
                                                                 Used only if AXI4-ACE is supported */
        uint32_t reserved_21           : 1;
        uint32_t domain_f              : 2;  /**< [ 23: 22](R/W) This signal indicates the share-ability domain of read and write transactions
                                                                 Used only if AXI4-ACE is supported */
        uint32_t rqos                  : 4;  /**< [ 27: 24](R/W) Read transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
        uint32_t wqos                  : 4;  /**< [ 31: 28](R/W) Write transaction Quality of Service, QoS.
                                                                 Used only if AXI4 is supported */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_addx_att0_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_addx_att0 bdk_cbpx_interfaceconfiguration_addx_att0_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=31)))
        return 0x87e044823524ll + 0x40000ll * ((a) & 0xf) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADDX_ATT0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(a,b) bdk_cbpx_interfaceconfiguration_addx_att0_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(a,b) "CBPX_INTERFACECONFIGURATION_ADDX_ATT0"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(a,b) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT0(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add#_att1
 *
 * CBP Interfaceconfiguration Add Att1 Register
 */
union bdk_cbpx_interfaceconfiguration_addx_att1
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_addx_att1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t l2a_nc_rd             : 4;  /**< [  8:  5](R/W) L2 Cache Policy for read accesses: (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t l2a_nc_wr             : 4;  /**< [  4:  1](R/W) L2 Cache Policy for write accesses: (AXI AWCACHE[3:0])
                                                                 0000              Device Non-bufferable
                                                                 0001              Device Bufferable
                                                                 0010              Normal Non-cacheable Non-bufferable
                                                                 0011              Normal Non-cacheable Bufferable
                                                                 0110              Write-through No-allocate
                                                                 0110             Write-through Read-allocate
                                                                 1110 (1010) Write-through Write-allocate
                                                                 1110              Write-through Read and Write-allocate
                                                                 0111              Write-back No-allocate
                                                                 0111             Write-back Read-allocate
                                                                 1111 (1011) Write-back Write-allocate
                                                                 1111              Write-back Read and Write-allocate */
        uint32_t exact_rd              : 1;  /**< [  0:  0](R/W) DDMA external port read transactions pursues exact read .
                                                                 DDMA pursues minimal cycle count resulting in possible over reading of data from
                                                                 the external address.
                                                                 DDMA pursues exact read resulting is possible additional read cycles on the external bus used. */
#else /* Word 0 - Little Endian */
        uint32_t exact_rd              : 1;  /**< [  0:  0](R/W) DDMA external port read transactions pursues exact read .
                                                                 DDMA pursues minimal cycle count resulting in possible over reading of data from
                                                                 the external address.
                                                                 DDMA pursues exact read resulting is possible additional read cycles on the external bus used. */
        uint32_t l2a_nc_wr             : 4;  /**< [  4:  1](R/W) L2 Cache Policy for write accesses: (AXI AWCACHE[3:0])
                                                                 0000              Device Non-bufferable
                                                                 0001              Device Bufferable
                                                                 0010              Normal Non-cacheable Non-bufferable
                                                                 0011              Normal Non-cacheable Bufferable
                                                                 0110              Write-through No-allocate
                                                                 0110             Write-through Read-allocate
                                                                 1110 (1010) Write-through Write-allocate
                                                                 1110              Write-through Read and Write-allocate
                                                                 0111              Write-back No-allocate
                                                                 0111             Write-back Read-allocate
                                                                 1111 (1011) Write-back Write-allocate
                                                                 1111              Write-back Read and Write-allocate */
        uint32_t l2a_nc_rd             : 4;  /**< [  8:  5](R/W) L2 Cache Policy for read accesses: (AXI ARCACHE[3:0])
                                                                 0000             Device Non-bufferable
                                                                 0001             Device Bufferable
                                                                 0010             Normal Non-cacheable Non-bufferable
                                                                 0011             Normal Non-cacheable Bufferable
                                                                 1010             Write-through No-allocate
                                                                 1110 (0110) Write-through Read-allocate
                                                                 1010             Write-through Write-allocate
                                                                 1110             Write-through Read and Write-allocate
                                                                 1011             Write-back No-allocate
                                                                 1111 (0111) Write-back Read-allocate
                                                                 1011             Write-back Write-allocate
                                                                 1111             Write-back Read and Write-allocate */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_addx_att1_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_addx_att1 bdk_cbpx_interfaceconfiguration_addx_att1_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=31)))
        return 0x87e044823528ll + 0x40000ll * ((a) & 0xf) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADDX_ATT1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(a,b) bdk_cbpx_interfaceconfiguration_addx_att1_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(a,b) "CBPX_INTERFACECONFIGURATION_ADDX_ATT1"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(a,b) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADDX_ATT1(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add0_start
 *
 * CBP Interfaceconfiguration Add0 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add0_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add0_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add0_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add0_start bdk_cbpx_interfaceconfiguration_add0_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823520ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD0_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(a) bdk_cbpx_interfaceconfiguration_add0_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(a) "CBPX_INTERFACECONFIGURATION_ADD0_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD0_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add10_start
 *
 * CBP Interfaceconfiguration Add10 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add10_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add10_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add10_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add10_start bdk_cbpx_interfaceconfiguration_add10_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235c0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD10_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(a) bdk_cbpx_interfaceconfiguration_add10_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(a) "CBPX_INTERFACECONFIGURATION_ADD10_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD10_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add11_start
 *
 * CBP Interfaceconfiguration Add11 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add11_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add11_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add11_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add11_start bdk_cbpx_interfaceconfiguration_add11_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235d0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD11_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(a) bdk_cbpx_interfaceconfiguration_add11_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(a) "CBPX_INTERFACECONFIGURATION_ADD11_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD11_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add12_start
 *
 * CBP Interfaceconfiguration Add12 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add12_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add12_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add12_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add12_start bdk_cbpx_interfaceconfiguration_add12_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235e0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD12_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(a) bdk_cbpx_interfaceconfiguration_add12_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(a) "CBPX_INTERFACECONFIGURATION_ADD12_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD12_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add13_start
 *
 * CBP Interfaceconfiguration Add13 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add13_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add13_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add13_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add13_start bdk_cbpx_interfaceconfiguration_add13_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235f0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD13_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(a) bdk_cbpx_interfaceconfiguration_add13_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(a) "CBPX_INTERFACECONFIGURATION_ADD13_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD13_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add14_start
 *
 * CBP Interfaceconfiguration Add14 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add14_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add14_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add14_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add14_start bdk_cbpx_interfaceconfiguration_add14_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823600ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD14_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(a) bdk_cbpx_interfaceconfiguration_add14_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(a) "CBPX_INTERFACECONFIGURATION_ADD14_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD14_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add15_start
 *
 * CBP Interfaceconfiguration Add15 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add15_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add15_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add15_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add15_start bdk_cbpx_interfaceconfiguration_add15_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823610ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD15_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(a) bdk_cbpx_interfaceconfiguration_add15_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(a) "CBPX_INTERFACECONFIGURATION_ADD15_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD15_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add16_start
 *
 * CBP Interfaceconfiguration Add16 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add16_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add16_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add16_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add16_start bdk_cbpx_interfaceconfiguration_add16_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823620ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD16_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(a) bdk_cbpx_interfaceconfiguration_add16_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(a) "CBPX_INTERFACECONFIGURATION_ADD16_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD16_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add17_start
 *
 * CBP Interfaceconfiguration Add17 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add17_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add17_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add17_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add17_start bdk_cbpx_interfaceconfiguration_add17_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823630ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD17_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(a) bdk_cbpx_interfaceconfiguration_add17_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(a) "CBPX_INTERFACECONFIGURATION_ADD17_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD17_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add18_start
 *
 * CBP Interfaceconfiguration Add18 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add18_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add18_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add18_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add18_start bdk_cbpx_interfaceconfiguration_add18_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823640ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD18_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(a) bdk_cbpx_interfaceconfiguration_add18_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(a) "CBPX_INTERFACECONFIGURATION_ADD18_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD18_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add19_start
 *
 * CBP Interfaceconfiguration Add19 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add19_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add19_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add19_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add19_start bdk_cbpx_interfaceconfiguration_add19_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823650ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD19_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(a) bdk_cbpx_interfaceconfiguration_add19_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(a) "CBPX_INTERFACECONFIGURATION_ADD19_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD19_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add1_start
 *
 * CBP Interfaceconfiguration Add1 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add1_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add1_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add1_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add1_start bdk_cbpx_interfaceconfiguration_add1_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823530ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD1_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(a) bdk_cbpx_interfaceconfiguration_add1_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(a) "CBPX_INTERFACECONFIGURATION_ADD1_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD1_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add20_start
 *
 * CBP Interfaceconfiguration Add20 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add20_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add20_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add20_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add20_start bdk_cbpx_interfaceconfiguration_add20_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823660ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD20_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(a) bdk_cbpx_interfaceconfiguration_add20_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(a) "CBPX_INTERFACECONFIGURATION_ADD20_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD20_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add21_start
 *
 * CBP Interfaceconfiguration Add21 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add21_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add21_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add21_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add21_start bdk_cbpx_interfaceconfiguration_add21_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823670ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD21_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(a) bdk_cbpx_interfaceconfiguration_add21_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(a) "CBPX_INTERFACECONFIGURATION_ADD21_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD21_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add22_start
 *
 * CBP Interfaceconfiguration Add22 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add22_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add22_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add22_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add22_start bdk_cbpx_interfaceconfiguration_add22_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823680ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD22_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(a) bdk_cbpx_interfaceconfiguration_add22_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(a) "CBPX_INTERFACECONFIGURATION_ADD22_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD22_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add23_start
 *
 * CBP Interfaceconfiguration Add23 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add23_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add23_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add23_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add23_start bdk_cbpx_interfaceconfiguration_add23_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823690ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD23_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(a) bdk_cbpx_interfaceconfiguration_add23_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(a) "CBPX_INTERFACECONFIGURATION_ADD23_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD23_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add24_start
 *
 * CBP Interfaceconfiguration Add24 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add24_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add24_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add24_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add24_start bdk_cbpx_interfaceconfiguration_add24_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236a0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD24_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(a) bdk_cbpx_interfaceconfiguration_add24_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(a) "CBPX_INTERFACECONFIGURATION_ADD24_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD24_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add25_start
 *
 * CBP Interfaceconfiguration Add25 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add25_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add25_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add25_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add25_start bdk_cbpx_interfaceconfiguration_add25_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236b0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD25_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(a) bdk_cbpx_interfaceconfiguration_add25_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(a) "CBPX_INTERFACECONFIGURATION_ADD25_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD25_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add26_start
 *
 * CBP Interfaceconfiguration Add26 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add26_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add26_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add26_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add26_start bdk_cbpx_interfaceconfiguration_add26_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236c0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD26_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(a) bdk_cbpx_interfaceconfiguration_add26_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(a) "CBPX_INTERFACECONFIGURATION_ADD26_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD26_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add27_start
 *
 * CBP Interfaceconfiguration Add27 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add27_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add27_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add27_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add27_start bdk_cbpx_interfaceconfiguration_add27_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236d0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD27_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(a) bdk_cbpx_interfaceconfiguration_add27_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(a) "CBPX_INTERFACECONFIGURATION_ADD27_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD27_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add28_start
 *
 * CBP Interfaceconfiguration Add28 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add28_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add28_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add28_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add28_start bdk_cbpx_interfaceconfiguration_add28_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236e0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD28_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(a) bdk_cbpx_interfaceconfiguration_add28_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(a) "CBPX_INTERFACECONFIGURATION_ADD28_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD28_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add29_start
 *
 * CBP Interfaceconfiguration Add29 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add29_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add29_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add29_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add29_start bdk_cbpx_interfaceconfiguration_add29_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448236f0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD29_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(a) bdk_cbpx_interfaceconfiguration_add29_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(a) "CBPX_INTERFACECONFIGURATION_ADD29_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD29_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add2_start
 *
 * CBP Interfaceconfiguration Add2 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add2_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add2_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add2_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add2_start bdk_cbpx_interfaceconfiguration_add2_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823540ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD2_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(a) bdk_cbpx_interfaceconfiguration_add2_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(a) "CBPX_INTERFACECONFIGURATION_ADD2_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD2_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add30_start
 *
 * CBP Interfaceconfiguration Add30 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add30_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add30_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add30_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add30_start bdk_cbpx_interfaceconfiguration_add30_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823700ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD30_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(a) bdk_cbpx_interfaceconfiguration_add30_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(a) "CBPX_INTERFACECONFIGURATION_ADD30_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD30_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add31_start
 *
 * CBP Interfaceconfiguration Add31 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add31_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add31_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add31_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add31_start bdk_cbpx_interfaceconfiguration_add31_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823710ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD31_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(a) bdk_cbpx_interfaceconfiguration_add31_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(a) "CBPX_INTERFACECONFIGURATION_ADD31_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD31_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add3_start
 *
 * CBP Interfaceconfiguration Add3 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add3_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add3_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add3_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add3_start bdk_cbpx_interfaceconfiguration_add3_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823550ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD3_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(a) bdk_cbpx_interfaceconfiguration_add3_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(a) "CBPX_INTERFACECONFIGURATION_ADD3_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD3_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add4_start
 *
 * CBP Interfaceconfiguration Add4 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add4_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add4_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add4_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add4_start bdk_cbpx_interfaceconfiguration_add4_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823560ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD4_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(a) bdk_cbpx_interfaceconfiguration_add4_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(a) "CBPX_INTERFACECONFIGURATION_ADD4_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD4_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add5_start
 *
 * CBP Interfaceconfiguration Add5 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add5_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add5_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add5_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add5_start bdk_cbpx_interfaceconfiguration_add5_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823570ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD5_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(a) bdk_cbpx_interfaceconfiguration_add5_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(a) "CBPX_INTERFACECONFIGURATION_ADD5_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD5_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add6_start
 *
 * CBP Interfaceconfiguration Add6 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add6_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add6_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add6_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add6_start bdk_cbpx_interfaceconfiguration_add6_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823580ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD6_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(a) bdk_cbpx_interfaceconfiguration_add6_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(a) "CBPX_INTERFACECONFIGURATION_ADD6_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD6_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add7_start
 *
 * CBP Interfaceconfiguration Add7 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add7_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add7_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add7_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add7_start bdk_cbpx_interfaceconfiguration_add7_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823590ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD7_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(a) bdk_cbpx_interfaceconfiguration_add7_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(a) "CBPX_INTERFACECONFIGURATION_ADD7_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD7_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add8_start
 *
 * CBP Interfaceconfiguration Add8 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add8_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add8_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add8_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add8_start bdk_cbpx_interfaceconfiguration_add8_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235a0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD8_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(a) bdk_cbpx_interfaceconfiguration_add8_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(a) "CBPX_INTERFACECONFIGURATION_ADD8_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD8_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_add9_start
 *
 * CBP Interfaceconfiguration Add9 Start Register
 */
union bdk_cbpx_interfaceconfiguration_add9_start
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_add9_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
#else /* Word 0 - Little Endian */
        uint32_t region_start          : 20; /**< [ 19:  0](R/W) 4KB start block of address region 0
                                                                 For ADD0_START This field is a read only and is hardcoded to the value of 0x0_0000 */
        uint32_t region_mid            : 8;  /**< [ 27: 20](R/W) Master  ID of region 0
                                                                 0x00  EDP
                                                                 0x11  FICM0
                                                                 0x22  FICM1
                                                                 0xFF  Blank region.
                                                                 All Others  Reserved */
        uint32_t inactive              : 1;  /**< [ 28: 28](R/W) Set if this region is not active
                                                                 0x0  this region is active
                                                                 0x1  this region is not active */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_add9_start_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_add9_start bdk_cbpx_interfaceconfiguration_add9_start_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448235b0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_ADD9_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(a) bdk_cbpx_interfaceconfiguration_add9_start_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(a) "CBPX_INTERFACECONFIGURATION_ADD9_START"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_ADD9_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_ficmr_cor
 *
 * CBP Interfaceconfiguration Ficmr Cor Register
 * Note:
 *         The user must ensure that STL_CNT0 and STL_CNT1 are properly configured
 * before FICM0 or FICM1 are used for performing read transactions.
 *         After initial configuration of the STL_CNT0 and STL_CNT1 the FIC buses do
 * not change structure and the user must not change the STL_CNT0 and STL_CNT1.
 */
union bdk_cbpx_interfaceconfiguration_ficmr_cor
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_ficmr_cor_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t stl_cnt1              : 5;  /**< [  9:  5](R/W) 16KByte address region crossing stall counter
                                                                 The FICM1 stops read transactions on the FIC read bus for STL_CNT1 cycles with
                                                                 ARREADY==1 plus one cycle when a 16KByte address region is crossed.
                                                                 Using STL_CNT1==0 the FICM1 port ignores 16KByte address region crossing (read
                                                                 accesses continues without stall). */
        uint32_t stl_cnt0              : 5;  /**< [  4:  0](R/W) 16KByte address region crossing stall counter
                                                                 The FICM0 stops read transactions on the FIC read bus for STL_CNT0 cycles with
                                                                 ARREADY==1 plus one cycle when a 16KByte address region is crossed.
                                                                 Using STL_CNT0==0 the FICM0 port ignores 16KByte address region crossing (read
                                                                 accesses continues without stall). */
#else /* Word 0 - Little Endian */
        uint32_t stl_cnt0              : 5;  /**< [  4:  0](R/W) 16KByte address region crossing stall counter
                                                                 The FICM0 stops read transactions on the FIC read bus for STL_CNT0 cycles with
                                                                 ARREADY==1 plus one cycle when a 16KByte address region is crossed.
                                                                 Using STL_CNT0==0 the FICM0 port ignores 16KByte address region crossing (read
                                                                 accesses continues without stall). */
        uint32_t stl_cnt1              : 5;  /**< [  9:  5](R/W) 16KByte address region crossing stall counter
                                                                 The FICM1 stops read transactions on the FIC read bus for STL_CNT1 cycles with
                                                                 ARREADY==1 plus one cycle when a 16KByte address region is crossed.
                                                                 Using STL_CNT1==0 the FICM1 port ignores 16KByte address region crossing (read
                                                                 accesses continues without stall). */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_ficmr_cor_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_ficmr_cor bdk_cbpx_interfaceconfiguration_ficmr_cor_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823508ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_FICMR_COR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(a) bdk_cbpx_interfaceconfiguration_ficmr_cor_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(a) "CBPX_INTERFACECONFIGURATION_FICMR_COR"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_FICMR_COR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_fics_cor
 *
 * CBP Interfaceconfiguration Fics Cor Register
 * Note:
 *         The DLY_PRMX (X denotes the number of slave port) field must be properly
 * configured to reflect the core to FIC bus clock ratio, before issuing read or write
 * transactions to the FIC slave port X.
 *         After initial configuration of DLY_PRMX the clock ratio of the FIC bus is
 * fixed and the value of DLY_PRMX must not change.
 * 	FIC slave port X must not be used for changing the value of DLY_PRMX.
 */
union bdk_cbpx_interfaceconfiguration_fics_cor
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_fics_cor_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t dly_prm7              : 2;  /**< [ 15: 14](R/W) Cycle count for FICS7.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm6              : 2;  /**< [ 13: 12](R/W) Cycle count for FICS6.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm5              : 2;  /**< [ 11: 10](R/W) Cycle count for FICS5.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm4              : 2;  /**< [  9:  8](R/W) Cycle count for FICS4.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm3              : 2;  /**< [  7:  6](R/W) Cycle count for FICS3.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm2              : 2;  /**< [  5:  4](R/W) Cycle count for FICS2.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm1              : 2;  /**< [  3:  2](R/W) Cycle count for FICS1.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm0              : 2;  /**< [  1:  0](R/W) Cycle count for FICS0.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
#else /* Word 0 - Little Endian */
        uint32_t dly_prm0              : 2;  /**< [  1:  0](R/W) Cycle count for FICS0.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm1              : 2;  /**< [  3:  2](R/W) Cycle count for FICS1.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm2              : 2;  /**< [  5:  4](R/W) Cycle count for FICS2.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm3              : 2;  /**< [  7:  6](R/W) Cycle count for FICS3.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm4              : 2;  /**< [  9:  8](R/W) Cycle count for FICS4.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm5              : 2;  /**< [ 11: 10](R/W) Cycle count for FICS5.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm6              : 2;  /**< [ 13: 12](R/W) Cycle count for FICS6.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t dly_prm7              : 2;  /**< [ 15: 14](R/W) Cycle count for FICS7.
                                                                 Delay parameter set for the FICS port.
                                                                 core:FIC clocks ratio ==1:1
                                                                 RVALID_DLY=6, ARREADY_DLY=4
                                                                 BVALID_DLY=5, AWREADY_DLY=4
                                                                 core:FIC clocks ration \>=2:1
                                                                 RVALID_DLY=4, ARREADY_DLY=3
                                                                 BVALID_DLY=4, AWREADY_DLY=3 */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_fics_cor_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_fics_cor bdk_cbpx_interfaceconfiguration_fics_cor_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823504ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_FICS_COR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(a) bdk_cbpx_interfaceconfiguration_fics_cor_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(a) "CBPX_INTERFACECONFIGURATION_FICS_COR"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_FICS_COR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_port_rid
 *
 * CBP Interfaceconfiguration Port Rid Register
 */
union bdk_cbpx_interfaceconfiguration_port_rid
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_port_rid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p_id                  : 4;  /**< [ 31: 28](R/W) Core program fetch Read ID */
        uint32_t pdma_id               : 4;  /**< [ 27: 24](R/W) PDMA Read ID */
        uint32_t qman_id               : 4;  /**< [ 23: 20](R/W) QMAN Read ID */
        uint32_t ddma_id               : 4;  /**< [ 19: 16](R/W) DDMA Read ID */
        uint32_t bfr_id                : 4;  /**< [ 15: 12](R/W) Cache line fill initiated by read or write , ID */
        uint32_t reserved_8_11         : 4;
        uint32_t ls1_id                : 4;  /**< [  7:  4](R/W) LS1 Read ID
                                                                 reserved
                                                                 11:8
                                                                 R/W
                                                                 reserved */
        uint32_t ls0_id                : 4;  /**< [  3:  0](R/W) LS0 Read ID */
#else /* Word 0 - Little Endian */
        uint32_t ls0_id                : 4;  /**< [  3:  0](R/W) LS0 Read ID */
        uint32_t ls1_id                : 4;  /**< [  7:  4](R/W) LS1 Read ID
                                                                 reserved
                                                                 11:8
                                                                 R/W
                                                                 reserved */
        uint32_t reserved_8_11         : 4;
        uint32_t bfr_id                : 4;  /**< [ 15: 12](R/W) Cache line fill initiated by read or write , ID */
        uint32_t ddma_id               : 4;  /**< [ 19: 16](R/W) DDMA Read ID */
        uint32_t qman_id               : 4;  /**< [ 23: 20](R/W) QMAN Read ID */
        uint32_t pdma_id               : 4;  /**< [ 27: 24](R/W) PDMA Read ID */
        uint32_t p_id                  : 4;  /**< [ 31: 28](R/W) Core program fetch Read ID */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_port_rid_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_port_rid bdk_cbpx_interfaceconfiguration_port_rid_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823930ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_PORT_RID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(a) bdk_cbpx_interfaceconfiguration_port_rid_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(a) "CBPX_INTERFACECONFIGURATION_PORT_RID"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_PORT_RID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_interfaceconfiguration_port_wid
 *
 * CBP Interfaceconfiguration Port Wid Register
 */
union bdk_cbpx_interfaceconfiguration_port_wid
{
    uint32_t u;
    struct bdk_cbpx_interfaceconfiguration_port_wid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocem_id               : 4;  /**< [ 31: 28](R/W) OCEM access Read and write ID */
        uint32_t reserved_24_27        : 4;
        uint32_t qman_wid              : 4;  /**< [ 23: 20](R/W) QMAN Write ID */
        uint32_t ddma_n_wid            : 4;  /**< [ 19: 16](R/W) DDMA Write ID when using WriteNoSnoop */
        uint32_t ewb_id                : 4;  /**< [ 15: 12](R/W) Eviction write buffer Write ID for all transaction except WriteNoSnoop */
        uint32_t ddma_u_wid            : 4;  /**< [ 11:  8](R/W) DDMA Write ID when using WriteUnique */
        uint32_t bar_id                : 4;  /**< [  7:  4](R/W) Barrier access Read and write ID */
        uint32_t wb_id                 : 4;  /**< [  3:  0](R/W) L1Write buffer Write ID, also use for Eviction write buffer when it uses WriteNoSnoop */
#else /* Word 0 - Little Endian */
        uint32_t wb_id                 : 4;  /**< [  3:  0](R/W) L1Write buffer Write ID, also use for Eviction write buffer when it uses WriteNoSnoop */
        uint32_t bar_id                : 4;  /**< [  7:  4](R/W) Barrier access Read and write ID */
        uint32_t ddma_u_wid            : 4;  /**< [ 11:  8](R/W) DDMA Write ID when using WriteUnique */
        uint32_t ewb_id                : 4;  /**< [ 15: 12](R/W) Eviction write buffer Write ID for all transaction except WriteNoSnoop */
        uint32_t ddma_n_wid            : 4;  /**< [ 19: 16](R/W) DDMA Write ID when using WriteNoSnoop */
        uint32_t qman_wid              : 4;  /**< [ 23: 20](R/W) QMAN Write ID */
        uint32_t reserved_24_27        : 4;
        uint32_t ocem_id               : 4;  /**< [ 31: 28](R/W) OCEM access Read and write ID */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_interfaceconfiguration_port_wid_s cn; */
};
typedef union bdk_cbpx_interfaceconfiguration_port_wid bdk_cbpx_interfaceconfiguration_port_wid_t;

static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823934ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_INTERFACECONFIGURATION_PORT_WID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(a) bdk_cbpx_interfaceconfiguration_port_wid_t
#define bustype_BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(a) "CBPX_INTERFACECONFIGURATION_PORT_WID"
#define busnum_BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(a) (a)
#define arguments_BDK_CBPX_INTERFACECONFIGURATION_PORT_WID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_lrua_lru_slt_hi
 *
 * CBP Lrua Lru Slt Hi Register
 */
union bdk_cbpx_lrua_lru_slt_hi
{
    uint32_t u;
    struct bdk_cbpx_lrua_lru_slt_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t slot11_reqm           : 4;  /**< [ 15: 12](R/W) Initial assignment to slot 11
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot10_reqm           : 4;  /**< [ 11:  8](R/W) Initial assignment to slot 10
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot9_reqm            : 4;  /**< [  7:  4](R/W) Initial assignment to slot 9
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot8_reqm            : 4;  /**< [  3:  0](R/W) Initial assignment to slot 8
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
#else /* Word 0 - Little Endian */
        uint32_t slot8_reqm            : 4;  /**< [  3:  0](R/W) Initial assignment to slot 8
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot9_reqm            : 4;  /**< [  7:  4](R/W) Initial assignment to slot 9
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot10_reqm           : 4;  /**< [ 11:  8](R/W) Initial assignment to slot 10
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot11_reqm           : 4;  /**< [ 15: 12](R/W) Initial assignment to slot 11
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_lrua_lru_slt_hi_s cn; */
};
typedef union bdk_cbpx_lrua_lru_slt_hi bdk_cbpx_lrua_lru_slt_hi_t;

static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_HI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448222a4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_LRUA_LRU_SLT_HI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_LRUA_LRU_SLT_HI(a) bdk_cbpx_lrua_lru_slt_hi_t
#define bustype_BDK_CBPX_LRUA_LRU_SLT_HI(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_LRUA_LRU_SLT_HI(a) "CBPX_LRUA_LRU_SLT_HI"
#define busnum_BDK_CBPX_LRUA_LRU_SLT_HI(a) (a)
#define arguments_BDK_CBPX_LRUA_LRU_SLT_HI(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_lrua_lru_slt_lo
 *
 * CBP Lrua Lru Slt Lo Register
 */
union bdk_cbpx_lrua_lru_slt_lo
{
    uint32_t u;
    struct bdk_cbpx_lrua_lru_slt_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t slot7_reqm            : 4;  /**< [ 31: 28](R/W) Initial assignment to slot 7
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot6_reqm            : 4;  /**< [ 27: 24](R/W) Initial assignment to slot 6
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot5_reqm            : 4;  /**< [ 23: 20](R/W) Initial assignment to slot 5
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot4_reqm            : 4;  /**< [ 19: 16](R/W) Initial assignment to slot 4
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot3_reqm            : 4;  /**< [ 15: 12](R/W) Initial assignment to slot 3
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot2_reqm            : 4;  /**< [ 11:  8](R/W) Initial assignment to slot 2
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot1_reqm            : 4;  /**< [  7:  4](R/W) Initial assignment to slot 1
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot0_reqm            : 4;  /**< [  3:  0](R/W) Initial assignment to slot 0
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
#else /* Word 0 - Little Endian */
        uint32_t slot0_reqm            : 4;  /**< [  3:  0](R/W) Initial assignment to slot 0
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot1_reqm            : 4;  /**< [  7:  4](R/W) Initial assignment to slot 1
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot2_reqm            : 4;  /**< [ 11:  8](R/W) Initial assignment to slot 2
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot3_reqm            : 4;  /**< [ 15: 12](R/W) Initial assignment to slot 3
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot4_reqm            : 4;  /**< [ 19: 16](R/W) Initial assignment to slot 4
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot5_reqm            : 4;  /**< [ 23: 20](R/W) Initial assignment to slot 5
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot6_reqm            : 4;  /**< [ 27: 24](R/W) Initial assignment to slot 6
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
        uint32_t slot7_reqm            : 4;  /**< [ 31: 28](R/W) Initial assignment to slot 7
                                                                 00 - DDMA requester
                                                                 01 - EDAP Read port requester
                                                                 02 - QMAN requester
                                                                 03 - FICS0 requester
                                                                 04 - FICS1 requester
                                                                 05 - FICS2 requester
                                                                 06 - FICS3 requester
                                                                 07 - FICS4 requester
                                                                 08 - FICS5 requester
                                                                 09 - FICS6 requester
                                                                 10 - FICS7 requester
                                                                 11 - EDAP Write port requester
                                                                 15:12      Reserved */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_lrua_lru_slt_lo_s cn; */
};
typedef union bdk_cbpx_lrua_lru_slt_lo bdk_cbpx_lrua_lru_slt_lo_t;

static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_LO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_LO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448222a0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_LRUA_LRU_SLT_LO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_LRUA_LRU_SLT_LO(a) bdk_cbpx_lrua_lru_slt_lo_t
#define bustype_BDK_CBPX_LRUA_LRU_SLT_LO(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_LRUA_LRU_SLT_LO(a) "CBPX_LRUA_LRU_SLT_LO"
#define busnum_BDK_CBPX_LRUA_LRU_SLT_LO(a) (a)
#define arguments_BDK_CBPX_LRUA_LRU_SLT_LO(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_lrua_lru_slt_pri
 *
 * CBP Lrua Lru Slt Pri Register
 */
union bdk_cbpx_lrua_lru_slt_pri
{
    uint32_t u;
    struct bdk_cbpx_lrua_lru_slt_pri_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t lru_rgion3_first_slot : 4;  /**< [ 11:  8](R/W) Number of lowest priority slot in LRUA priority region 3 */
        uint32_t lru_rgion2_first_slot : 4;  /**< [  7:  4](R/W) Number of lowest priority slot in LRUA priority region 2 */
        uint32_t lru_rgion1_first_slot : 4;  /**< [  3:  0](R/W) Number of lowest priority slot in LRUA priority region 1 */
#else /* Word 0 - Little Endian */
        uint32_t lru_rgion1_first_slot : 4;  /**< [  3:  0](R/W) Number of lowest priority slot in LRUA priority region 1 */
        uint32_t lru_rgion2_first_slot : 4;  /**< [  7:  4](R/W) Number of lowest priority slot in LRUA priority region 2 */
        uint32_t lru_rgion3_first_slot : 4;  /**< [ 11:  8](R/W) Number of lowest priority slot in LRUA priority region 3 */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_lrua_lru_slt_pri_s cn; */
};
typedef union bdk_cbpx_lrua_lru_slt_pri bdk_cbpx_lrua_lru_slt_pri_t;

static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_PRI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_LRUA_LRU_SLT_PRI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448222a8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_LRUA_LRU_SLT_PRI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_LRUA_LRU_SLT_PRI(a) bdk_cbpx_lrua_lru_slt_pri_t
#define bustype_BDK_CBPX_LRUA_LRU_SLT_PRI(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_LRUA_LRU_SLT_PRI(a) "CBPX_LRUA_LRU_SLT_PRI"
#define busnum_BDK_CBPX_LRUA_LRU_SLT_PRI(a) (a)
#define arguments_BDK_CBPX_LRUA_LRU_SLT_PRI(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_lrua_lru_weight_hi
 *
 * CBP Lrua Lru Weight Hi Register
 */
union bdk_cbpx_lrua_lru_weight_hi
{
    uint32_t u;
    struct bdk_cbpx_lrua_lru_weight_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_15_31        : 17;
        uint32_t edap_wr_weight        : 3;  /**< [ 14: 12](R/W) EDAP Write arbitration weight */
        uint32_t reserved_11           : 1;
        uint32_t fics7_weight          : 3;  /**< [ 10:  8](R/W) FICS7 arbitration weight */
        uint32_t reserved_7            : 1;
        uint32_t fics6_weight          : 3;  /**< [  6:  4](R/W) FICS6 arbitration weight */
        uint32_t reserved_3            : 1;
        uint32_t fics5_weight          : 3;  /**< [  2:  0](R/W) FICS5 arbitration weight */
#else /* Word 0 - Little Endian */
        uint32_t fics5_weight          : 3;  /**< [  2:  0](R/W) FICS5 arbitration weight */
        uint32_t reserved_3            : 1;
        uint32_t fics6_weight          : 3;  /**< [  6:  4](R/W) FICS6 arbitration weight */
        uint32_t reserved_7            : 1;
        uint32_t fics7_weight          : 3;  /**< [ 10:  8](R/W) FICS7 arbitration weight */
        uint32_t reserved_11           : 1;
        uint32_t edap_wr_weight        : 3;  /**< [ 14: 12](R/W) EDAP Write arbitration weight */
        uint32_t reserved_15_31        : 17;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_lrua_lru_weight_hi_s cn; */
};
typedef union bdk_cbpx_lrua_lru_weight_hi bdk_cbpx_lrua_lru_weight_hi_t;

static inline uint64_t BDK_CBPX_LRUA_LRU_WEIGHT_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_LRUA_LRU_WEIGHT_HI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448222b0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_LRUA_LRU_WEIGHT_HI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_LRUA_LRU_WEIGHT_HI(a) bdk_cbpx_lrua_lru_weight_hi_t
#define bustype_BDK_CBPX_LRUA_LRU_WEIGHT_HI(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_LRUA_LRU_WEIGHT_HI(a) "CBPX_LRUA_LRU_WEIGHT_HI"
#define busnum_BDK_CBPX_LRUA_LRU_WEIGHT_HI(a) (a)
#define arguments_BDK_CBPX_LRUA_LRU_WEIGHT_HI(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_lrua_lru_weight_lo
 *
 * CBP Lrua Lru Weight Lo Register
 */
union bdk_cbpx_lrua_lru_weight_lo
{
    uint32_t u;
    struct bdk_cbpx_lrua_lru_weight_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t fics4_weight          : 3;  /**< [ 30: 28](R/W) FICS4 arbitration weight */
        uint32_t reserved_27           : 1;
        uint32_t fics3_weight          : 3;  /**< [ 26: 24](R/W) FICS3 arbitration weight */
        uint32_t reserved_23           : 1;
        uint32_t fics2_weight          : 3;  /**< [ 22: 20](R/W) FICS2 arbitration weight */
        uint32_t reserved_19           : 1;
        uint32_t fics1_weight          : 3;  /**< [ 18: 16](R/W) FICS1 arbitration weight */
        uint32_t reserved_15           : 1;
        uint32_t fics0_weight          : 3;  /**< [ 14: 12](R/W) FICS0 arbitration weight */
        uint32_t reserved_11           : 1;
        uint32_t qman_weight           : 3;  /**< [ 10:  8](R/W) QMAN arbitration weight */
        uint32_t reserved_7            : 1;
        uint32_t edap_rd_weight        : 3;  /**< [  6:  4](R/W) EDAP Read arbitration weight */
        uint32_t reserved_3            : 1;
        uint32_t ddma_weight           : 3;  /**< [  2:  0](R/W) DDMA arbitration weight */
#else /* Word 0 - Little Endian */
        uint32_t ddma_weight           : 3;  /**< [  2:  0](R/W) DDMA arbitration weight */
        uint32_t reserved_3            : 1;
        uint32_t edap_rd_weight        : 3;  /**< [  6:  4](R/W) EDAP Read arbitration weight */
        uint32_t reserved_7            : 1;
        uint32_t qman_weight           : 3;  /**< [ 10:  8](R/W) QMAN arbitration weight */
        uint32_t reserved_11           : 1;
        uint32_t fics0_weight          : 3;  /**< [ 14: 12](R/W) FICS0 arbitration weight */
        uint32_t reserved_15           : 1;
        uint32_t fics1_weight          : 3;  /**< [ 18: 16](R/W) FICS1 arbitration weight */
        uint32_t reserved_19           : 1;
        uint32_t fics2_weight          : 3;  /**< [ 22: 20](R/W) FICS2 arbitration weight */
        uint32_t reserved_23           : 1;
        uint32_t fics3_weight          : 3;  /**< [ 26: 24](R/W) FICS3 arbitration weight */
        uint32_t reserved_27           : 1;
        uint32_t fics4_weight          : 3;  /**< [ 30: 28](R/W) FICS4 arbitration weight */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_lrua_lru_weight_lo_s cn; */
};
typedef union bdk_cbpx_lrua_lru_weight_lo bdk_cbpx_lrua_lru_weight_lo_t;

static inline uint64_t BDK_CBPX_LRUA_LRU_WEIGHT_LO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_LRUA_LRU_WEIGHT_LO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448222acll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_LRUA_LRU_WEIGHT_LO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_LRUA_LRU_WEIGHT_LO(a) bdk_cbpx_lrua_lru_weight_lo_t
#define bustype_BDK_CBPX_LRUA_LRU_WEIGHT_LO(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_LRUA_LRU_WEIGHT_LO(a) "CBPX_LRUA_LRU_WEIGHT_LO"
#define busnum_BDK_CBPX_LRUA_LRU_WEIGHT_LO(a) (a)
#define arguments_BDK_CBPX_LRUA_LRU_WEIGHT_LO(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_com_int_en
 *
 * CBP Multicoreconfiguration Com Int En Register
 */
union bdk_cbpx_multicoreconfiguration_com_int_en
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_com_int_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t com_int_en            : 32; /**< [ 31:  0](R/W) Interrupt masking COM_STS status indication; Each bit corresponds to COM_STS bit respectively.
                                                                 0: Masking.
                                                                 1: Enabling */
#else /* Word 0 - Little Endian */
        uint32_t com_int_en            : 32; /**< [ 31:  0](R/W) Interrupt masking COM_STS status indication; Each bit corresponds to COM_STS bit respectively.
                                                                 0: Masking.
                                                                 1: Enabling */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_com_int_en_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_com_int_en bdk_cbpx_multicoreconfiguration_com_int_en_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044820084ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_COM_INT_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(a) bdk_cbpx_multicoreconfiguration_com_int_en_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(a) "CBPX_MULTICORECONFIGURATION_COM_INT_EN"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(a) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_COM_INT_EN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_com_reg#
 *
 * CBP Multicoreconfiguration Com Reg Register
 * When accessing this register from slave port it is write-only
 */
union bdk_cbpx_multicoreconfiguration_com_regx
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_com_regx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t com_reg               : 32; /**< [ 31:  0](WO) Messaging memory register space (Command Registers)
                                                                 This register is write only when accessed through the EDAP or one of the FIC slave ports. */
#else /* Word 0 - Little Endian */
        uint32_t com_reg               : 32; /**< [ 31:  0](WO) Messaging memory register space (Command Registers)
                                                                 This register is write only when accessed through the EDAP or one of the FIC slave ports. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_com_regx_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_com_regx bdk_cbpx_multicoreconfiguration_com_regx_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=31)))
        return 0x87e044820000ll + 0x40000ll * ((a) & 0xf) + 4ll * ((b) & 0x1f);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_COM_REGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(a,b) bdk_cbpx_multicoreconfiguration_com_regx_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(a,b) "CBPX_MULTICORECONFIGURATION_COM_REGX"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(a,b) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_COM_REGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_com_sts
 *
 * CBP Multicoreconfiguration Com Sts Register
 * When accessing this register from slave port it is read-only
 */
union bdk_cbpx_multicoreconfiguration_com_sts
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_com_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t com_sts               : 32; /**< [ 31:  0](R/W/H) Write status COM_REG0-31 registers indication; Each bit corresponds to each
                                                                 COM_REG respectively (write indication to the command registers).
                                                                 Writing 1 to each bit clears its status indication.
                                                                 0: no write occurred (since the last time it was cleared/reset)
                                                                 1: COM register was written
                                                                 This register is read only when accessed through the EDAP or one of the FIC slave ports. */
#else /* Word 0 - Little Endian */
        uint32_t com_sts               : 32; /**< [ 31:  0](R/W/H) Write status COM_REG0-31 registers indication; Each bit corresponds to each
                                                                 COM_REG respectively (write indication to the command registers).
                                                                 Writing 1 to each bit clears its status indication.
                                                                 0: no write occurred (since the last time it was cleared/reset)
                                                                 1: COM register was written
                                                                 This register is read only when accessed through the EDAP or one of the FIC slave ports. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_com_sts_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_com_sts bdk_cbpx_multicoreconfiguration_com_sts_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_STS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_COM_STS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044820080ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_COM_STS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_COM_STS(a) bdk_cbpx_multicoreconfiguration_com_sts_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_COM_STS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_COM_STS(a) "CBPX_MULTICORECONFIGURATION_COM_STS"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_COM_STS(a) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_COM_STS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_snoop_csr
 *
 * CBP Multicoreconfiguration Snoop Csr Register
 */
union bdk_cbpx_multicoreconfiguration_snoop_csr
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_snoop_csr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t snoop_int_en          : 1;  /**< [  3:  3](R/W) Snooping detection interrupt enable
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t snoop_sts             : 1;  /**< [  2:  2](R/W/H) Snooping detection; Writing 0 clears this bit.
                                                                 0: No access
                                                                 1: IDM accessed */
        uint32_t snoop_rd_wr           : 2;  /**< [  1:  0](R/W) Snooping Read Write Access Type
                                                                 00: Snoop is disabled.
                                                                 01: Snoop RD is enabled.
                                                                 10: Snoop WR is enabled
                                                                 11: Snoop is enabled for both RD and WR. */
#else /* Word 0 - Little Endian */
        uint32_t snoop_rd_wr           : 2;  /**< [  1:  0](R/W) Snooping Read Write Access Type
                                                                 00: Snoop is disabled.
                                                                 01: Snoop RD is enabled.
                                                                 10: Snoop WR is enabled
                                                                 11: Snoop is enabled for both RD and WR. */
        uint32_t snoop_sts             : 1;  /**< [  2:  2](R/W/H) Snooping detection; Writing 0 clears this bit.
                                                                 0: No access
                                                                 1: IDM accessed */
        uint32_t snoop_int_en          : 1;  /**< [  3:  3](R/W) Snooping detection interrupt enable
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_snoop_csr_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_snoop_csr bdk_cbpx_multicoreconfiguration_snoop_csr_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044820098ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_SNOOP_CSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(a) bdk_cbpx_multicoreconfiguration_snoop_csr_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(a) "CBPX_MULTICORECONFIGURATION_SNOOP_CSR"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(a) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_SNOOP_CSR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_start_add
 *
 * CBP Multicoreconfiguration Start Add Register
 */
union bdk_cbpx_multicoreconfiguration_start_add
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_start_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_21_31        : 11;
        uint32_t start_add             : 21; /**< [ 20:  0](RO) IDM snooping base address range */
#else /* Word 0 - Little Endian */
        uint32_t start_add             : 21; /**< [ 20:  0](RO) IDM snooping base address range */
        uint32_t reserved_21_31        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_start_add_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_start_add bdk_cbpx_multicoreconfiguration_start_add_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_START_ADD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_START_ADD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044820090ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_START_ADD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_START_ADD(a) bdk_cbpx_multicoreconfiguration_start_add_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_START_ADD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_START_ADD(a) "CBPX_MULTICORECONFIGURATION_START_ADD"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_START_ADD(a) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_START_ADD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_multicoreconfiguration_top_add
 *
 * CBP Multicoreconfiguration Top Add Register
 */
union bdk_cbpx_multicoreconfiguration_top_add
{
    uint32_t u;
    struct bdk_cbpx_multicoreconfiguration_top_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_21_31        : 11;
        uint32_t top_add               : 21; /**< [ 20:  0](RO) IDM snooping top address range
                                                                 TOP_ADD must be configured with a value larger or equal to START_ADD. */
#else /* Word 0 - Little Endian */
        uint32_t top_add               : 21; /**< [ 20:  0](RO) IDM snooping top address range
                                                                 TOP_ADD must be configured with a value larger or equal to START_ADD. */
        uint32_t reserved_21_31        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_multicoreconfiguration_top_add_s cn; */
};
typedef union bdk_cbpx_multicoreconfiguration_top_add bdk_cbpx_multicoreconfiguration_top_add_t;

static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044820094ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_MULTICORECONFIGURATION_TOP_ADD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(a) bdk_cbpx_multicoreconfiguration_top_add_t
#define bustype_BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(a) "CBPX_MULTICORECONFIGURATION_TOP_ADD"
#define busnum_BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(a) (a)
#define arguments_BDK_CBPX_MULTICORECONFIGURATION_TOP_ADD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_bpcount_drd_ocm_acount
 *
 * CBP Ocem Bpcount Drd Ocm Acount Register
 */
union bdk_cbpx_ocem_bpcount_drd_ocm_acount
{
    uint32_t u;
    struct bdk_cbpx_ocem_bpcount_drd_ocm_acount_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t ocm_acount            : 16; /**< [ 15:  0](R/W) Data address breakpoint count value:
                                                                 Triggers a breakpoint once the data address breakpoint counter is equal to this
                                                                 value. After breakpoint is triggered the counter is cleared.
                                                                 In enhanced mode this count value is used for combined address and data breakpoints. */
#else /* Word 0 - Little Endian */
        uint32_t ocm_acount            : 16; /**< [ 15:  0](R/W) Data address breakpoint count value:
                                                                 Triggers a breakpoint once the data address breakpoint counter is equal to this
                                                                 value. After breakpoint is triggered the counter is cleared.
                                                                 In enhanced mode this count value is used for combined address and data breakpoints. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_bpcount_drd_ocm_acount_s cn; */
};
typedef union bdk_cbpx_ocem_bpcount_drd_ocm_acount bdk_cbpx_ocem_bpcount_drd_ocm_acount_t;

static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221f0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(a) bdk_cbpx_ocem_bpcount_drd_ocm_acount_t
#define bustype_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(a) "CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT"
#define busnum_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(a) (a)
#define arguments_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_ACOUNT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_bpcount_drd_ocm_dcount
 *
 * CBP Ocem Bpcount Drd Ocm Dcount Register
 */
union bdk_cbpx_ocem_bpcount_drd_ocm_dcount
{
    uint32_t u;
    struct bdk_cbpx_ocem_bpcount_drd_ocm_dcount_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t ocm_dcount            : 16; /**< [ 15:  0](R/W) Data value breakpoint count value (Enhanced mode only):
                                                                 Triggers a breakpoint once the data value breakpoint counter is equal to this
                                                                 value. After breakpoint is triggered the counter is cleared. */
#else /* Word 0 - Little Endian */
        uint32_t ocm_dcount            : 16; /**< [ 15:  0](R/W) Data value breakpoint count value (Enhanced mode only):
                                                                 Triggers a breakpoint once the data value breakpoint counter is equal to this
                                                                 value. After breakpoint is triggered the counter is cleared. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_bpcount_drd_ocm_dcount_s cn; */
};
typedef union bdk_cbpx_ocem_bpcount_drd_ocm_dcount bdk_cbpx_ocem_bpcount_drd_ocm_dcount_t;

static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221f4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(a) bdk_cbpx_ocem_bpcount_drd_ocm_dcount_t
#define bustype_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(a) "CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT"
#define busnum_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(a) (a)
#define arguments_BDK_CBPX_OCEM_BPCOUNT_DRD_OCM_DCOUNT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_bpcount_drd_ocore_drd
 *
 * CBP Ocem Bpcount Drd Ocore Drd Register
 * The OCORE_DRD register is written whenever the address 0xFC is used regardless of
 * the iopage field in mod2 register
 * Note: This register is write-only. The host can read the value written to this
 * register by reading scan chain 0x9F.
 */
union bdk_cbpx_ocem_bpcount_drd_ocore_drd
{
    uint32_t u;
    struct bdk_cbpx_ocem_bpcount_drd_ocore_drd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocore_drd             : 32; /**< [ 31:  0](R/W) Output core data read register
                                                                 The OCORE_DRD register is used by the core software to pass values to the debugger. */
#else /* Word 0 - Little Endian */
        uint32_t ocore_drd             : 32; /**< [ 31:  0](R/W) Output core data read register
                                                                 The OCORE_DRD register is used by the core software to pass values to the debugger. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_bpcount_drd_ocore_drd_s cn; */
};
typedef union bdk_cbpx_ocem_bpcount_drd_ocore_drd bdk_cbpx_ocem_bpcount_drd_ocore_drd_t;

static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221fcll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(a) bdk_cbpx_ocem_bpcount_drd_ocore_drd_t
#define bustype_BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(a) "CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD"
#define busnum_BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(a) (a)
#define arguments_BDK_CBPX_OCEM_BPCOUNT_DRD_OCORE_DRD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_cevax_d3_pc
 *
 * CBP Ocem Cevax D3 Pc Register
 */
union bdk_cbpx_ocem_cevax_d3_pc
{
    uint32_t u;
    struct bdk_cbpx_ocem_cevax_d3_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ceva_d3_pc            : 32; /**< [ 31:  0](RO) PC of the D3 stage
                                                                 This register is read only */
#else /* Word 0 - Little Endian */
        uint32_t ceva_d3_pc            : 32; /**< [ 31:  0](RO) PC of the D3 stage
                                                                 This register is read only */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_cevax_d3_pc_s cn; */
};
typedef union bdk_cbpx_ocem_cevax_d3_pc bdk_cbpx_ocem_cevax_d3_pc_t;

static inline uint64_t BDK_CBPX_OCEM_CEVAX_D3_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_CEVAX_D3_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822134ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_CEVAX_D3_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_CEVAX_D3_PC(a) bdk_cbpx_ocem_cevax_d3_pc_t
#define bustype_BDK_CBPX_OCEM_CEVAX_D3_PC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_CEVAX_D3_PC(a) "CBPX_OCEM_CEVAX_D3_PC"
#define busnum_BDK_CBPX_OCEM_CEVAX_D3_PC(a) (a)
#define arguments_BDK_CBPX_OCEM_CEVAX_D3_PC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_core_config
 *
 * CBP Ocem Core Config Register
 */
union bdk_cbpx_ocem_core_config
{
    uint32_t u;
    struct bdk_cbpx_ocem_core_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t desprdr               : 1;  /**< [ 31: 31](RO) De-spreader configuration
                                                                 1 = De-spreader included
                                                                 0 = De-spreader not included */
        uint32_t ocem_conf             : 1;  /**< [ 30: 30](RO) OCEM Configuration
                                                                 1 = Enhanced Configuration
                                                                 0 = Basic Configuration */
        uint32_t fpu                   : 1;  /**< [ 29: 29](RO) Floating Point configuration:
                                                                 1 = Floating Point included
                                                                 0 = Floating Point not included */
        uint32_t ecc                   : 2;  /**< [ 28: 27](RO) Error Correction Code (ECC) configuration:
                                                                 00 = disabled
                                                                 01 = enabled with 16-bit ECC
                                                                 10 = enabled with 32-bit ECC.
                                                                 11 = Reserved */
        uint32_t reserved_26           : 1;
        uint32_t etm                   : 2;  /**< [ 25: 24](RO) ETM configuration trace
                                                                 2b00 = No ETM
                                                                 2b01 = Internal ETM
                                                                 2b10 = External ETM */
        uint32_t pflp                  : 1;  /**< [ 23: 23](RO) Pseudo Floating Point configuration
                                                                 1 = Pseudo Floating Point included
                                                                 0 = Pseudo Floating Point not included */
        uint32_t long_mult             : 1;  /**< [ 22: 22](RO) 32X32 Long multiplier operations configuration
                                                                 1 = 32X32 Long multiplier included
                                                                 0 = 32X32 Long multiplier not included LONG */
        uint32_t dmss_blk              : 2;  /**< [ 21: 20](RO) Number of DMSS blocks
                                                                 2b00 = reserved
                                                                 2b01 = 4 blocks
                                                                 2b10 = Reserved
                                                                 2b11 = 8 blocks */
        uint32_t demapper              : 1;  /**< [ 19: 19](RO) De-Mapper configuration:
                                                                 1 = De-Mapper included
                                                                 0 = De-Mapper not included */
        uint32_t dmem_tcm_size         : 3;  /**< [ 18: 16](RO) Data memory TCM size
                                                                 3b000 = Reserved
                                                                 3b001 = 128 KB
                                                                 3b010 = Reserved
                                                                 3b011 = 256 KB
                                                                 3b100 = 512 KB
                                                                 3b101 = 1024 KB */
        uint32_t reserved_15           : 1;
        uint32_t dcache                : 1;  /**< [ 14: 14](RO) Data cache configuration
                                                                 1 = cache included
                                                                 0 = cache not included */
        uint32_t fft                   : 1;  /**< [ 13: 13](RO) FFT configuration
                                                                 1 = FFT included
                                                                 0 = FFT not included */
        uint32_t reserved_11_12        : 2;
        uint32_t pmem_tcm_size         : 3;  /**< [ 10:  8](RO) Program memory TCM size
                                                                               3b000 = 32 KB
                                                                               3b001 = 64 KB
                                                                               3b010 = 128 KB
                                                                               3b011 = 256 KB
                                                                               3b100 = 512 KB
                                                                               3b101 = 1024 KB */
        uint32_t mem_pwr               : 1;  /**< [  7:  7](RO) Use memories with power gating
                                                                 1 = used
                                                                 0 = not used */
        uint32_t div_sqrt              : 2;  /**< [  6:  5](RO) Number of DivSqrt units configuration:
                                                                 2b00 = Reserved
                                                                 2b01 = 4
                                                                 2b10 = 8
                                                                 2b11 = Reserved */
        uint32_t profiler              : 1;  /**< [  4:  4](RO) Profiler configuration:
                                                                 1 = Profiler included
                                                                 0 = Profiler not included */
        uint32_t viterbi               : 1;  /**< [  3:  3](RO) Viterbi configuration:
                                                                 1 = viterbi included
                                                                 0 = viterbi not included */
        uint32_t vcu_xtend             : 1;  /**< [  2:  2](RO) CEVA-Xtend VCU hardware configuration:
                                                                 1 = CEVA-Xtend VCU hardware present
                                                                 0 = CEVA-Xtend VCU hardware not present */
        uint32_t vcu_num               : 2;  /**< [  1:  0](RO) Number of Vector Units
                                                                 2b00 = One VCU
                                                                 2b01 = Two VCUs
                                                                 2b10 = Reserved
                                                                 2b11 = Four VCUs */
#else /* Word 0 - Little Endian */
        uint32_t vcu_num               : 2;  /**< [  1:  0](RO) Number of Vector Units
                                                                 2b00 = One VCU
                                                                 2b01 = Two VCUs
                                                                 2b10 = Reserved
                                                                 2b11 = Four VCUs */
        uint32_t vcu_xtend             : 1;  /**< [  2:  2](RO) CEVA-Xtend VCU hardware configuration:
                                                                 1 = CEVA-Xtend VCU hardware present
                                                                 0 = CEVA-Xtend VCU hardware not present */
        uint32_t viterbi               : 1;  /**< [  3:  3](RO) Viterbi configuration:
                                                                 1 = viterbi included
                                                                 0 = viterbi not included */
        uint32_t profiler              : 1;  /**< [  4:  4](RO) Profiler configuration:
                                                                 1 = Profiler included
                                                                 0 = Profiler not included */
        uint32_t div_sqrt              : 2;  /**< [  6:  5](RO) Number of DivSqrt units configuration:
                                                                 2b00 = Reserved
                                                                 2b01 = 4
                                                                 2b10 = 8
                                                                 2b11 = Reserved */
        uint32_t mem_pwr               : 1;  /**< [  7:  7](RO) Use memories with power gating
                                                                 1 = used
                                                                 0 = not used */
        uint32_t pmem_tcm_size         : 3;  /**< [ 10:  8](RO) Program memory TCM size
                                                                               3b000 = 32 KB
                                                                               3b001 = 64 KB
                                                                               3b010 = 128 KB
                                                                               3b011 = 256 KB
                                                                               3b100 = 512 KB
                                                                               3b101 = 1024 KB */
        uint32_t reserved_11_12        : 2;
        uint32_t fft                   : 1;  /**< [ 13: 13](RO) FFT configuration
                                                                 1 = FFT included
                                                                 0 = FFT not included */
        uint32_t dcache                : 1;  /**< [ 14: 14](RO) Data cache configuration
                                                                 1 = cache included
                                                                 0 = cache not included */
        uint32_t reserved_15           : 1;
        uint32_t dmem_tcm_size         : 3;  /**< [ 18: 16](RO) Data memory TCM size
                                                                 3b000 = Reserved
                                                                 3b001 = 128 KB
                                                                 3b010 = Reserved
                                                                 3b011 = 256 KB
                                                                 3b100 = 512 KB
                                                                 3b101 = 1024 KB */
        uint32_t demapper              : 1;  /**< [ 19: 19](RO) De-Mapper configuration:
                                                                 1 = De-Mapper included
                                                                 0 = De-Mapper not included */
        uint32_t dmss_blk              : 2;  /**< [ 21: 20](RO) Number of DMSS blocks
                                                                 2b00 = reserved
                                                                 2b01 = 4 blocks
                                                                 2b10 = Reserved
                                                                 2b11 = 8 blocks */
        uint32_t long_mult             : 1;  /**< [ 22: 22](RO) 32X32 Long multiplier operations configuration
                                                                 1 = 32X32 Long multiplier included
                                                                 0 = 32X32 Long multiplier not included LONG */
        uint32_t pflp                  : 1;  /**< [ 23: 23](RO) Pseudo Floating Point configuration
                                                                 1 = Pseudo Floating Point included
                                                                 0 = Pseudo Floating Point not included */
        uint32_t etm                   : 2;  /**< [ 25: 24](RO) ETM configuration trace
                                                                 2b00 = No ETM
                                                                 2b01 = Internal ETM
                                                                 2b10 = External ETM */
        uint32_t reserved_26           : 1;
        uint32_t ecc                   : 2;  /**< [ 28: 27](RO) Error Correction Code (ECC) configuration:
                                                                 00 = disabled
                                                                 01 = enabled with 16-bit ECC
                                                                 10 = enabled with 32-bit ECC.
                                                                 11 = Reserved */
        uint32_t fpu                   : 1;  /**< [ 29: 29](RO) Floating Point configuration:
                                                                 1 = Floating Point included
                                                                 0 = Floating Point not included */
        uint32_t ocem_conf             : 1;  /**< [ 30: 30](RO) OCEM Configuration
                                                                 1 = Enhanced Configuration
                                                                 0 = Basic Configuration */
        uint32_t desprdr               : 1;  /**< [ 31: 31](RO) De-spreader configuration
                                                                 1 = De-spreader included
                                                                 0 = De-spreader not included */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_core_config_s cn; */
};
typedef union bdk_cbpx_ocem_core_config bdk_cbpx_ocem_core_config_t;

static inline uint64_t BDK_CBPX_OCEM_CORE_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_CORE_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482217cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_CORE_CONFIG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_CORE_CONFIG(a) bdk_cbpx_ocem_core_config_t
#define bustype_BDK_CBPX_OCEM_CORE_CONFIG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_CORE_CONFIG(a) "CBPX_OCEM_CORE_CONFIG"
#define busnum_BDK_CBPX_OCEM_CORE_CONFIG(a) (a)
#define arguments_BDK_CBPX_OCEM_CORE_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_core_id
 *
 * CBP Ocem Core Id Register
 */
union bdk_cbpx_ocem_core_id
{
    uint32_t u;
    struct bdk_cbpx_ocem_core_id_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t core_id               : 32; /**< [ 31:  0](RO/H) The value of this register is sampled at reset from the core_id input bus.
                                                                 This register is read only.
                                                                 For EDAP or FICSR ports the CORE_ID register can be  accessed using address 0x40_1004 . */
#else /* Word 0 - Little Endian */
        uint32_t core_id               : 32; /**< [ 31:  0](RO/H) The value of this register is sampled at reset from the core_id input bus.
                                                                 This register is read only.
                                                                 For EDAP or FICSR ports the CORE_ID register can be  accessed using address 0x40_1004 . */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_core_id_s cn; */
};
typedef union bdk_cbpx_ocem_core_id bdk_cbpx_ocem_core_id_t;

static inline uint64_t BDK_CBPX_OCEM_CORE_ID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_CORE_ID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822178ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_CORE_ID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_CORE_ID(a) bdk_cbpx_ocem_core_id_t
#define bustype_BDK_CBPX_OCEM_CORE_ID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_CORE_ID(a) "CBPX_OCEM_CORE_ID"
#define busnum_BDK_CBPX_OCEM_CORE_ID(a) (a)
#define arguments_BDK_CBPX_OCEM_CORE_ID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_core_version
 *
 * CBP Ocem Core Version Register
 */
union bdk_cbpx_ocem_core_version
{
    uint32_t u;
    struct bdk_cbpx_ocem_core_version_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t core_version          : 32; /**< [ 31:  0](RO) Bits [31:16]: DSP core type
                                                                 Reset value: Core Version.
                                                                 Bits [15:4] : DSP RTL version
                                                                 Reset value: RTL version
                                                                 For example for version v2.0.0 this field contains 0x200.
                                                                 Bits [3:0] : DSP RTL revision
                                                                 Reset value: RTL revision
                                                                 Preliminary revisions contain ascending values: preliminary revision 0 contains
                                                                 the value 0x0, preliminary revision 1 contains the value 0x1, preliminary
                                                                 revision 2 contains the value 0x2, etc. The final revision contains the value
                                                                 0xF.

                                                                 This register is read only.
                                                                 This register Can be read via the OCEM chain 0x72.
                                                                 For EDAP or FICSR ports the CORE_VERSION register can be accessed using address 0x401000. */
#else /* Word 0 - Little Endian */
        uint32_t core_version          : 32; /**< [ 31:  0](RO) Bits [31:16]: DSP core type
                                                                 Reset value: Core Version.
                                                                 Bits [15:4] : DSP RTL version
                                                                 Reset value: RTL version
                                                                 For example for version v2.0.0 this field contains 0x200.
                                                                 Bits [3:0] : DSP RTL revision
                                                                 Reset value: RTL revision
                                                                 Preliminary revisions contain ascending values: preliminary revision 0 contains
                                                                 the value 0x0, preliminary revision 1 contains the value 0x1, preliminary
                                                                 revision 2 contains the value 0x2, etc. The final revision contains the value
                                                                 0xF.

                                                                 This register is read only.
                                                                 This register Can be read via the OCEM chain 0x72.
                                                                 For EDAP or FICSR ports the CORE_VERSION register can be accessed using address 0x401000. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_core_version_s cn; */
};
typedef union bdk_cbpx_ocem_core_version bdk_cbpx_ocem_core_version_t;

static inline uint64_t BDK_CBPX_OCEM_CORE_VERSION(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_CORE_VERSION(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822174ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_CORE_VERSION", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_CORE_VERSION(a) bdk_cbpx_ocem_core_version_t
#define bustype_BDK_CBPX_OCEM_CORE_VERSION(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_CORE_VERSION(a) "CBPX_OCEM_CORE_VERSION"
#define busnum_BDK_CBPX_OCEM_CORE_VERSION(a) (a)
#define arguments_BDK_CBPX_OCEM_CORE_VERSION(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ficm_config
 *
 * CBP Ocem Ficm Config Register
 */
union bdk_cbpx_ocem_ficm_config
{
    uint32_t u;
    struct bdk_cbpx_ocem_ficm_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ficm_width            : 3;  /**< [  2:  0](RO) Width of FIC master
                                                                 000  port is disabled
                                                                 001   Reserved
                                                                 010  128 bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved */
#else /* Word 0 - Little Endian */
        uint32_t ficm_width            : 3;  /**< [  2:  0](RO) Width of FIC master
                                                                 000  port is disabled
                                                                 001   Reserved
                                                                 010  128 bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ficm_config_s cn; */
};
typedef union bdk_cbpx_ocem_ficm_config bdk_cbpx_ocem_ficm_config_t;

static inline uint64_t BDK_CBPX_OCEM_FICM_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_FICM_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822168ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_FICM_CONFIG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_FICM_CONFIG(a) bdk_cbpx_ocem_ficm_config_t
#define bustype_BDK_CBPX_OCEM_FICM_CONFIG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_FICM_CONFIG(a) "CBPX_OCEM_FICM_CONFIG"
#define busnum_BDK_CBPX_OCEM_FICM_CONFIG(a) (a)
#define arguments_BDK_CBPX_OCEM_FICM_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_fics_config
 *
 * CBP Ocem Fics Config Register
 */
union bdk_cbpx_ocem_fics_config
{
    uint32_t u;
    struct bdk_cbpx_ocem_fics_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t fics7_width           : 3;  /**< [ 30: 28](RO) Width of FIC slave port 7
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_27           : 1;
        uint32_t fics6_width           : 3;  /**< [ 26: 24](RO) Width of FIC slave port 6
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_23           : 1;
        uint32_t fics5_width           : 3;  /**< [ 22: 20](RO) Width of FIC slave port 5
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_19           : 1;
        uint32_t fics4_width           : 3;  /**< [ 18: 16](RO) Width of FIC slave port 4
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_15           : 1;
        uint32_t fics3_width           : 3;  /**< [ 14: 12](RO) Width of FIC slave port 3
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_11           : 1;
        uint32_t fics2_width           : 3;  /**< [ 10:  8](RO) Width of FIC slave port 2
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_7            : 1;
        uint32_t fics1_width           : 3;  /**< [  6:  4](RO) Width of FIC slave port 1
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_3            : 1;
        uint32_t fics0_width           : 3;  /**< [  2:  0](RO) Width of FIC slave port 0
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
#else /* Word 0 - Little Endian */
        uint32_t fics0_width           : 3;  /**< [  2:  0](RO) Width of FIC slave port 0
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_3            : 1;
        uint32_t fics1_width           : 3;  /**< [  6:  4](RO) Width of FIC slave port 1
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_7            : 1;
        uint32_t fics2_width           : 3;  /**< [ 10:  8](RO) Width of FIC slave port 2
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_11           : 1;
        uint32_t fics3_width           : 3;  /**< [ 14: 12](RO) Width of FIC slave port 3
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_15           : 1;
        uint32_t fics4_width           : 3;  /**< [ 18: 16](RO) Width of FIC slave port 4
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_19           : 1;
        uint32_t fics5_width           : 3;  /**< [ 22: 20](RO) Width of FIC slave port 5
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_23           : 1;
        uint32_t fics6_width           : 3;  /**< [ 26: 24](RO) Width of FIC slave port 6
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_27           : 1;
        uint32_t fics7_width           : 3;  /**< [ 30: 28](RO) Width of FIC slave port 7
                                                                 000  port is disabled
                                                                 001 -  Reserved
                                                                 010  128bit
                                                                 011  256 bit
                                                                 100  512 bit
                                                                 101  Reserved
                                                                 110  reserved
                                                                 111 - reserved */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_fics_config_s cn; */
};
typedef union bdk_cbpx_ocem_fics_config bdk_cbpx_ocem_fics_config_t;

static inline uint64_t BDK_CBPX_OCEM_FICS_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_FICS_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482216cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_FICS_CONFIG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_FICS_CONFIG(a) bdk_cbpx_ocem_fics_config_t
#define bustype_BDK_CBPX_OCEM_FICS_CONFIG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_FICS_CONFIG(a) "CBPX_OCEM_FICS_CONFIG"
#define busnum_BDK_CBPX_OCEM_FICS_CONFIG(a) (a)
#define arguments_BDK_CBPX_OCEM_FICS_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_mss_config
 *
 * CBP Ocem Mss Config Register
 */
union bdk_cbpx_ocem_mss_config
{
    uint32_t u;
    struct bdk_cbpx_ocem_mss_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_13_31        : 19;
        uint32_t num_bman              : 5;  /**< [ 12:  8](RO) Number of available hardware Buffer Managers
                                                                 00100  4 BMANs
                                                                 01000  8 BMANs
                                                                 01100  12 BMANs
                                                                 10000  16 BMANs
                                                                 11000  24 BMANs
                                                                 All other values  reserved. */
        uint32_t reserved_4_7          : 4;
        uint32_t num_qman              : 4;  /**< [  3:  0](RO) Number of available hardware Queue Managers
                                                                 0100  4 QMANs
                                                                 1000  8 QMANs
                                                                 1100  12 QMANs
                                                                 All other values  reserved. */
#else /* Word 0 - Little Endian */
        uint32_t num_qman              : 4;  /**< [  3:  0](RO) Number of available hardware Queue Managers
                                                                 0100  4 QMANs
                                                                 1000  8 QMANs
                                                                 1100  12 QMANs
                                                                 All other values  reserved. */
        uint32_t reserved_4_7          : 4;
        uint32_t num_bman              : 5;  /**< [ 12:  8](RO) Number of available hardware Buffer Managers
                                                                 00100  4 BMANs
                                                                 01000  8 BMANs
                                                                 01100  12 BMANs
                                                                 10000  16 BMANs
                                                                 11000  24 BMANs
                                                                 All other values  reserved. */
        uint32_t reserved_13_31        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_mss_config_s cn; */
};
typedef union bdk_cbpx_ocem_mss_config bdk_cbpx_ocem_mss_config_t;

static inline uint64_t BDK_CBPX_OCEM_MSS_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_MSS_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482215cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_MSS_CONFIG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_MSS_CONFIG(a) bdk_cbpx_ocem_mss_config_t
#define bustype_BDK_CBPX_OCEM_MSS_CONFIG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_MSS_CONFIG(a) "CBPX_OCEM_MSS_CONFIG"
#define busnum_BDK_CBPX_OCEM_MSS_CONFIG(a) (a)
#define arguments_BDK_CBPX_OCEM_MSS_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_control
 *
 * CBP Ocem Ocm Control Register
 */
union bdk_cbpx_ocem_ocm_control
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t auto_clk_num          : 4;  /**< [ 27: 24](R/W) The number of clocks to apply during auto-clock mode */
        uint32_t boot_mask             : 1;  /**< [ 23: 23](R/W) Control the boot wake up after OCEM  reset the core */
        uint32_t tag_val_clr           : 1;  /**< [ 22: 22](R/W) When set, causes the tag memory valid bit to be cleared when performing an access to the tag memory */
        uint32_t auto_clk              : 1;  /**< [ 21: 21](R/W) Auto clock mode enable bit (when set, enables auto clock mode) */
        uint32_t rst_status            : 1;  /**< [ 20: 20](WO) When written with 1, clears all the status bits */
        uint32_t reserved_18_19        : 2;
        uint32_t dvm_type              : 2;  /**< [ 17: 16](R/W) Width of the data value inserted in the DVM:
                                                                 2b00: byte
                                                                 2b01: word
                                                                 2b10: double word */
        uint32_t gp_out                : 4;  /**< [ 15: 12](R/W) General purpose outputs */
        uint32_t reserved_8_11         : 4;
        uint32_t padd_inc              : 1;  /**< [  7:  7](R/W) Program address increment enable: enables the address auto increment mode for
                                                                 program memory access. */
        uint32_t step                  : 1;  /**< [  6:  6](WO) Single step: setting this bit activates single stepping */
        uint32_t stop_go               : 1;  /**< [  5:  5](WO) Stop/go: setting this bit causes the OCEM to generate a breakpoint signal to the
                                                                 core. This is effective only during normal operation. When in debug mode,
                                                                 clearing this bit resumes normal operation, i.e. exits debug mode. Writing one
                                                                 to this bit while in debug mode has no effect. */
        uint32_t trape_en              : 1;  /**< [  4:  4](R/W) When set, enables the OCEM to enter debug mode for trape instructions */
        uint32_t mss_rst               : 1;  /**< [  3:  3](WO) When set, activates a reset to the Memory Sub System */
        uint32_t core_rst              : 1;  /**< [  2:  2](WO) When set, activates a core reset */
        uint32_t bp_detect_en          : 1;  /**< [  1:  1](R/W) When set, enables breakpoint detection (enables the FFs that sample the core interface buses) */
        uint32_t debug_enable          : 1;  /**< [  0:  0](R/W) When set, enables the OCEM to enter debug mode (i.e., activate the wait signal
                                                                 and the debug indication) */
#else /* Word 0 - Little Endian */
        uint32_t debug_enable          : 1;  /**< [  0:  0](R/W) When set, enables the OCEM to enter debug mode (i.e., activate the wait signal
                                                                 and the debug indication) */
        uint32_t bp_detect_en          : 1;  /**< [  1:  1](R/W) When set, enables breakpoint detection (enables the FFs that sample the core interface buses) */
        uint32_t core_rst              : 1;  /**< [  2:  2](WO) When set, activates a core reset */
        uint32_t mss_rst               : 1;  /**< [  3:  3](WO) When set, activates a reset to the Memory Sub System */
        uint32_t trape_en              : 1;  /**< [  4:  4](R/W) When set, enables the OCEM to enter debug mode for trape instructions */
        uint32_t stop_go               : 1;  /**< [  5:  5](WO) Stop/go: setting this bit causes the OCEM to generate a breakpoint signal to the
                                                                 core. This is effective only during normal operation. When in debug mode,
                                                                 clearing this bit resumes normal operation, i.e. exits debug mode. Writing one
                                                                 to this bit while in debug mode has no effect. */
        uint32_t step                  : 1;  /**< [  6:  6](WO) Single step: setting this bit activates single stepping */
        uint32_t padd_inc              : 1;  /**< [  7:  7](R/W) Program address increment enable: enables the address auto increment mode for
                                                                 program memory access. */
        uint32_t reserved_8_11         : 4;
        uint32_t gp_out                : 4;  /**< [ 15: 12](R/W) General purpose outputs */
        uint32_t dvm_type              : 2;  /**< [ 17: 16](R/W) Width of the data value inserted in the DVM:
                                                                 2b00: byte
                                                                 2b01: word
                                                                 2b10: double word */
        uint32_t reserved_18_19        : 2;
        uint32_t rst_status            : 1;  /**< [ 20: 20](WO) When written with 1, clears all the status bits */
        uint32_t auto_clk              : 1;  /**< [ 21: 21](R/W) Auto clock mode enable bit (when set, enables auto clock mode) */
        uint32_t tag_val_clr           : 1;  /**< [ 22: 22](R/W) When set, causes the tag memory valid bit to be cleared when performing an access to the tag memory */
        uint32_t boot_mask             : 1;  /**< [ 23: 23](R/W) Control the boot wake up after OCEM  reset the core */
        uint32_t auto_clk_num          : 4;  /**< [ 27: 24](R/W) The number of clocks to apply during auto-clock mode */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_control_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_control bdk_cbpx_ocem_ocm_control_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_CONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_CONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822150ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_CONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_CONTROL(a) bdk_cbpx_ocem_ocm_control_t
#define bustype_BDK_CBPX_OCEM_OCM_CONTROL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_CONTROL(a) "CBPX_OCEM_OCM_CONTROL"
#define busnum_BDK_CBPX_OCEM_OCM_CONTROL(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_CONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_dadd_high
 *
 * CBP Ocem Ocm Dadd High Register
 */
union bdk_cbpx_ocem_ocm_dadd_high
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_dadd_high_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_dadd_high         : 32; /**< [ 31:  0](R/W) Data address breakpoint higher address:
                                                                 This register represents the upper boundary of the data address range. */
#else /* Word 0 - Little Endian */
        uint32_t ocm_dadd_high         : 32; /**< [ 31:  0](R/W) Data address breakpoint higher address:
                                                                 This register represents the upper boundary of the data address range. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_dadd_high_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_dadd_high bdk_cbpx_ocem_ocm_dadd_high_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_DADD_HIGH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_DADD_HIGH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822140ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_DADD_HIGH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_DADD_HIGH(a) bdk_cbpx_ocem_ocm_dadd_high_t
#define bustype_BDK_CBPX_OCEM_OCM_DADD_HIGH(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_DADD_HIGH(a) "CBPX_OCEM_OCM_DADD_HIGH"
#define busnum_BDK_CBPX_OCEM_OCM_DADD_HIGH(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_DADD_HIGH(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_dadd_low
 *
 * CBP Ocem Ocm Dadd Low Register
 */
union bdk_cbpx_ocem_ocm_dadd_low
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_dadd_low_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_dadd_low          : 32; /**< [ 31:  0](R/W) Data address breakpoint lower address:
                                                                 This register represents the lower boundary of the data address range. */
#else /* Word 0 - Little Endian */
        uint32_t ocm_dadd_low          : 32; /**< [ 31:  0](R/W) Data address breakpoint lower address:
                                                                 This register represents the lower boundary of the data address range. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_dadd_low_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_dadd_low bdk_cbpx_ocem_ocm_dadd_low_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_DADD_LOW(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_DADD_LOW(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822130ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_DADD_LOW", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_DADD_LOW(a) bdk_cbpx_ocem_ocm_dadd_low_t
#define bustype_BDK_CBPX_OCEM_OCM_DADD_LOW(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_DADD_LOW(a) "CBPX_OCEM_OCM_DADD_LOW"
#define busnum_BDK_CBPX_OCEM_OCM_DADD_LOW(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_DADD_LOW(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_dvm
 *
 * CBP Ocem Ocm Dvm Register
 */
union bdk_cbpx_ocem_ocm_dvm
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_dvm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_dvm               : 32; /**< [ 31:  0](R/W) Data value match register (Enhanced mode only):
                                                                 Increments breakpoint counters when stored data matches this value. This
                                                                 register is coupled with the OCM_DCOUNT register. */
#else /* Word 0 - Little Endian */
        uint32_t ocm_dvm               : 32; /**< [ 31:  0](R/W) Data value match register (Enhanced mode only):
                                                                 Increments breakpoint counters when stored data matches this value. This
                                                                 register is coupled with the OCM_DCOUNT register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_dvm_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_dvm bdk_cbpx_ocem_ocm_dvm_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_DVM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_DVM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822104ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_DVM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_DVM(a) bdk_cbpx_ocem_ocm_dvm_t
#define bustype_BDK_CBPX_OCEM_OCM_DVM(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_DVM(a) "CBPX_OCEM_OCM_DVM"
#define busnum_BDK_CBPX_OCEM_OCM_DVM(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_DVM(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio1
 *
 * CBP Ocem Ocm Ofio1 Register
 */
union bdk_cbpx_ocem_ocm_ofio1
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio1             : 32; /**< [ 31:  0](R/W) File I/O #1 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio1             : 32; /**< [ 31:  0](R/W) File I/O #1 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio1_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio1 bdk_cbpx_ocem_ocm_ofio1_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822118ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO1(a) bdk_cbpx_ocem_ocm_ofio1_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO1(a) "CBPX_OCEM_OCM_OFIO1"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO1(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio2
 *
 * CBP Ocem Ocm Ofio2 Register
 */
union bdk_cbpx_ocem_ocm_ofio2
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio2             : 32; /**< [ 31:  0](R/W) File I/O #2 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio2             : 32; /**< [ 31:  0](R/W) File I/O #2 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio2_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio2 bdk_cbpx_ocem_ocm_ofio2_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482211cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO2(a) bdk_cbpx_ocem_ocm_ofio2_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO2(a) "CBPX_OCEM_OCM_OFIO2"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO2(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio3
 *
 * CBP Ocem Ocm Ofio3 Register
 */
union bdk_cbpx_ocem_ocm_ofio3
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio3             : 32; /**< [ 31:  0](R/W) File I/O #3 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio3             : 32; /**< [ 31:  0](R/W) File I/O #3 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio3_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio3 bdk_cbpx_ocem_ocm_ofio3_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822128ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO3(a) bdk_cbpx_ocem_ocm_ofio3_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO3(a) "CBPX_OCEM_OCM_OFIO3"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO3(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio4
 *
 * CBP Ocem Ocm Ofio4 Register
 */
union bdk_cbpx_ocem_ocm_ofio4
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio4             : 32; /**< [ 31:  0](R/W) File I/O #4 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio4             : 32; /**< [ 31:  0](R/W) File I/O #4 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio4_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio4 bdk_cbpx_ocem_ocm_ofio4_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482212cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO4(a) bdk_cbpx_ocem_ocm_ofio4_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO4(a) "CBPX_OCEM_OCM_OFIO4"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO4(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio5
 *
 * CBP Ocem Ocm Ofio5 Register
 */
union bdk_cbpx_ocem_ocm_ofio5
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio5             : 32; /**< [ 31:  0](R/W) File I/O #5 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio5             : 32; /**< [ 31:  0](R/W) File I/O #5 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio5_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio5 bdk_cbpx_ocem_ocm_ofio5_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822138ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO5(a) bdk_cbpx_ocem_ocm_ofio5_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO5(a) "CBPX_OCEM_OCM_OFIO5"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO5(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio6
 *
 * CBP Ocem Ocm Ofio6 Register
 */
union bdk_cbpx_ocem_ocm_ofio6
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio6             : 32; /**< [ 31:  0](R/W) File I/O #6 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio6             : 32; /**< [ 31:  0](R/W) File I/O #6 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio6_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio6 bdk_cbpx_ocem_ocm_ofio6_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482213cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO6(a) bdk_cbpx_ocem_ocm_ofio6_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO6(a) "CBPX_OCEM_OCM_OFIO6"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO6(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio7
 *
 * CBP Ocem Ocm Ofio7 Register
 */
union bdk_cbpx_ocem_ocm_ofio7
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio7             : 32; /**< [ 31:  0](R/W) File I/O #7 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio7             : 32; /**< [ 31:  0](R/W) File I/O #7 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio7_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio7 bdk_cbpx_ocem_ocm_ofio7_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822148ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO7(a) bdk_cbpx_ocem_ocm_ofio7_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO7(a) "CBPX_OCEM_OCM_OFIO7"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO7(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio7p
 *
 * CBP Ocem Ocm Ofio7p Register
 */
union bdk_cbpx_ocem_ocm_ofio7p
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio7p_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio7p            : 32; /**< [ 31:  0](RO) "File I/O #7 register
                                                                 A shadow register for read only access to the OCM_OFIO7 Register (offset 0x148).
                                                                 This register is mainly used when the host wishes to read the OCM_OFIO7 register
                                                                 through the JTAG scan chain without changing its value (read only)." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio7p            : 32; /**< [ 31:  0](RO) "File I/O #7 register
                                                                 A shadow register for read only access to the OCM_OFIO7 Register (offset 0x148).
                                                                 This register is mainly used when the host wishes to read the OCM_OFIO7 register
                                                                 through the JTAG scan chain without changing its value (read only)." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio7p_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio7p bdk_cbpx_ocem_ocm_ofio7p_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO7P(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO7P(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822108ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO7P", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO7P(a) bdk_cbpx_ocem_ocm_ofio7p_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO7P(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO7P(a) "CBPX_OCEM_OCM_OFIO7P"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO7P(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO7P(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio8
 *
 * CBP Ocem Ocm Ofio8 Register
 */
union bdk_cbpx_ocem_ocm_ofio8
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio8             : 32; /**< [ 31:  0](R/W) File I/O #8 register */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio8             : 32; /**< [ 31:  0](R/W) File I/O #8 register */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio8_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio8 bdk_cbpx_ocem_ocm_ofio8_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482214cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO8(a) bdk_cbpx_ocem_ocm_ofio8_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO8(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO8(a) "CBPX_OCEM_OCM_OFIO8"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO8(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO8(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_ofio8p
 *
 * CBP Ocem Ocm Ofio8p Register
 */
union bdk_cbpx_ocem_ocm_ofio8p
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_ofio8p_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_ofio8p            : 32; /**< [ 31:  0](RO) "File I/O #8 register
                                                                 A shadow register for read only access to the OCM_OFIO8 Register (offset 0x14C).
                                                                 This register is mainly used when the host wishes to read the OCM_OFIO8 register
                                                                 through the JTAG scan chain without changing its value (read only)." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_ofio8p            : 32; /**< [ 31:  0](RO) "File I/O #8 register
                                                                 A shadow register for read only access to the OCM_OFIO8 Register (offset 0x14C).
                                                                 This register is mainly used when the host wishes to read the OCM_OFIO8 register
                                                                 through the JTAG scan chain without changing its value (read only)." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_ofio8p_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_ofio8p bdk_cbpx_ocem_ocm_ofio8p_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO8P(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_OFIO8P(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482210cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_OFIO8P", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_OFIO8P(a) bdk_cbpx_ocem_ocm_ofio8p_t
#define bustype_BDK_CBPX_OCEM_OCM_OFIO8P(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_OFIO8P(a) "CBPX_OCEM_OCM_OFIO8P"
#define busnum_BDK_CBPX_OCEM_OCM_OFIO8P(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_OFIO8P(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_padd1
 *
 * CBP Ocem Ocm Padd1 Register
 */
union bdk_cbpx_ocem_ocm_padd1
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_padd1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_padd1             : 32; /**< [ 31:  0](R/W) "Program address breakpoint  #1 value:
                                                                 Increments the breakpoint counter when program counter matches this value. This
                                                                 register is coupled with the OCM_PCOUNT1 register." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_padd1             : 32; /**< [ 31:  0](R/W) "Program address breakpoint  #1 value:
                                                                 Increments the breakpoint counter when program counter matches this value. This
                                                                 register is coupled with the OCM_PCOUNT1 register." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_padd1_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_padd1 bdk_cbpx_ocem_ocm_padd1_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_PADD1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_PADD1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822110ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_PADD1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_PADD1(a) bdk_cbpx_ocem_ocm_padd1_t
#define bustype_BDK_CBPX_OCEM_OCM_PADD1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_PADD1(a) "CBPX_OCEM_OCM_PADD1"
#define busnum_BDK_CBPX_OCEM_OCM_PADD1(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_PADD1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_padd2
 *
 * CBP Ocem Ocm Padd2 Register
 */
union bdk_cbpx_ocem_ocm_padd2
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_padd2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_padd2             : 32; /**< [ 31:  0](R/W) "Program address breakpoint  #2 value:
                                                                 Increments the breakpoint counter when program counter matches this value. This
                                                                 register is coupled with the OCM_PCOUNT2 register." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_padd2             : 32; /**< [ 31:  0](R/W) "Program address breakpoint  #2 value:
                                                                 Increments the breakpoint counter when program counter matches this value. This
                                                                 register is coupled with the OCM_PCOUNT2 register." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_padd2_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_padd2 bdk_cbpx_ocem_ocm_padd2_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_PADD2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_PADD2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822114ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_PADD2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_PADD2(a) bdk_cbpx_ocem_ocm_padd2_t
#define bustype_BDK_CBPX_OCEM_OCM_PADD2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_PADD2(a) "CBPX_OCEM_OCM_PADD2"
#define busnum_BDK_CBPX_OCEM_OCM_PADD2(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_PADD2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_pcount1
 *
 * CBP Ocem Ocm Pcount1 Register
 */
union bdk_cbpx_ocem_ocm_pcount1
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_pcount1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_pcount1           : 32; /**< [ 31:  0](R/W) "Program address breakpoint #1 count value:
                                                                 Triggers a breakpoint and is cleared once the OCM_PADD1 breakpoint counter is equal to this value." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_pcount1           : 32; /**< [ 31:  0](R/W) "Program address breakpoint #1 count value:
                                                                 Triggers a breakpoint and is cleared once the OCM_PADD1 breakpoint counter is equal to this value." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_pcount1_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_pcount1 bdk_cbpx_ocem_ocm_pcount1_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_PCOUNT1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_PCOUNT1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822120ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_PCOUNT1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_PCOUNT1(a) bdk_cbpx_ocem_ocm_pcount1_t
#define bustype_BDK_CBPX_OCEM_OCM_PCOUNT1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_PCOUNT1(a) "CBPX_OCEM_OCM_PCOUNT1"
#define busnum_BDK_CBPX_OCEM_OCM_PCOUNT1(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_PCOUNT1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_pcount2
 *
 * CBP Ocem Ocm Pcount2 Register
 */
union bdk_cbpx_ocem_ocm_pcount2
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_pcount2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ocm_pcount2           : 32; /**< [ 31:  0](R/W) "Program address breakpoint #2 count value:
                                                                 Triggers a breakpoint and is cleared once the OCM_PADD2 breakpoint counter is equal to this value." */
#else /* Word 0 - Little Endian */
        uint32_t ocm_pcount2           : 32; /**< [ 31:  0](R/W) "Program address breakpoint #2 count value:
                                                                 Triggers a breakpoint and is cleared once the OCM_PADD2 breakpoint counter is equal to this value." */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_pcount2_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_pcount2 bdk_cbpx_ocem_ocm_pcount2_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_PCOUNT2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_PCOUNT2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822124ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_PCOUNT2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_PCOUNT2(a) bdk_cbpx_ocem_ocm_pcount2_t
#define bustype_BDK_CBPX_OCEM_OCM_PCOUNT2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_PCOUNT2(a) "CBPX_OCEM_OCM_PCOUNT2"
#define busnum_BDK_CBPX_OCEM_OCM_PCOUNT2(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_PCOUNT2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_sa_bp_en
 *
 * CBP Ocem Ocm Sa Bp En Register
 * Note:
 * 	For all breakpoints: 0: breakpoint is disabled, 1: breakpoint enabled.
 *         When enabling read and write breakpoints together the breakpoint counter
 * will increment for both accesses.
 */
union bdk_cbpx_ocem_ocm_sa_bp_en
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_sa_bp_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t sa_comb_wr            : 1;  /**< [ 19: 19](R/W) Enable  combined data address and data value match BP, write access (Enhanced mode only) */
        uint32_t sa_comb_rd            : 1;  /**< [ 18: 18](R/W) Enable  combined data address and data value match BP, read access (Enhanced mode only) */
        uint32_t reserved_17           : 1;
        uint32_t sa_dvm                : 1;  /**< [ 16: 16](R/W) Enable data value match breakpoint (Enhanced mode only) */
        uint32_t reserved_15           : 1;
        uint32_t co_d_en               : 1;  /**< [ 14: 14](R/W) Enable data breakpoint counter */
        uint32_t co_a_en               : 1;  /**< [ 13: 13](R/W) Enable address breakpoint counter */
        uint32_t sa_da_wr              : 1;  /**< [ 12: 12](R/W) Enable data address breakpoint for write access */
        uint32_t reserved_9_11         : 3;
        uint32_t sa_da_rd              : 1;  /**< [  8:  8](R/W) Enable data address breakpoint for read access */
        uint32_t reserved_6_7          : 2;
        uint32_t sa_pa                 : 2;  /**< [  5:  4](R/W) Enable program address breakpoints 2-1 respectively:
                                                                 Bit5: SA_PA2
                                                                 Bit4: SA_PA1 */
        uint32_t dma_da_e              : 1;  /**< [  3:  3](RO) Enable breakpoint for DMA request */
        uint32_t reserved_2            : 1;
        uint32_t sa_ext                : 2;  /**< [  1:  0](R/W) Enable breakpoint for external request 2-1 respectively:
                                                                 Bit1: SA_EXT2
                                                                 Bit0: SA_EXT1 */
#else /* Word 0 - Little Endian */
        uint32_t sa_ext                : 2;  /**< [  1:  0](R/W) Enable breakpoint for external request 2-1 respectively:
                                                                 Bit1: SA_EXT2
                                                                 Bit0: SA_EXT1 */
        uint32_t reserved_2            : 1;
        uint32_t dma_da_e              : 1;  /**< [  3:  3](RO) Enable breakpoint for DMA request */
        uint32_t sa_pa                 : 2;  /**< [  5:  4](R/W) Enable program address breakpoints 2-1 respectively:
                                                                 Bit5: SA_PA2
                                                                 Bit4: SA_PA1 */
        uint32_t reserved_6_7          : 2;
        uint32_t sa_da_rd              : 1;  /**< [  8:  8](R/W) Enable data address breakpoint for read access */
        uint32_t reserved_9_11         : 3;
        uint32_t sa_da_wr              : 1;  /**< [ 12: 12](R/W) Enable data address breakpoint for write access */
        uint32_t co_a_en               : 1;  /**< [ 13: 13](R/W) Enable address breakpoint counter */
        uint32_t co_d_en               : 1;  /**< [ 14: 14](R/W) Enable data breakpoint counter */
        uint32_t reserved_15           : 1;
        uint32_t sa_dvm                : 1;  /**< [ 16: 16](R/W) Enable data value match breakpoint (Enhanced mode only) */
        uint32_t reserved_17           : 1;
        uint32_t sa_comb_rd            : 1;  /**< [ 18: 18](R/W) Enable  combined data address and data value match BP, read access (Enhanced mode only) */
        uint32_t sa_comb_wr            : 1;  /**< [ 19: 19](R/W) Enable  combined data address and data value match BP, write access (Enhanced mode only) */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_sa_bp_en_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_sa_bp_en bdk_cbpx_ocem_ocm_sa_bp_en_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_SA_BP_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_SA_BP_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822154ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_SA_BP_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_SA_BP_EN(a) bdk_cbpx_ocem_ocm_sa_bp_en_t
#define bustype_BDK_CBPX_OCEM_OCM_SA_BP_EN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_SA_BP_EN(a) "CBPX_OCEM_OCM_SA_BP_EN"
#define busnum_BDK_CBPX_OCEM_OCM_SA_BP_EN(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_SA_BP_EN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_sa_bp_st
 *
 * CBP Ocem Ocm Sa Bp St Register
 * For all breakpoints: 0: breakpoint not accepted, 1: breakpoint accepted
 * 	When enabling read and write breakpoints together, only the last access will set the status bit.
 */
union bdk_cbpx_ocem_ocm_sa_bp_st
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_sa_bp_st_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t sa_comb_wr_st         : 1;  /**< [ 19: 19](RO/H) Status of combined data address and data value match breakpoint
                                                                 write access (Enhanced mode only) */
        uint32_t sa_comb_rd_st         : 1;  /**< [ 18: 18](RO/H) Status of combined data address and data value match breakpoint
                                                                 read access (Enhanced mode only) */
        uint32_t reserved_17           : 1;
        uint32_t sa_dvm_st             : 1;  /**< [ 16: 16](RO/H) Status of  data value match breakpoint (Enhanced mode only) */
        uint32_t reserved_13_15        : 3;
        uint32_t sa_da_wr_st           : 1;  /**< [ 12: 12](RO/H) Status of data address breakpoint for write access */
        uint32_t reserved_9_11         : 3;
        uint32_t sa_da_rd_st           : 1;  /**< [  8:  8](RO/H) Status of data address breakpoint for read access */
        uint32_t reserved_6_7          : 2;
        uint32_t sa_pa_st              : 2;  /**< [  5:  4](RO/H) Program address breakpoint status:
                                                                 Bit5: SA_PA2
                                                                 Bit4: SA_PA1 */
        uint32_t dma_da_st             : 1;  /**< [  3:  3](RO/H) Status of DMA data address match breakpoint */
        uint32_t reserved_2            : 1;
        uint32_t sa_ext_st             : 2;  /**< [  1:  0](RO/H) Breakpoint status for external request 2-1 respectively:
                                                                 Bit1: SA_EXT2
                                                                 Bit0: SA_EXT1 */
#else /* Word 0 - Little Endian */
        uint32_t sa_ext_st             : 2;  /**< [  1:  0](RO/H) Breakpoint status for external request 2-1 respectively:
                                                                 Bit1: SA_EXT2
                                                                 Bit0: SA_EXT1 */
        uint32_t reserved_2            : 1;
        uint32_t dma_da_st             : 1;  /**< [  3:  3](RO/H) Status of DMA data address match breakpoint */
        uint32_t sa_pa_st              : 2;  /**< [  5:  4](RO/H) Program address breakpoint status:
                                                                 Bit5: SA_PA2
                                                                 Bit4: SA_PA1 */
        uint32_t reserved_6_7          : 2;
        uint32_t sa_da_rd_st           : 1;  /**< [  8:  8](RO/H) Status of data address breakpoint for read access */
        uint32_t reserved_9_11         : 3;
        uint32_t sa_da_wr_st           : 1;  /**< [ 12: 12](RO/H) Status of data address breakpoint for write access */
        uint32_t reserved_13_15        : 3;
        uint32_t sa_dvm_st             : 1;  /**< [ 16: 16](RO/H) Status of  data value match breakpoint (Enhanced mode only) */
        uint32_t reserved_17           : 1;
        uint32_t sa_comb_rd_st         : 1;  /**< [ 18: 18](RO/H) Status of combined data address and data value match breakpoint
                                                                 read access (Enhanced mode only) */
        uint32_t sa_comb_wr_st         : 1;  /**< [ 19: 19](RO/H) Status of combined data address and data value match breakpoint
                                                                 write access (Enhanced mode only) */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_sa_bp_st_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_sa_bp_st bdk_cbpx_ocem_ocm_sa_bp_st_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_SA_BP_ST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_SA_BP_ST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822164ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_SA_BP_ST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_SA_BP_ST(a) bdk_cbpx_ocem_ocm_sa_bp_st_t
#define bustype_BDK_CBPX_OCEM_OCM_SA_BP_ST(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_SA_BP_ST(a) "CBPX_OCEM_OCM_SA_BP_ST"
#define busnum_BDK_CBPX_OCEM_OCM_SA_BP_ST(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_SA_BP_ST(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_ocem_ocm_status
 *
 * CBP Ocem Ocm Status Register
 * Note: All the status bits are cleared when the debugger reads the status register.
 * This functionality enables the debugger to identify multiple occurrences of the
 * events that these status bits reflect, within the same debug session. They are also
 * cleared when the debug session ends.
 */
union bdk_cbpx_ocem_ocm_status
{
    uint32_t u;
    struct bdk_cbpx_ocem_ocm_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t snoop_idle            : 1;  /**< [ 19: 19](RO/H) Indicates that there are no ongoing SNOOP is in MSS */
        uint32_t wait_f                : 1;  /**< [ 18: 18](RO/H) Indicates that the core is in wait */
        uint32_t axi_dmm_wr            : 1;  /**< [ 17: 17](RO/H) Indicates that the external Data memory write request was confirmed by the AXI
                                                                 * */
        uint32_t axi_pmm_wr            : 1;  /**< [ 16: 16](RO/H) Indicates that the external Program memory write request was confirmed by the AXI
                                                                 * */
        uint32_t reserved_15           : 1;
        uint32_t ocem_wait_f           : 1;  /**< [ 14: 14](RO/H) Wait initiated by the OCEM after branch to self */
        uint32_t dmss_idle_ocem        : 1;  /**< [ 13: 13](RO/H) Indicates all memory access are complete and memory access can be performed using the OCEM.
                                                                 This bit is set when:
                                                                 Write buffer is empty
                                                                 EDP has no pending read or write transactions
                                                                 FICM0 has no pending read or write transactions
                                                                 FICM1 has no pending read or write transactions
                                                                 EPP has no pending read or write transactions */
        uint32_t dactive_trans         : 1;  /**< [ 12: 12](RO/H) External data memory active-transaction indication
                                                                 * */
        uint32_t reserved_10_11        : 2;
        uint32_t pdma_active           : 1;  /**< [  9:  9](RO/H) The Program external port is occupied by the PDMA */
        uint32_t trape_inst            : 1;  /**< [  8:  8](RO) Debug mode was entered due to a trape instruction */
        uint32_t pactive_trans         : 1;  /**< [  7:  7](RO/H) External program memory active-transaction indication */
        uint32_t clk_applied           : 1;  /**< [  6:  6](RO/H) Indicates that the total number of clock cycles that the debugger requested were
                                                                 applied by the OCEM */
        uint32_t q_flush               : 1;  /**< [  5:  5](RO/H) Indicates that the queue is empty (flushed) */
        uint32_t pmem_ext_wr           : 1;  /**< [  4:  4](RO/H) Indicates that the external program memory was written (by any master) */
        uint32_t pmem_b1_wr            : 1;  /**< [  3:  3](RO/H) Indicates that block1 of the internal program memory was written */
        uint32_t pmem_b0_wr            : 1;  /**< [  2:  2](RO/H) Indicates that block0 of the internal program memory was written */
        uint32_t rst_dur_dbg           : 1;  /**< [  1:  1](RO/H) Indicates that there was a user reset during the debug session */
        uint32_t dbg_mode              : 1;  /**< [  0:  0](RO/H) Indicates that the OCEM is in debug mode (a breakpoint was accepted) */
#else /* Word 0 - Little Endian */
        uint32_t dbg_mode              : 1;  /**< [  0:  0](RO/H) Indicates that the OCEM is in debug mode (a breakpoint was accepted) */
        uint32_t rst_dur_dbg           : 1;  /**< [  1:  1](RO/H) Indicates that there was a user reset during the debug session */
        uint32_t pmem_b0_wr            : 1;  /**< [  2:  2](RO/H) Indicates that block0 of the internal program memory was written */
        uint32_t pmem_b1_wr            : 1;  /**< [  3:  3](RO/H) Indicates that block1 of the internal program memory was written */
        uint32_t pmem_ext_wr           : 1;  /**< [  4:  4](RO/H) Indicates that the external program memory was written (by any master) */
        uint32_t q_flush               : 1;  /**< [  5:  5](RO/H) Indicates that the queue is empty (flushed) */
        uint32_t clk_applied           : 1;  /**< [  6:  6](RO/H) Indicates that the total number of clock cycles that the debugger requested were
                                                                 applied by the OCEM */
        uint32_t pactive_trans         : 1;  /**< [  7:  7](RO/H) External program memory active-transaction indication */
        uint32_t trape_inst            : 1;  /**< [  8:  8](RO) Debug mode was entered due to a trape instruction */
        uint32_t pdma_active           : 1;  /**< [  9:  9](RO/H) The Program external port is occupied by the PDMA */
        uint32_t reserved_10_11        : 2;
        uint32_t dactive_trans         : 1;  /**< [ 12: 12](RO/H) External data memory active-transaction indication
                                                                 * */
        uint32_t dmss_idle_ocem        : 1;  /**< [ 13: 13](RO/H) Indicates all memory access are complete and memory access can be performed using the OCEM.
                                                                 This bit is set when:
                                                                 Write buffer is empty
                                                                 EDP has no pending read or write transactions
                                                                 FICM0 has no pending read or write transactions
                                                                 FICM1 has no pending read or write transactions
                                                                 EPP has no pending read or write transactions */
        uint32_t ocem_wait_f           : 1;  /**< [ 14: 14](RO/H) Wait initiated by the OCEM after branch to self */
        uint32_t reserved_15           : 1;
        uint32_t axi_pmm_wr            : 1;  /**< [ 16: 16](RO/H) Indicates that the external Program memory write request was confirmed by the AXI
                                                                 * */
        uint32_t axi_dmm_wr            : 1;  /**< [ 17: 17](RO/H) Indicates that the external Data memory write request was confirmed by the AXI
                                                                 * */
        uint32_t wait_f                : 1;  /**< [ 18: 18](RO/H) Indicates that the core is in wait */
        uint32_t snoop_idle            : 1;  /**< [ 19: 19](RO/H) Indicates that there are no ongoing SNOOP is in MSS */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_ocem_ocm_status_s cn; */
};
typedef union bdk_cbpx_ocem_ocm_status bdk_cbpx_ocem_ocm_status_t;

static inline uint64_t BDK_CBPX_OCEM_OCM_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_OCEM_OCM_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822160ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_OCEM_OCM_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_OCEM_OCM_STATUS(a) bdk_cbpx_ocem_ocm_status_t
#define bustype_BDK_CBPX_OCEM_OCM_STATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_OCEM_OCM_STATUS(a) "CBPX_OCEM_OCM_STATUS"
#define busnum_BDK_CBPX_OCEM_OCM_STATUS(a) (a)
#define arguments_BDK_CBPX_OCEM_OCM_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_pmss_mss_pb1ba
 *
 * CBP Pmss Mss Pb1ba Register
 * Note: Block1 is mapped immediately following Block0.
 */
union bdk_cbpx_pmss_mss_pb1ba
{
    uint32_t u;
    struct bdk_cbpx_pmss_mss_pb1ba_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pb1ba                 : 32; /**< [ 31:  0](RO) Read only Block1 base address */
#else /* Word 0 - Little Endian */
        uint32_t pb1ba                 : 32; /**< [ 31:  0](RO) Read only Block1 base address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_pmss_mss_pb1ba_s cn; */
};
typedef union bdk_cbpx_pmss_mss_pb1ba bdk_cbpx_pmss_mss_pb1ba_t;

static inline uint64_t BDK_CBPX_PMSS_MSS_PB1BA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PMSS_MSS_PB1BA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822004ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PMSS_MSS_PB1BA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PMSS_MSS_PB1BA(a) bdk_cbpx_pmss_mss_pb1ba_t
#define bustype_BDK_CBPX_PMSS_MSS_PB1BA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PMSS_MSS_PB1BA(a) "CBPX_PMSS_MSS_PB1BA"
#define busnum_BDK_CBPX_PMSS_MSS_PB1BA(a) (a)
#define arguments_BDK_CBPX_PMSS_MSS_PB1BA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_pmss_mss_pdea
 *
 * CBP Pmss Mss Pdea Register
 * Note: Bits [4:0] are written as 0.
 */
union bdk_cbpx_pmss_mss_pdea
{
    uint32_t u;
    struct bdk_cbpx_pmss_mss_pdea_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pdea                  : 32; /**< [ 31:  0](R/W/H) PDMA external source address: This field is incremented by one fetch-line after
                                                                 each external read burst.
                                                                 Note: If AXI_B strap pin is asserted, the address configured in the PDEA must be:
                                                                 1. aligned to 64B and PBSZ set to 01
                                                                 2. or aligned to 32B and PBSZ set to 00 */
#else /* Word 0 - Little Endian */
        uint32_t pdea                  : 32; /**< [ 31:  0](R/W/H) PDMA external source address: This field is incremented by one fetch-line after
                                                                 each external read burst.
                                                                 Note: If AXI_B strap pin is asserted, the address configured in the PDEA must be:
                                                                 1. aligned to 64B and PBSZ set to 01
                                                                 2. or aligned to 32B and PBSZ set to 00 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_pmss_mss_pdea_s cn; */
};
typedef union bdk_cbpx_pmss_mss_pdea bdk_cbpx_pmss_mss_pdea_t;

static inline uint64_t BDK_CBPX_PMSS_MSS_PDEA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PMSS_MSS_PDEA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822008ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PMSS_MSS_PDEA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PMSS_MSS_PDEA(a) bdk_cbpx_pmss_mss_pdea_t
#define bustype_BDK_CBPX_PMSS_MSS_PDEA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PMSS_MSS_PDEA(a) "CBPX_PMSS_MSS_PDEA"
#define busnum_BDK_CBPX_PMSS_MSS_PDEA(a) (a)
#define arguments_BDK_CBPX_PMSS_MSS_PDEA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_pmss_mss_pdia
 *
 * CBP Pmss Mss Pdia Register
 * Note: Bits [4:0] are written as 0.
 *             Bits [31:16] are ignored when accessing 32KB TCM or cache.
 *             Bits [31:17] are ignored when only accessing 64KB TCM.
 *             Bits [31:18] are ignored when only accessing 128KB TCM.
 *             Bits [31:19] are ignored when only accessing 256KB TCM.
 *             Bits [31:20] are ignored when only accessing 512KB TCM.
 */
union bdk_cbpx_pmss_mss_pdia
{
    uint32_t u;
    struct bdk_cbpx_pmss_mss_pdia_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pdia                  : 32; /**< [ 31:  0](R/W/H) PDMA internal destination address: This field is incremented by one fetch-line
                                                                 after a fetch-line is written into the internal memory. */
#else /* Word 0 - Little Endian */
        uint32_t pdia                  : 32; /**< [ 31:  0](R/W/H) PDMA internal destination address: This field is incremented by one fetch-line
                                                                 after a fetch-line is written into the internal memory. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_pmss_mss_pdia_s cn; */
};
typedef union bdk_cbpx_pmss_mss_pdia bdk_cbpx_pmss_mss_pdia_t;

static inline uint64_t BDK_CBPX_PMSS_MSS_PDIA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PMSS_MSS_PDIA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482200cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PMSS_MSS_PDIA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PMSS_MSS_PDIA(a) bdk_cbpx_pmss_mss_pdia_t
#define bustype_BDK_CBPX_PMSS_MSS_PDIA(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PMSS_MSS_PDIA(a) "CBPX_PMSS_MSS_PDIA"
#define busnum_BDK_CBPX_PMSS_MSS_PDIA(a) (a)
#define arguments_BDK_CBPX_PMSS_MSS_PDIA(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_pmss_mss_pdtc
 *
 * CBP Pmss Mss Pdtc Register
 * * The PDTC field is an example for 32KB configuration.
 */
union bdk_cbpx_pmss_mss_pdtc
{
    uint32_t u;
    struct bdk_cbpx_pmss_mss_pdtc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pdie                  : 1;  /**< [ 31: 31](R/W) Program DMA interrupt enable: when set, the Program DMA interrupt at the end of
                                                                 the transfer is enabled. */
        uint32_t cac_inv               : 1;  /**< [ 30: 30](R/W) Cache invalidate: When set, the cache is invalidated by the PDMA. This process takes 1,024 cycles.
                                                                 The cache size in bytes (32 KB) is loaded into PDTC, and PDST is set.
                                                                 CAC_INV is automatically cleared when PDST is cleared and the entire cache is invalidated. */
        uint32_t pdst                  : 1;  /**< [ 29: 29](RO/H) PDMA status: This read-only bit indicates the PDMA status. When set, the Program
                                                                 DMA is busy  that is: a frame is currently being transferred. When cleared, the
                                                                 DMA is not busy. This bit is automatically set by hardware when a frame transfer
                                                                 starts, and is cleared when the frame transfer has been completed. */
        uint32_t outs                  : 2;  /**< [ 28: 27](R/W) PDMA maximum outstanding reads:
                                                                 00 : 1 outstanding
                                                                 01 : 2 outstanding
                                                                 10 : 4 outstanding */
        uint32_t pbsz                  : 2;  /**< [ 26: 25](R/W) Program DMA maximum burst length:
                                                                 00: 2 beats
                                                                 01: 4 beats
                                                                 10: 8 beats
                                                                 11: 16 beats */
        uint32_t reserved_22_24        : 3;
        uint32_t pdtc                  : 22; /**< [ 21:  0](R/W/H) PDMA transfer count: Number of program bytes to be transferred in a frame. (The
                                                                 value is rounded by instruction fetch-line width. Bits [4:0] are always zero.)
                                                                 This field is decremented by one fetch-line width after each IPM write access.
                                                                 Writing a value to this register starts the DMA transfer. */
#else /* Word 0 - Little Endian */
        uint32_t pdtc                  : 22; /**< [ 21:  0](R/W/H) PDMA transfer count: Number of program bytes to be transferred in a frame. (The
                                                                 value is rounded by instruction fetch-line width. Bits [4:0] are always zero.)
                                                                 This field is decremented by one fetch-line width after each IPM write access.
                                                                 Writing a value to this register starts the DMA transfer. */
        uint32_t reserved_22_24        : 3;
        uint32_t pbsz                  : 2;  /**< [ 26: 25](R/W) Program DMA maximum burst length:
                                                                 00: 2 beats
                                                                 01: 4 beats
                                                                 10: 8 beats
                                                                 11: 16 beats */
        uint32_t outs                  : 2;  /**< [ 28: 27](R/W) PDMA maximum outstanding reads:
                                                                 00 : 1 outstanding
                                                                 01 : 2 outstanding
                                                                 10 : 4 outstanding */
        uint32_t pdst                  : 1;  /**< [ 29: 29](RO/H) PDMA status: This read-only bit indicates the PDMA status. When set, the Program
                                                                 DMA is busy  that is: a frame is currently being transferred. When cleared, the
                                                                 DMA is not busy. This bit is automatically set by hardware when a frame transfer
                                                                 starts, and is cleared when the frame transfer has been completed. */
        uint32_t cac_inv               : 1;  /**< [ 30: 30](R/W) Cache invalidate: When set, the cache is invalidated by the PDMA. This process takes 1,024 cycles.
                                                                 The cache size in bytes (32 KB) is loaded into PDTC, and PDST is set.
                                                                 CAC_INV is automatically cleared when PDST is cleared and the entire cache is invalidated. */
        uint32_t pdie                  : 1;  /**< [ 31: 31](R/W) Program DMA interrupt enable: when set, the Program DMA interrupt at the end of
                                                                 the transfer is enabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_pmss_mss_pdtc_s cn; */
};
typedef union bdk_cbpx_pmss_mss_pdtc bdk_cbpx_pmss_mss_pdtc_t;

static inline uint64_t BDK_CBPX_PMSS_MSS_PDTC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PMSS_MSS_PDTC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822010ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PMSS_MSS_PDTC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PMSS_MSS_PDTC(a) bdk_cbpx_pmss_mss_pdtc_t
#define bustype_BDK_CBPX_PMSS_MSS_PDTC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PMSS_MSS_PDTC(a) "CBPX_PMSS_MSS_PDTC"
#define busnum_BDK_CBPX_PMSS_MSS_PDTC(a) (a)
#define arguments_BDK_CBPX_PMSS_MSS_PDTC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_pmss_pmss_pcr
 *
 * CBP Pmss Pmss Pcr Register
 * Note: If the invalidate cache input strap pin is set during reset, the value after
 * reset is 0x0000_000B (meaning that the cache is disabled).
 */
union bdk_cbpx_pmss_pmss_pcr
{
    uint32_t u;
    struct bdk_cbpx_pmss_pmss_pcr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t tcme                  : 1;  /**< [  3:  3](R/W) TCM Enable:
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t cac_pfe               : 1;  /**< [  2:  2](R/W) Cache Pre-fetch Enable:
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t cac_mod               : 2;  /**< [  1:  0](R/W) Cache Mode:
                                                                 00: Mapped
                                                                 01: Cache is enabled
                                                                 10: Cache is locked
                                                                 11: Cache is disabled; all non-TCM accesses result in an external memory access
                                                                 through the AXI interface */
#else /* Word 0 - Little Endian */
        uint32_t cac_mod               : 2;  /**< [  1:  0](R/W) Cache Mode:
                                                                 00: Mapped
                                                                 01: Cache is enabled
                                                                 10: Cache is locked
                                                                 11: Cache is disabled; all non-TCM accesses result in an external memory access
                                                                 through the AXI interface */
        uint32_t cac_pfe               : 1;  /**< [  2:  2](R/W) Cache Pre-fetch Enable:
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t tcme                  : 1;  /**< [  3:  3](R/W) TCM Enable:
                                                                 0: Disabled
                                                                 1: Enabled */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_pmss_pmss_pcr_s cn; */
};
typedef union bdk_cbpx_pmss_pmss_pcr bdk_cbpx_pmss_pmss_pcr_t;

static inline uint64_t BDK_CBPX_PMSS_PMSS_PCR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PMSS_PMSS_PCR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822000ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PMSS_PMSS_PCR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PMSS_PMSS_PCR(a) bdk_cbpx_pmss_pmss_pcr_t
#define bustype_BDK_CBPX_PMSS_PMSS_PCR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PMSS_PMSS_PCR(a) "CBPX_PMSS_PMSS_PCR"
#define busnum_BDK_CBPX_PMSS_PMSS_PCR(a) (a)
#define arguments_BDK_CBPX_PMSS_PMSS_PCR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_dbc
 *
 * CBP Psu Dbc Register
 */
union bdk_cbpx_psu_dbc
{
    uint32_t u;
    struct bdk_cbpx_psu_dbc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t dbc                   : 1;  /**< [  0:  0](R/W) Debug Block Configuration:
                                                                 1b0 : Operational Production  the Debug Block power  and clocks are shutdown
                                                                 regardless of the Power Save Mode configurations
                                                                 1b1: Debug Block On  clocks and power are provided to the debug block
                                                                 When the core and MSS are shut down the debug block is off regardless the DBC bit */
#else /* Word 0 - Little Endian */
        uint32_t dbc                   : 1;  /**< [  0:  0](R/W) Debug Block Configuration:
                                                                 1b0 : Operational Production  the Debug Block power  and clocks are shutdown
                                                                 regardless of the Power Save Mode configurations
                                                                 1b1: Debug Block On  clocks and power are provided to the debug block
                                                                 When the core and MSS are shut down the debug block is off regardless the DBC bit */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_dbc_s cn; */
};
typedef union bdk_cbpx_psu_dbc bdk_cbpx_psu_dbc_t;

static inline uint64_t BDK_CBPX_PSU_DBC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_DBC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822254ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_DBC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_DBC(a) bdk_cbpx_psu_dbc_t
#define bustype_BDK_CBPX_PSU_DBC(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_DBC(a) "CBPX_PSU_DBC"
#define busnum_BDK_CBPX_PSU_DBC(a) (a)
#define arguments_BDK_CBPX_PSU_DBC(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_pgr
 *
 * CBP Psu Pgr Register
 */
union bdk_cbpx_psu_pgr
{
    uint32_t u;
    struct bdk_cbpx_psu_pgr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t vinte                 : 1;  /**< [  0:  0](R/W) Vector interrupt enable:
                                                                 1b0: Recovery by VINT signal.
                                                                 1b1: Recovery by CORE_RCVR signal. */
#else /* Word 0 - Little Endian */
        uint32_t vinte                 : 1;  /**< [  0:  0](R/W) Vector interrupt enable:
                                                                 1b0: Recovery by VINT signal.
                                                                 1b1: Recovery by CORE_RCVR signal. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_pgr_s cn; */
};
typedef union bdk_cbpx_psu_pgr bdk_cbpx_psu_pgr_t;

static inline uint64_t BDK_CBPX_PSU_PGR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_PGR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822258ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_PGR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_PGR(a) bdk_cbpx_psu_pgr_t
#define bustype_BDK_CBPX_PSU_PGR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_PGR(a) "CBPX_PSU_PGR"
#define busnum_BDK_CBPX_PSU_PGR(a) (a)
#define arguments_BDK_CBPX_PSU_PGR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_psvm_hi
 *
 * CBP Psu Psvm Hi Register
 */
union bdk_cbpx_psu_psvm_hi
{
    uint32_t u;
    struct bdk_cbpx_psu_psvm_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_21_31        : 11;
        uint32_t fics7_ae              : 1;  /**< [ 20: 20](R/W) FICS7 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS7 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS7 clock bridge is free running (clock is always provided) */
        uint32_t fics6_ae              : 1;  /**< [ 19: 19](R/W) FICS6 Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS6 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS6 clock bridge is free running (clock is always provided) */
        uint32_t fics5_ae              : 1;  /**< [ 18: 18](R/W) FICS5 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS5 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS5 clock bridge is free running (clock is always provided) */
        uint32_t fics4_ae              : 1;  /**< [ 17: 17](R/W) FICS4 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS4 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS4 clock bridge is free running (clock is always provided) */
        uint32_t shtdwn_hi             : 6;  /**< [ 16: 11](R/W) Shutdown Indications bus (high part) for IDM blocks
                                                                    4,5,6,7::
                                                                 When clear, indicates that the physical memory is in shutdown (no voltage is supplied)
                                                                 Bit[11]: DMSS tag shutdown indication
                                                                    Bit[12]: DMSS Cache set  shutdown indication
                                                                 Bit[13] -DMSS block 4 shutdown indication
                                                                 Bit[14] -DMSS block 5 shutdown indication
                                                                 Bit[15]* -DMSS block 6 shutdown indication
                                                                 Bit[16]* -DMSS block 7 shutdown indication

                                                                    When DMSS is hardware configured to four blocks, the above bits are hardcoded
                                                                 to 0 values after reset.
                                                                 * When DMSS is hardware configured to four or six blocks, these bits are
                                                                 hardcoded to 0 values after reset. */
        uint32_t reserved_10           : 1;
        uint32_t ret_hi                : 6;  /**< [  9:  4](R/W) Retention Indication bus (high part) for IDM blocks 4,5,6,7:
                                                                 When clear, indicates that the physical memory is in retention.
                                                                 Bit[4]: DMSS tag retention indication
                                                                    Bit[5]: DMSS Cache set  retention indication
                                                                 Bit[6] -DMSS block 4 retention indication
                                                                 Bit[7] -DMSS block 5 retention indication
                                                                 Bit[8]* -DMSS block 6 retention indication
                                                                 Bit[9]* -DMSS block 7 retention indication
                                                                 When DMSS is hardware-configured to four blocks, the above bits are hardcoded to
                                                                 0 values after reset.
                                                                 * When DMSS is hardware configured to two blocks these bits are hardcoded to 0 values after reset. */
        uint32_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_3          : 4;
        uint32_t ret_hi                : 6;  /**< [  9:  4](R/W) Retention Indication bus (high part) for IDM blocks 4,5,6,7:
                                                                 When clear, indicates that the physical memory is in retention.
                                                                 Bit[4]: DMSS tag retention indication
                                                                    Bit[5]: DMSS Cache set  retention indication
                                                                 Bit[6] -DMSS block 4 retention indication
                                                                 Bit[7] -DMSS block 5 retention indication
                                                                 Bit[8]* -DMSS block 6 retention indication
                                                                 Bit[9]* -DMSS block 7 retention indication
                                                                 When DMSS is hardware-configured to four blocks, the above bits are hardcoded to
                                                                 0 values after reset.
                                                                 * When DMSS is hardware configured to two blocks these bits are hardcoded to 0 values after reset. */
        uint32_t reserved_10           : 1;
        uint32_t shtdwn_hi             : 6;  /**< [ 16: 11](R/W) Shutdown Indications bus (high part) for IDM blocks
                                                                    4,5,6,7::
                                                                 When clear, indicates that the physical memory is in shutdown (no voltage is supplied)
                                                                 Bit[11]: DMSS tag shutdown indication
                                                                    Bit[12]: DMSS Cache set  shutdown indication
                                                                 Bit[13] -DMSS block 4 shutdown indication
                                                                 Bit[14] -DMSS block 5 shutdown indication
                                                                 Bit[15]* -DMSS block 6 shutdown indication
                                                                 Bit[16]* -DMSS block 7 shutdown indication

                                                                    When DMSS is hardware configured to four blocks, the above bits are hardcoded
                                                                 to 0 values after reset.
                                                                 * When DMSS is hardware configured to four or six blocks, these bits are
                                                                 hardcoded to 0 values after reset. */
        uint32_t fics4_ae              : 1;  /**< [ 17: 17](R/W) FICS4 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS4 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS4 clock bridge is free running (clock is always provided) */
        uint32_t fics5_ae              : 1;  /**< [ 18: 18](R/W) FICS5 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS5 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS5 clock bridge is free running (clock is always provided) */
        uint32_t fics6_ae              : 1;  /**< [ 19: 19](R/W) FICS6 Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS6 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS6 clock bridge is free running (clock is always provided) */
        uint32_t fics7_ae              : 1;  /**< [ 20: 20](R/W) FICS7 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS7 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS7 clock bridge is free running (clock is always provided) */
        uint32_t reserved_21_31        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_psvm_hi_s cn; */
};
typedef union bdk_cbpx_psu_psvm_hi bdk_cbpx_psu_psvm_hi_t;

static inline uint64_t BDK_CBPX_PSU_PSVM_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_PSVM_HI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482224cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_PSVM_HI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_PSVM_HI(a) bdk_cbpx_psu_psvm_hi_t
#define bustype_BDK_CBPX_PSU_PSVM_HI(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_PSVM_HI(a) "CBPX_PSU_PSVM_HI"
#define busnum_BDK_CBPX_PSU_PSVM_HI(a) (a)
#define arguments_BDK_CBPX_PSU_PSVM_HI(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_psvm_lo
 *
 * CBP Psu Psvm Lo Register
 */
union bdk_cbpx_psu_psvm_lo
{
    uint32_t u;
    struct bdk_cbpx_psu_psvm_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t snoop_ae              : 1;  /**< [ 29: 29](R/W) SNOOP port Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1'b0:  SNOOP clock bridge is automatic enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1'b1:  SNOOP clock bridge is free running (clock is always provided) */
        uint32_t dman_ae               : 1;  /**< [ 28: 28](R/W) DMA Manager Automatic Enable mode:
                                                                 When clear, the QMAN and BMAN are automatically clocked. This mode is valid only
                                                                 under DPS and Light Sleep modes:
                                                                 1b0:  DMAN clock is automatic enabled
                                                                 1b1:  DMAN clock is free running (clock is always provided) */
        uint32_t reserved_21_27        : 7;
        uint32_t fics3_ae              : 1;  /**< [ 20: 20](R/W) FICS3 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS3 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS3 clock bridge is free running (clock is always provided) */
        uint32_t fics2_ae              : 1;  /**< [ 19: 19](R/W) FICS2 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS2 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS2 clock bridge is free running (clock is always provided) */
        uint32_t fics1_ae              : 1;  /**< [ 18: 18](R/W) FICS1 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS1 clock bridge is automatic enabled due to incoming transactions
                                                                 (clock is automatically only when transaction is valid)
                                                                 1b1:  FICS1 clock bridge is free running (clock is always provided) */
        uint32_t fics0_ae              : 1;  /**< [ 17: 17](R/W) FICS0 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS0 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS0 clock bridge is free running (clock is always provided) */
        uint32_t shtdwn_lo             : 7;  /**< [ 16: 10](R/W) Shutdown Indications bus(low part):
                                                                 When clear, indicates that the physical memory is in Shutdown (no voltage is supplied)
                                                                 BIT[10] -Core and MSS shutdown indication
                                                                 Bit[11] -PMSS TCM shutdown indication
                                                                 Bit[12] -PMSS cache shutdown indication
                                                                 Bit[13] -DMSS block 0 shutdown indication
                                                                 Bit[14] -DMSS block 1 shutdown indication
                                                                 Bit[15] -DMSS block 2 shutdown indication
                                                                 Bit[16] -DMSS block 3 shutdown indication */
        uint32_t ret_lo                : 6;  /**< [  9:  4](R/W) Retention Indication bus (low part):
                                                                 When clear, indicates that the physical memory is in retention.
                                                                 Bit[4] -PMSS TCM retention indication
                                                                 Bit[5] -PMSS cache and tag retention indication
                                                                 Bit[6] -DMSS block 0 retention indication
                                                                 Bit[7] -DMSS block 1 retention indication
                                                                 Bit[8]** -DMSS block 2 retention indication
                                                                 Bit[9]** -DMSS block 3 retention indication
                                                                 ** When DMSS is hardware configured to two blocks these bits are hardcoded to 0 values after reset. */
        uint32_t edap_ae               : 1;  /**< [  3:  3](R/W) EDAP Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1b0:  EDAP clock bridge is automatic enabled due to incoming transactions (clock
                                                                 is provided only when transaction is valid)
                                                                 1b1:  EDAP clock bridge is free running (clock is always provided) */
        uint32_t mss_ae                : 1;  /**< [  2:  2](R/W) MSS Automatic Enable mode:
                                                                 Provide free clocks to all MSS units (except EDAP) under Light Sleep and DPS.
                                                                 1b0: The MSS clocks are provided only when units are ACTIVE.
                                                                 1b1: Enables all MSS clocks. */
        uint32_t pmod                  : 2;  /**< [  1:  0](R/W) Power Save Mode:
                                                                 2b00: 	Free Run. All clocks are enabled.
                                                                 2b01: 	Dynamic Power Save (DPS). Automatic clock getting for active units. This is the reset value.
                                                                 2b10: 	Light Sleep. The core and WB clocks shut down.
                                                                 2b11: 	Standby. All clocks are shut down and can also be shut down externally */
#else /* Word 0 - Little Endian */
        uint32_t pmod                  : 2;  /**< [  1:  0](R/W) Power Save Mode:
                                                                 2b00: 	Free Run. All clocks are enabled.
                                                                 2b01: 	Dynamic Power Save (DPS). Automatic clock getting for active units. This is the reset value.
                                                                 2b10: 	Light Sleep. The core and WB clocks shut down.
                                                                 2b11: 	Standby. All clocks are shut down and can also be shut down externally */
        uint32_t mss_ae                : 1;  /**< [  2:  2](R/W) MSS Automatic Enable mode:
                                                                 Provide free clocks to all MSS units (except EDAP) under Light Sleep and DPS.
                                                                 1b0: The MSS clocks are provided only when units are ACTIVE.
                                                                 1b1: Enables all MSS clocks. */
        uint32_t edap_ae               : 1;  /**< [  3:  3](R/W) EDAP Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1b0:  EDAP clock bridge is automatic enabled due to incoming transactions (clock
                                                                 is provided only when transaction is valid)
                                                                 1b1:  EDAP clock bridge is free running (clock is always provided) */
        uint32_t ret_lo                : 6;  /**< [  9:  4](R/W) Retention Indication bus (low part):
                                                                 When clear, indicates that the physical memory is in retention.
                                                                 Bit[4] -PMSS TCM retention indication
                                                                 Bit[5] -PMSS cache and tag retention indication
                                                                 Bit[6] -DMSS block 0 retention indication
                                                                 Bit[7] -DMSS block 1 retention indication
                                                                 Bit[8]** -DMSS block 2 retention indication
                                                                 Bit[9]** -DMSS block 3 retention indication
                                                                 ** When DMSS is hardware configured to two blocks these bits are hardcoded to 0 values after reset. */
        uint32_t shtdwn_lo             : 7;  /**< [ 16: 10](R/W) Shutdown Indications bus(low part):
                                                                 When clear, indicates that the physical memory is in Shutdown (no voltage is supplied)
                                                                 BIT[10] -Core and MSS shutdown indication
                                                                 Bit[11] -PMSS TCM shutdown indication
                                                                 Bit[12] -PMSS cache shutdown indication
                                                                 Bit[13] -DMSS block 0 shutdown indication
                                                                 Bit[14] -DMSS block 1 shutdown indication
                                                                 Bit[15] -DMSS block 2 shutdown indication
                                                                 Bit[16] -DMSS block 3 shutdown indication */
        uint32_t fics0_ae              : 1;  /**< [ 17: 17](R/W) FICS0 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS0 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS0 clock bridge is free running (clock is always provided) */
        uint32_t fics1_ae              : 1;  /**< [ 18: 18](R/W) FICS1 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS1 clock bridge is automatic enabled due to incoming transactions
                                                                 (clock is automatically only when transaction is valid)
                                                                 1b1:  FICS1 clock bridge is free running (clock is always provided) */
        uint32_t fics2_ae              : 1;  /**< [ 19: 19](R/W) FICS2 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS2 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS2 clock bridge is free running (clock is always provided) */
        uint32_t fics3_ae              : 1;  /**< [ 20: 20](R/W) FICS3 Automatic Enable mode:
                                                                 When clear, the bridge is automatically clocked when accessing the bridge. This
                                                                 mode is valid only under DPS and Light Sleep modes:
                                                                 1b0:  FICS3 clock bridge is automatically enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1b1:  FICS3 clock bridge is free running (clock is always provided) */
        uint32_t reserved_21_27        : 7;
        uint32_t dman_ae               : 1;  /**< [ 28: 28](R/W) DMA Manager Automatic Enable mode:
                                                                 When clear, the QMAN and BMAN are automatically clocked. This mode is valid only
                                                                 under DPS and Light Sleep modes:
                                                                 1b0:  DMAN clock is automatic enabled
                                                                 1b1:  DMAN clock is free running (clock is always provided) */
        uint32_t snoop_ae              : 1;  /**< [ 29: 29](R/W) SNOOP port Automatic Enable mode:
                                                                 When clear, the bridge is automatic clocked when accessing the bridge. This mode
                                                                 is valid only under DPS and Light Sleep modes:
                                                                 1'b0:  SNOOP clock bridge is automatic enabled due to incoming transactions
                                                                 (clock is provided only when transaction is valid)
                                                                 1'b1:  SNOOP clock bridge is free running (clock is always provided) */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_psvm_lo_s cn; */
};
typedef union bdk_cbpx_psu_psvm_lo bdk_cbpx_psu_psvm_lo_t;

static inline uint64_t BDK_CBPX_PSU_PSVM_LO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_PSVM_LO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822250ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_PSVM_LO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_PSVM_LO(a) bdk_cbpx_psu_psvm_lo_t
#define bustype_BDK_CBPX_PSU_PSVM_LO(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_PSVM_LO(a) "CBPX_PSU_PSVM_LO"
#define busnum_BDK_CBPX_PSU_PSVM_LO(a) (a)
#define arguments_BDK_CBPX_PSU_PSVM_LO(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_spret
 *
 * CBP Psu Spret Register
 */
union bdk_cbpx_psu_spret
{
    uint32_t u;
    struct bdk_cbpx_psu_spret_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t spret                 : 16; /**< [ 15:  0](R/W) Cycle counter in order to get out of retention mode
                                                                 This register is only present if the PSU Power Gating is set */
#else /* Word 0 - Little Endian */
        uint32_t spret                 : 16; /**< [ 15:  0](R/W) Cycle counter in order to get out of retention mode
                                                                 This register is only present if the PSU Power Gating is set */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_spret_s cn; */
};
typedef union bdk_cbpx_psu_spret bdk_cbpx_psu_spret_t;

static inline uint64_t BDK_CBPX_PSU_SPRET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_SPRET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822260ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_SPRET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_SPRET(a) bdk_cbpx_psu_spret_t
#define bustype_BDK_CBPX_PSU_SPRET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_SPRET(a) "CBPX_PSU_SPRET"
#define busnum_BDK_CBPX_PSU_SPRET(a) (a)
#define arguments_BDK_CBPX_PSU_SPRET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_spsd
 *
 * CBP Psu Spsd Register
 */
union bdk_cbpx_psu_spsd
{
    uint32_t u;
    struct bdk_cbpx_psu_spsd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t spsd                  : 16; /**< [ 15:  0](R/W) Cycle counter in order to get out of shutdown mode */
#else /* Word 0 - Little Endian */
        uint32_t spsd                  : 16; /**< [ 15:  0](R/W) Cycle counter in order to get out of shutdown mode */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_spsd_s cn; */
};
typedef union bdk_cbpx_psu_spsd bdk_cbpx_psu_spsd_t;

static inline uint64_t BDK_CBPX_PSU_SPSD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_SPSD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822268ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_SPSD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_SPSD(a) bdk_cbpx_psu_spsd_t
#define bustype_BDK_CBPX_PSU_SPSD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_SPSD(a) "CBPX_PSU_SPSD"
#define busnum_BDK_CBPX_PSU_SPSD(a) (a)
#define arguments_BDK_CBPX_PSU_SPSD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_stret
 *
 * CBP Psu Stret Register
 */
union bdk_cbpx_psu_stret
{
    uint32_t u;
    struct bdk_cbpx_psu_stret_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t stret                 : 16; /**< [ 15:  0](R/W) Cycle counter in order to get into retention mode
                                                                 This register is only present if the PSU Power Gating is set */
#else /* Word 0 - Little Endian */
        uint32_t stret                 : 16; /**< [ 15:  0](R/W) Cycle counter in order to get into retention mode
                                                                 This register is only present if the PSU Power Gating is set */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_stret_s cn; */
};
typedef union bdk_cbpx_psu_stret bdk_cbpx_psu_stret_t;

static inline uint64_t BDK_CBPX_PSU_STRET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_STRET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482225cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_STRET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_STRET(a) bdk_cbpx_psu_stret_t
#define bustype_BDK_CBPX_PSU_STRET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_STRET(a) "CBPX_PSU_STRET"
#define busnum_BDK_CBPX_PSU_STRET(a) (a)
#define arguments_BDK_CBPX_PSU_STRET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_psu_stsd
 *
 * CBP Psu Stsd Register
 */
union bdk_cbpx_psu_stsd
{
    uint32_t u;
    struct bdk_cbpx_psu_stsd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t stsd                  : 16; /**< [ 15:  0](R/W) Cycle counter in order to get into shutdown mode
                                                                 This register is only present if the PSU Power Gating is set */
#else /* Word 0 - Little Endian */
        uint32_t stsd                  : 16; /**< [ 15:  0](R/W) Cycle counter in order to get into shutdown mode
                                                                 This register is only present if the PSU Power Gating is set */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_psu_stsd_s cn; */
};
typedef union bdk_cbpx_psu_stsd bdk_cbpx_psu_stsd_t;

static inline uint64_t BDK_CBPX_PSU_STSD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_PSU_STSD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822264ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_PSU_STSD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_PSU_STSD(a) bdk_cbpx_psu_stsd_t
#define bustype_BDK_CBPX_PSU_STSD(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_PSU_STSD(a) "CBPX_PSU_STSD"
#define busnum_BDK_CBPX_PSU_STSD(a) (a)
#define arguments_BDK_CBPX_PSU_STSD(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_bman_irq_addr_reg
 *
 * CBP Qman Bman Cntrl Bman Irq Addr Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t bman_irq_addr         : 20; /**< [ 19:  0](R/W) An interrupt is set when selected buffer pointer is equal to or crossed BMAN_IRQ_ADDR
                                                                 The two LSBs of this register are always replaced with 2h0 */
#else /* Word 0 - Little Endian */
        uint32_t bman_irq_addr         : 20; /**< [ 19:  0](R/W) An interrupt is set when selected buffer pointer is equal to or crossed BMAN_IRQ_ADDR
                                                                 The two LSBs of this register are always replaced with 2h0 */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227e4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(a) bdk_cbpx_qman_bman_cntrl_bman_irq_addr_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(a) "CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_ADDR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_bman_irq_cfg_reg
 *
 * CBP Qman Bman Cntrl Bman Irq Cfg Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t dsp_empty             : 1;  /**< [ 31: 31](RO/H) Read only register holding the status of the buffer in use when BMAN_IRQ_SEL==11
                                                                 0-	Buffer is not empty
                                                                 1-	Buffer is almost empty */
        uint32_t reserved_20_30        : 11;
        uint32_t bman_irq_sel          : 2;  /**< [ 19: 18](R/W) Selects the source for the bman_irq
                                                                 00  not used (interrupt is not set).
                                                                 01  Interrupt is set when read pointer of selected buffer is equal to BMAN_IRQ_ADDR.
                                                                 10  Interrupt is set when write pointer of selected buffer is equal to BMAN_IRQ_ADDR.
                                                                 11  Interrupt is set when DSP reads from an almost empty buffer. */
        uint32_t reserved_17           : 1;
        uint32_t dsp_bman_sel          : 5;  /**< [ 16: 12](R/W) Selects the BMAN to be used for interrupting the CEVA-XC4000 */
        uint32_t reserved_10_11        : 2;
        uint32_t dsp_rd_thld           : 10; /**< [  9:  0](R/W) Read threshold for setting the bman_irq.
                                                                 When the buffer read by the CEVA-XC4500  is below the DSP_RD_THLD  bman_irq is
                                                                 set to prevent the CEVA-XC4000 from reading an empty buffer */
#else /* Word 0 - Little Endian */
        uint32_t dsp_rd_thld           : 10; /**< [  9:  0](R/W) Read threshold for setting the bman_irq.
                                                                 When the buffer read by the CEVA-XC4500  is below the DSP_RD_THLD  bman_irq is
                                                                 set to prevent the CEVA-XC4000 from reading an empty buffer */
        uint32_t reserved_10_11        : 2;
        uint32_t dsp_bman_sel          : 5;  /**< [ 16: 12](R/W) Selects the BMAN to be used for interrupting the CEVA-XC4000 */
        uint32_t reserved_17           : 1;
        uint32_t bman_irq_sel          : 2;  /**< [ 19: 18](R/W) Selects the source for the bman_irq
                                                                 00  not used (interrupt is not set).
                                                                 01  Interrupt is set when read pointer of selected buffer is equal to BMAN_IRQ_ADDR.
                                                                 10  Interrupt is set when write pointer of selected buffer is equal to BMAN_IRQ_ADDR.
                                                                 11  Interrupt is set when DSP reads from an almost empty buffer. */
        uint32_t reserved_20_30        : 11;
        uint32_t dsp_empty             : 1;  /**< [ 31: 31](RO/H) Read only register holding the status of the buffer in use when BMAN_IRQ_SEL==11
                                                                 0-	Buffer is not empty
                                                                 1-	Buffer is almost empty */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227e0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(a) bdk_cbpx_qman_bman_cntrl_bman_irq_cfg_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(a) "CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_IRQ_CFG_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_bman_rst_reg
 *
 * CBP Qman Bman Cntrl Bman Rst Reg Register
 * Reset Value:
 * 	Twenty four BMANs hardware configuration - 0x00FF_FFFF
 * 	Sixteen BMANs hardware configuration - 0x0000_FFFF
 * 	Twelve BMANs hardware configuration - 0x0000_0FFF
 * 	Eight BMANs hardware configuration - 0x0000_00FF
 * 	Four BMANs hardware configuration - 0x0000_000F
 * 	Zero BMANs hardware configuration - Reserved
 */
union bdk_cbpx_qman_bman_cntrl_bman_rst_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_bman_rst_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t b7_rst                : 1;  /**< [  7:  7](R/W) Software reset for BMAN 7; setting this bit resets all of the BMAN 7 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b6_rst                : 1;  /**< [  6:  6](R/W) Software reset for BMAN 6; setting this bit resets all of the BMAN 6 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b5_rst                : 1;  /**< [  5:  5](R/W) Software reset for BMAN 5; setting this bit resets all of the BMAN 5 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b4_rst                : 1;  /**< [  4:  4](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 4; setting this bit resets all of the BMAN 4 internal
                                                                 registers */
        uint32_t b3_rst                : 1;  /**< [  3:  3](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 3; setting this bit resets all of the BMAN 3 internal
                                                                 registers */
        uint32_t b2_rst                : 1;  /**< [  2:  2](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 2; setting this bit resets all of the BMAN 2 internal
                                                                 registers */
        uint32_t b1_rst                : 1;  /**< [  1:  1](R/W) Software reset for BMAN 1; setting this bit resets all of the BMAN 1 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b0_rst                : 1;  /**< [  0:  0](R/W) Software reset for BMAN 0; setting this bit resets all of the BMAN 0 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
#else /* Word 0 - Little Endian */
        uint32_t b0_rst                : 1;  /**< [  0:  0](R/W) Software reset for BMAN 0; setting this bit resets all of the BMAN 0 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b1_rst                : 1;  /**< [  1:  1](R/W) Software reset for BMAN 1; setting this bit resets all of the BMAN 1 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b2_rst                : 1;  /**< [  2:  2](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 2; setting this bit resets all of the BMAN 2 internal
                                                                 registers */
        uint32_t b3_rst                : 1;  /**< [  3:  3](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 3; setting this bit resets all of the BMAN 3 internal
                                                                 registers */
        uint32_t b4_rst                : 1;  /**< [  4:  4](R/W) The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to
                                                                 0Software reset for BMAN 4; setting this bit resets all of the BMAN 4 internal
                                                                 registers */
        uint32_t b5_rst                : 1;  /**< [  5:  5](R/W) Software reset for BMAN 5; setting this bit resets all of the BMAN 5 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b6_rst                : 1;  /**< [  6:  6](R/W) Software reset for BMAN 6; setting this bit resets all of the BMAN 6 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t b7_rst                : 1;  /**< [  7:  7](R/W) Software reset for BMAN 7; setting this bit resets all of the BMAN 7 internal registers
                                                                 The user must keep the BMAN at reset until BMAN configuration is completed.
                                                                 When DMSS is hardware-configured without BMANs this field is hardwired to 0 */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_bman_rst_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_bman_rst_reg bdk_cbpx_qman_bman_cntrl_bman_rst_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227f8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(a) bdk_cbpx_qman_bman_cntrl_bman_rst_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(a) "CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_BMAN_RST_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_dsp_pkt_size_reg
 *
 * CBP Qman Bman Cntrl Dsp Pkt Size Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t dsp_pkt_size          : 16; /**< [ 15:  0](R/W) CEVA-XC4000 read packet size (bytes).
                                                                 The DSP writes the size of the packet it is about to read from the buffer.
                                                                 This register decrease with every read performed by the DSP.
                                                                 When only the last bytes of the packet are available in the buffer this register
                                                                 replaces the DSP_RD_THLD enabling the DSP to keep reading until the last bytes
                                                                 of the packet is read from the buffer. */
#else /* Word 0 - Little Endian */
        uint32_t dsp_pkt_size          : 16; /**< [ 15:  0](R/W) CEVA-XC4000 read packet size (bytes).
                                                                 The DSP writes the size of the packet it is about to read from the buffer.
                                                                 This register decrease with every read performed by the DSP.
                                                                 When only the last bytes of the packet are available in the buffer this register
                                                                 replaces the DSP_RD_THLD enabling the DSP to keep reading until the last bytes
                                                                 of the packet is read from the buffer. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227e8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(a) bdk_cbpx_qman_bman_cntrl_dsp_pkt_size_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(a) "CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_DSP_PKT_SIZE_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_qbman_irq_status_reg
 *
 * CBP Qman Bman Cntrl Qbman Irq Status Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t bman_irq_status       : 1;  /**< [ 17: 17](R/W/H) BMAN interrupt status.
                                                                 This bit is set when a selected buffer read or write pointers reach a
                                                                 preconfigured address or when the buffer used by the DSP is almost empty.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
        uint32_t fnum_vi               : 1;  /**< [ 16: 16](R/W/H) Frame number violation interrupt status.
                                                                 This bit is set when two or more tasks are accessing the queue arbitration with
                                                                 same absolute priority and non-consecutive frame number.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
        uint32_t reserved_12_15        : 4;
        uint32_t empty_vi              : 12; /**< [ 11:  0](R/W/H) Queue empty violation interrupt status.
                                                                 Each bit is used as an empty violation interrupt status.
                                                                 Each bit is set if the corresponding queue is empty and its enabled task counter
                                                                 indicates active tasks in the queue.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
#else /* Word 0 - Little Endian */
        uint32_t empty_vi              : 12; /**< [ 11:  0](R/W/H) Queue empty violation interrupt status.
                                                                 Each bit is used as an empty violation interrupt status.
                                                                 Each bit is set if the corresponding queue is empty and its enabled task counter
                                                                 indicates active tasks in the queue.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
        uint32_t reserved_12_15        : 4;
        uint32_t fnum_vi               : 1;  /**< [ 16: 16](R/W/H) Frame number violation interrupt status.
                                                                 This bit is set when two or more tasks are accessing the queue arbitration with
                                                                 same absolute priority and non-consecutive frame number.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
        uint32_t bman_irq_status       : 1;  /**< [ 17: 17](R/W/H) BMAN interrupt status.
                                                                 This bit is set when a selected buffer read or write pointers reach a
                                                                 preconfigured address or when the buffer used by the DSP is almost empty.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register bit. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227f0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(a) bdk_cbpx_qman_bman_cntrl_qbman_irq_status_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(a) "CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_QBMAN_IRQ_STATUS_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_qman_active_reg
 *
 * CBP Qman Bman Cntrl Qman Active Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_qman_active_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_qman_active_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_28_31        : 4;
        uint32_t q11_active            : 1;  /**< [ 27: 27](RO/H) Queue 11 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q10_active            : 1;  /**< [ 26: 26](RO/H) Queue 10 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q9_active             : 1;  /**< [ 25: 25](RO/H) Queue 9 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q8_active             : 1;  /**< [ 24: 24](RO/H) Queue 8 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q7_active             : 1;  /**< [ 23: 23](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q6_active             : 1;  /**< [ 22: 22](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q5_active             : 1;  /**< [ 21: 21](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q4_active             : 1;  /**< [ 20: 20](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q3_active             : 1;  /**< [ 19: 19](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q2_active             : 1;  /**< [ 18: 18](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q1_active             : 1;  /**< [ 17: 17](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q0_active             : 1;  /**< [ 16: 16](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t reserved_12_15        : 4;
        uint32_t q11_idm_cros          : 1;  /**< [ 11: 11](R/W/H) Error indication QMAN11 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q10_idm_cros          : 1;  /**< [ 10: 10](R/W/H) Error indication QMAN10 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q9_idm_cros           : 1;  /**< [  9:  9](R/W/H) Error indication QMAN9 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q8_idm_cros           : 1;  /**< [  8:  8](R/W/H) Error indication QMAN8 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q7_idm_cros           : 1;  /**< [  7:  7](R/W/H) Error indication QMAN7 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q6_idm_cros           : 1;  /**< [  6:  6](R/W/H) Error indication QMAN6 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q5_idm_cros           : 1;  /**< [  5:  5](R/W/H) Error indication QMAN5 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q4_idm_cros           : 1;  /**< [  4:  4](R/W/H) Error indication QMAN4 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q3_idm_cros           : 1;  /**< [  3:  3](R/W/H) Error indication QMAN3 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q2_idm_cros           : 1;  /**< [  2:  2](R/W/H) Error indication QMAN2 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q1_idm_cros           : 1;  /**< [  1:  1](R/W/H) Error indication QMAN1 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q0_idm_cros           : 1;  /**< [  0:  0](R/W/H) Error indication QMAN0 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
#else /* Word 0 - Little Endian */
        uint32_t q0_idm_cros           : 1;  /**< [  0:  0](R/W/H) Error indication QMAN0 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q1_idm_cros           : 1;  /**< [  1:  1](R/W/H) Error indication QMAN1 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q2_idm_cros           : 1;  /**< [  2:  2](R/W/H) Error indication QMAN2 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q3_idm_cros           : 1;  /**< [  3:  3](R/W/H) Error indication QMAN3 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q4_idm_cros           : 1;  /**< [  4:  4](R/W/H) Error indication QMAN4 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q5_idm_cros           : 1;  /**< [  5:  5](R/W/H) Error indication QMAN5 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q6_idm_cros           : 1;  /**< [  6:  6](R/W/H) Error indication QMAN6 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q7_idm_cros           : 1;  /**< [  7:  7](R/W/H) Error indication QMAN7 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q8_idm_cros           : 1;  /**< [  8:  8](R/W/H) Error indication QMAN8 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q9_idm_cros           : 1;  /**< [  9:  9](R/W/H) Error indication QMAN9 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q10_idm_cros          : 1;  /**< [ 10: 10](R/W/H) Error indication QMAN10 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t q11_idm_cros          : 1;  /**< [ 11: 11](R/W/H) Error indication QMAN11 internal access crossed IDM last address.
                                                                 This bit is a sticky bit and is cleared by writing 1 to this register. */
        uint32_t reserved_12_15        : 4;
        uint32_t q0_active             : 1;  /**< [ 16: 16](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q1_active             : 1;  /**< [ 17: 17](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q2_active             : 1;  /**< [ 18: 18](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q3_active             : 1;  /**< [ 19: 19](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q4_active             : 1;  /**< [ 20: 20](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q5_active             : 1;  /**< [ 21: 21](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q6_active             : 1;  /**< [ 22: 22](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q7_active             : 1;  /**< [ 23: 23](RO/H) Queue 0 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q8_active             : 1;  /**< [ 24: 24](RO/H) Queue 8 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q9_active             : 1;  /**< [ 25: 25](RO/H) Queue 9 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q10_active            : 1;  /**< [ 26: 26](RO/H) Queue 10 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t q11_active            : 1;  /**< [ 27: 27](RO/H) Queue 11 active status indication.
                                                                 Indicates the status of the QMAN state machine.
                                                                 0-QMAN is not active
                                                                 1-QMAN is active */
        uint32_t reserved_28_31        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_qman_active_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_qman_active_reg bdk_cbpx_qman_bman_cntrl_qman_active_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227dcll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(a) bdk_cbpx_qman_bman_cntrl_qman_active_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(a) "CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_ACTIVE_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_qman_rst_reg
 *
 * CBP Qman Bman Cntrl Qman Rst Reg Register
 * Twelve QMANs hardware configuration - 0x0000_0FFF
 * 	Eight QMANs hardware configuration - 0x0000_00FF
 * 	Four QMANs hardware configuration - 0x0000_000F
 * 	Zero QMANs hardware configuration - 0x0000_0000
 */
union bdk_cbpx_qman_bman_cntrl_qman_rst_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_qman_rst_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t q7_rst                : 1;  /**< [  7:  7](R/W) Software reset for Queue 7.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q7_EN (Q7_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q6_rst                : 1;  /**< [  6:  6](R/W) Software reset for Queue 6.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q6_EN (Q6_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q5_rst                : 1;  /**< [  5:  5](R/W) Software reset for Queue 5.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q5_EN (Q5_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q4_rst                : 1;  /**< [  4:  4](R/W) Software reset for Queue 4.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q4_EN (Q4_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q3_rst                : 1;  /**< [  3:  3](R/W) Software reset for Queue 3.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q3_EN (Q3_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q2_rst                : 1;  /**< [  2:  2](R/W) Software reset for Queue 2.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q2_EN (Q2_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q1_rst                : 1;  /**< [  1:  1](R/W) Software reset for Queue 1.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q1_EN (Q1_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q0_rst                : 1;  /**< [  0:  0](R/W) Software reset for Queue 0.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q0_EN (Q0_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
#else /* Word 0 - Little Endian */
        uint32_t q0_rst                : 1;  /**< [  0:  0](R/W) Software reset for Queue 0.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q0_EN (Q0_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q1_rst                : 1;  /**< [  1:  1](R/W) Software reset for Queue 1.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q1_EN (Q1_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q2_rst                : 1;  /**< [  2:  2](R/W) Software reset for Queue 2.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q2_EN (Q2_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q3_rst                : 1;  /**< [  3:  3](R/W) Software reset for Queue 3.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q3_EN (Q3_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q4_rst                : 1;  /**< [  4:  4](R/W) Software reset for Queue 4.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q4_EN (Q4_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q5_rst                : 1;  /**< [  5:  5](R/W) Software reset for Queue 5.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q5_EN (Q5_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q6_rst                : 1;  /**< [  6:  6](R/W) Software reset for Queue 6.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q6_EN (Q6_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t q7_rst                : 1;  /**< [  7:  7](R/W) Software reset for Queue 7.
                                                                  Setting this bit resets all of the queue internal registers. Setting this bit
                                                                 does not reset the Queue configuration registers except Q7_EN (Q7_EN is reset to
                                                                 0 when this bit is set)
                                                                 When DMSS is hardware-configured without QMANs this field is hardwired to 0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_qman_rst_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_qman_rst_reg bdk_cbpx_qman_bman_cntrl_qman_rst_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227f4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(a) bdk_cbpx_qman_bman_cntrl_qman_rst_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(a) "CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_RST_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_qman_bman_cntrl_qman_vi_mask_reg
 *
 * CBP Qman Bman Cntrl Qman Vi Mask Reg Register
 */
union bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg
{
    uint32_t u;
    struct bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t fnum_vi_mask          : 1;  /**< [ 16: 16](R/W) Frame number violation interrupt mask
                                                                 This bit indicates whether the QMAN can set the qman_vi_irq interrupt when two
                                                                 or more tasks are accessing the queue arbitration with same absolute priority
                                                                 and non-consecutive frame number.
                                                                 0- interrupt is enabled
                                                                 1- interrupt is disabled */
        uint32_t reserved_12_15        : 4;
        uint32_t empty_vi_mask         : 12; /**< [ 11:  0](R/W) Queue empty violation interrupt Mask
                                                                 Each bit is used as an empty violation interrupt mask.
                                                                 Each bit indicates whether the corresponding queue can set the qman_vi_irq
                                                                 interrupt when it is empty and its enabled task counter indicates active tasks
                                                                 in the queue.
                                                                 0- interrupt is enabled
                                                                 1- interrupt is disabled

                                                                 When DMSS is hardware-configured to eight QMANs the four MS Bits of this field are hardwired to 0. */
#else /* Word 0 - Little Endian */
        uint32_t empty_vi_mask         : 12; /**< [ 11:  0](R/W) Queue empty violation interrupt Mask
                                                                 Each bit is used as an empty violation interrupt mask.
                                                                 Each bit indicates whether the corresponding queue can set the qman_vi_irq
                                                                 interrupt when it is empty and its enabled task counter indicates active tasks
                                                                 in the queue.
                                                                 0- interrupt is enabled
                                                                 1- interrupt is disabled

                                                                 When DMSS is hardware-configured to eight QMANs the four MS Bits of this field are hardwired to 0. */
        uint32_t reserved_12_15        : 4;
        uint32_t fnum_vi_mask          : 1;  /**< [ 16: 16](R/W) Frame number violation interrupt mask
                                                                 This bit indicates whether the QMAN can set the qman_vi_irq interrupt when two
                                                                 or more tasks are accessing the queue arbitration with same absolute priority
                                                                 and non-consecutive frame number.
                                                                 0- interrupt is enabled
                                                                 1- interrupt is disabled */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg_s cn; */
};
typedef union bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg_t;

static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227ecll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(a) bdk_cbpx_qman_bman_cntrl_qman_vi_mask_reg_t
#define bustype_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(a) "CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG"
#define busnum_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(a) (a)
#define arguments_BDK_CBPX_QMAN_BMAN_CNTRL_QMAN_VI_MASK_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuedescriptor_qpush_dsc_ext_ptr_reg
 *
 * CBP Queuedescriptor Qpush Dsc Ext Ptr Reg Register
 */
union bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qpush_dsc_ext_ptr     : 32; /**< [ 31:  0](R/W) 32 LSBs of the new descriptor to be pushed into a queue.
                                                                 Contains the External address pointer descriptor field to be pushed into a queue. */
#else /* Word 0 - Little Endian */
        uint32_t qpush_dsc_ext_ptr     : 32; /**< [ 31:  0](R/W) 32 LSBs of the new descriptor to be pushed into a queue.
                                                                 Contains the External address pointer descriptor field to be pushed into a queue. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg_s cn; */
};
typedef union bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227c0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(a) bdk_cbpx_queuedescriptor_qpush_dsc_ext_ptr_reg_t
#define bustype_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(a) "CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG"
#define busnum_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(a) (a)
#define arguments_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_EXT_PTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuedescriptor_qpush_dsc_int_ptr_reg
 *
 * CBP Queuedescriptor Qpush Dsc Int Ptr Reg Register
 */
union bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qpush_dsc_int_ptr     : 32; /**< [ 31:  0](R/W) Bits [63:32] of the new descriptor to be pushed into a queue
                                                                 Contains the internal address pointer descriptor field to be pushed into a queue */
#else /* Word 0 - Little Endian */
        uint32_t qpush_dsc_int_ptr     : 32; /**< [ 31:  0](R/W) Bits [63:32] of the new descriptor to be pushed into a queue
                                                                 Contains the internal address pointer descriptor field to be pushed into a queue */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg_s cn; */
};
typedef union bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227c4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(a) bdk_cbpx_queuedescriptor_qpush_dsc_int_ptr_reg_t
#define bustype_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(a) "CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG"
#define busnum_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(a) (a)
#define arguments_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_INT_PTR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuedescriptor_qpush_dsc_tctl_reg
 *
 * CBP Queuedescriptor Qpush Dsc Tctl Reg Register
 */
union bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg
{
    uint32_t u;
    struct bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qpush_dsc_tctl        : 32; /**< [ 31:  0](R/W) Bits [95:64] of the new descriptor to be pushed into a queue
                                                                 Contains the TCTL related descriptor fields to be pushed into a queue */
#else /* Word 0 - Little Endian */
        uint32_t qpush_dsc_tctl        : 32; /**< [ 31:  0](R/W) Bits [95:64] of the new descriptor to be pushed into a queue
                                                                 Contains the TCTL related descriptor fields to be pushed into a queue */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg_s cn; */
};
typedef union bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg_t;

static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227c8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(a) bdk_cbpx_queuedescriptor_qpush_dsc_tctl_reg_t
#define bustype_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(a) "CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG"
#define busnum_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(a) (a)
#define arguments_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TCTL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuedescriptor_qpush_dsc_tframe_len_reg
 *
 * CBP Queuedescriptor Qpush Dsc Tframe Len Reg Register
 */
union bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg
{
    uint32_t u;
    struct bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t qpush_dsc_tframe_len  : 8;  /**< [  7:  0](R/W) Bits [127:96] of the new descriptor to be pushed into a queue
                                                                 Contains the TFRAME_LEN descriptor field to be pushed into a queue */
#else /* Word 0 - Little Endian */
        uint32_t qpush_dsc_tframe_len  : 8;  /**< [  7:  0](R/W) Bits [127:96] of the new descriptor to be pushed into a queue
                                                                 Contains the TFRAME_LEN descriptor field to be pushed into a queue */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg_s cn; */
};
typedef union bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg_t;

static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227ccll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(a) bdk_cbpx_queuedescriptor_qpush_dsc_tframe_len_reg_t
#define bustype_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(a) "CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG"
#define busnum_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(a) (a)
#define arguments_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_DSC_TFRAME_LEN_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuedescriptor_qpush_num_reg
 *
 * CBP Queuedescriptor Qpush Num Reg Register
 */
union bdk_cbpx_queuedescriptor_qpush_num_reg
{
    uint32_t u;
    struct bdk_cbpx_queuedescriptor_qpush_num_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t qpush_status          : 1;  /**< [ 17: 17](RO/H) Read Only register used for indication of the status of the simplified interface.
                                                                 0  the simplified interface is IDLE
                                                                 1  the simplified interface is BUSY writing the task to the queue (writing new
                                                                 task and read-modify-write for WPTR) */
        uint32_t qpush_status_rls      : 1;  /**< [ 16: 16](WO) Writing 0x1 to this register releases all QX_STATUS registers to show the real
                                                                 status of the queues without pushing a new descriptor to a queue. */
        uint32_t reserved_4_15         : 12;
        uint32_t qpush_num             : 4;  /**< [  3:  0](R/W) Write to this register triggers a push operation of the DDMA descriptor written
                                                                 in QPUSH_DSC_EXT_PTR,QPUSH_DSC_INT_PTR,QPUSH_DSC_TCTL and QPUSH_DSC_TFRAME_LEN
                                                                 configuration registers into the queue number QPUSH_NUM
                                                                 Writes to this register are ignored (push operation is canceled) if the
                                                                 QPUSH_STATUS_RLS field is set. */
#else /* Word 0 - Little Endian */
        uint32_t qpush_num             : 4;  /**< [  3:  0](R/W) Write to this register triggers a push operation of the DDMA descriptor written
                                                                 in QPUSH_DSC_EXT_PTR,QPUSH_DSC_INT_PTR,QPUSH_DSC_TCTL and QPUSH_DSC_TFRAME_LEN
                                                                 configuration registers into the queue number QPUSH_NUM
                                                                 Writes to this register are ignored (push operation is canceled) if the
                                                                 QPUSH_STATUS_RLS field is set. */
        uint32_t reserved_4_15         : 12;
        uint32_t qpush_status_rls      : 1;  /**< [ 16: 16](WO) Writing 0x1 to this register releases all QX_STATUS registers to show the real
                                                                 status of the queues without pushing a new descriptor to a queue. */
        uint32_t qpush_status          : 1;  /**< [ 17: 17](RO/H) Read Only register used for indication of the status of the simplified interface.
                                                                 0  the simplified interface is IDLE
                                                                 1  the simplified interface is BUSY writing the task to the queue (writing new
                                                                 task and read-modify-write for WPTR) */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuedescriptor_qpush_num_reg_s cn; */
};
typedef union bdk_cbpx_queuedescriptor_qpush_num_reg bdk_cbpx_queuedescriptor_qpush_num_reg_t;

static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448227d0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(a) bdk_cbpx_queuedescriptor_qpush_num_reg_t
#define bustype_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(a) "CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG"
#define busnum_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(a) (a)
#define arguments_BDK_CBPX_QUEUEDESCRIPTOR_QPUSH_NUM_REG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_base_ptr_reg
 *
 * CBP Queuemanager Q Base Ptr Reg Register
 */
union bdk_cbpx_queuemanager_qx_base_ptr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_base_ptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_base_ptr           : 32; /**< [ 31:  0](R/W) A base pointer (pointer to pointer) used as a pointer to queue X read and write pointers.
                                                                 The read and write pointers of the queue are located in a RAM (IDM or external RAM).
                                                                 The user can directly access these pointers for reading.
                                                                 The user can directly push new descriptors to the queue provided that the
                                                                 descriptor push interface was never used.
                                                                 The data structure is used at the location of *QX_BASE_PTR
                                                                 *QX_BASE_PTR : QX_RPTR
                                                                 *(Q0BASE_PTR+4) : QX_LAST_CORE_ID RAM
                                                                 *(Q0BASE_PTR+8) :QX_WPTR
                                                                 The four LSBs of this register are always replaced with 4h0 (QX_RPTR is 16 Byte aligned) */
#else /* Word 0 - Little Endian */
        uint32_t qx_base_ptr           : 32; /**< [ 31:  0](R/W) A base pointer (pointer to pointer) used as a pointer to queue X read and write pointers.
                                                                 The read and write pointers of the queue are located in a RAM (IDM or external RAM).
                                                                 The user can directly access these pointers for reading.
                                                                 The user can directly push new descriptors to the queue provided that the
                                                                 descriptor push interface was never used.
                                                                 The data structure is used at the location of *QX_BASE_PTR
                                                                 *QX_BASE_PTR : QX_RPTR
                                                                 *(Q0BASE_PTR+4) : QX_LAST_CORE_ID RAM
                                                                 *(Q0BASE_PTR+8) :QX_WPTR
                                                                 The four LSBs of this register are always replaced with 4h0 (QX_RPTR is 16 Byte aligned) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_base_ptr_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_base_ptr_reg bdk_cbpx_queuemanager_qx_base_ptr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822808ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_BASE_PTR_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(a,b) bdk_cbpx_queuemanager_qx_base_ptr_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(a,b) "CBPX_QUEUEMANAGER_QX_BASE_PTR_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_BASE_PTR_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_chnk_size_reg
 *
 * CBP Queuemanager Q Chnk Size Reg Register
 */
union bdk_cbpx_queuemanager_qx_chnk_size_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_chnk_size_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t qx_chnk_size          : 14; /**< [ 13:  0](R/W) Indicates the size of a chunk used for activating the DDMA
                                                                 The chunk size is taken as QX_CHNK_SIZE * 128 Bytes */
#else /* Word 0 - Little Endian */
        uint32_t qx_chnk_size          : 14; /**< [ 13:  0](R/W) Indicates the size of a chunk used for activating the DDMA
                                                                 The chunk size is taken as QX_CHNK_SIZE * 128 Bytes */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_chnk_size_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_chnk_size_reg bdk_cbpx_queuemanager_qx_chnk_size_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e04482280cll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(a,b) bdk_cbpx_queuemanager_qx_chnk_size_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(a,b) "CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_CHNK_SIZE_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_desc_en_inc_reg
 *
 * CBP Queuemanager Q Desc En Inc Reg Register
 */
union bdk_cbpx_queuemanager_qx_desc_en_inc_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_desc_en_inc_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qx_desc_en            : 1;  /**< [ 16: 16](R/W) Queue X descriptor enable
                                                                 When written with 1 queue X enabled task counter (QX_EN_CNT) is incremented
                                                                 using the QX_EN_INC_VAL register.
                                                                 This field is automatically cleared to 0 after being written. */
        uint32_t reserved_6_15         : 10;
        uint32_t qx_en_inc_val         : 6;  /**< [  5:  0](R/W) Queue X descriptor enable counter
                                                                 The value written to this register is added to queue X enabled task counter
                                                                 (QX_EN_CNT) when the queue enable input signal is set (qX_desc_en) or when the
                                                                 QX_DESC_EN configuration register is written with 1.
                                                                 Up to 63 descriptors can be activated in a single QX_DESC_EN write operation or
                                                                 for each cycle were qX_desc_en is set. */
#else /* Word 0 - Little Endian */
        uint32_t qx_en_inc_val         : 6;  /**< [  5:  0](R/W) Queue X descriptor enable counter
                                                                 The value written to this register is added to queue X enabled task counter
                                                                 (QX_EN_CNT) when the queue enable input signal is set (qX_desc_en) or when the
                                                                 QX_DESC_EN configuration register is written with 1.
                                                                 Up to 63 descriptors can be activated in a single QX_DESC_EN write operation or
                                                                 for each cycle were qX_desc_en is set. */
        uint32_t reserved_6_15         : 10;
        uint32_t qx_desc_en            : 1;  /**< [ 16: 16](R/W) Queue X descriptor enable
                                                                 When written with 1 queue X enabled task counter (QX_EN_CNT) is incremented
                                                                 using the QX_EN_INC_VAL register.
                                                                 This field is automatically cleared to 0 after being written. */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_desc_en_inc_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_desc_en_inc_reg bdk_cbpx_queuemanager_qx_desc_en_inc_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822810ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(a,b) bdk_cbpx_queuemanager_qx_desc_en_inc_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(a,b) "CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_DESC_EN_INC_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_dsc_ext_ptr_reg
 *
 * CBP Queuemanager Q Dsc Ext Ptr Reg Register
 */
union bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_dsc_ext_ptr        : 32; /**< [ 31:  0](RO) Queue X external pointer from last used descriptor
                                                                 32 LSBs of the last used descriptor at queue X.
                                                                 Contains the External address pointer descriptor field.

                                                                 This registers gets the value of 0 after QX_RST is set */
#else /* Word 0 - Little Endian */
        uint32_t qx_dsc_ext_ptr        : 32; /**< [ 31:  0](RO) Queue X external pointer from last used descriptor
                                                                 32 LSBs of the last used descriptor at queue X.
                                                                 Contains the External address pointer descriptor field.

                                                                 This registers gets the value of 0 after QX_RST is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e04482281cll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(a,b) bdk_cbpx_queuemanager_qx_dsc_ext_ptr_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(a,b) "CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_DSC_EXT_PTR_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_dsc_int_ptr_reg
 *
 * CBP Queuemanager Q Dsc Int Ptr Reg Register
 */
union bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_dsc_int_ptr        : 32; /**< [ 31:  0](RO) Queue X internal pointer from last used descriptor
                                                                 Bits [63:32] of the last used descriptor at queue X.
                                                                 Contains the internal address pointer descriptor field.

                                                                 This registers gets the value of 0 after QX_RST  is set */
#else /* Word 0 - Little Endian */
        uint32_t qx_dsc_int_ptr        : 32; /**< [ 31:  0](RO) Queue X internal pointer from last used descriptor
                                                                 Bits [63:32] of the last used descriptor at queue X.
                                                                 Contains the internal address pointer descriptor field.

                                                                 This registers gets the value of 0 after QX_RST  is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822820ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(a,b) bdk_cbpx_queuemanager_qx_dsc_int_ptr_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(a,b) "CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_DSC_INT_PTR_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_dsc_tctl_reg
 *
 * CBP Queuemanager Q Dsc Tctl Reg Register
 */
union bdk_cbpx_queuemanager_qx_dsc_tctl_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_dsc_tctl_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_dsc_tctl           : 32; /**< [ 31:  0](RO) Queue X internal transfer size from last used descriptor
                                                                 Bits [95:64] of the last used descriptor at queue X.
                                                                 Contains the TCTL related descriptor fields.

                                                                 This register gets the value of 0 after QX_RST is set */
#else /* Word 0 - Little Endian */
        uint32_t qx_dsc_tctl           : 32; /**< [ 31:  0](RO) Queue X internal transfer size from last used descriptor
                                                                 Bits [95:64] of the last used descriptor at queue X.
                                                                 Contains the TCTL related descriptor fields.

                                                                 This register gets the value of 0 after QX_RST is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_dsc_tctl_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_dsc_tctl_reg bdk_cbpx_queuemanager_qx_dsc_tctl_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822824ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(a,b) bdk_cbpx_queuemanager_qx_dsc_tctl_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(a,b) "CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_DSC_TCTL_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_dsc_tframe_len_reg
 *
 * CBP Queuemanager Q Dsc Tframe Len Reg Register
 */
union bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_dsc_tframe_len     : 32; /**< [ 31:  0](RO) Queue X task frame length from last used descriptor
                                                                 Bits [127:96] of the last used descriptor at queue X.
                                                                 Contains the TFRAME_LEN descriptor field.

                                                                 This registers gets the value of 0 after QX_RST is set */
#else /* Word 0 - Little Endian */
        uint32_t qx_dsc_tframe_len     : 32; /**< [ 31:  0](RO) Queue X task frame length from last used descriptor
                                                                 Bits [127:96] of the last used descriptor at queue X.
                                                                 Contains the TFRAME_LEN descriptor field.

                                                                 This registers gets the value of 0 after QX_RST is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822828ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(a,b) bdk_cbpx_queuemanager_qx_dsc_tframe_len_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(a,b) "CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_DSC_TFRAME_LEN_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_en_depth_reg
 *
 * CBP Queuemanager Q En Depth Reg Register
 */
union bdk_cbpx_queuemanager_qx_en_depth_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_en_depth_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_en                 : 1;  /**< [ 31: 31](R/W) Enable bit for activating the queue.
                                                                 0-Queue is disabled
                                                                 1-Queue is enabled
                                                                 This register is used for activating the queue after all other configuration
                                                                 registers and data base variables are initialized and the queue is loaded with
                                                                 at least one descriptor.
                                                                 This bit is reset automatically when the queue is empty (QX_RPTR==QX_WPTR) and
                                                                 the queue enabled counter (QXEN_CNT) indicates queue contains enabled tasks.
                                                                 Manually resetting this register disables the queue from attempting to send new
                                                                 tasks to DDMA (tasks in the DDMA or tasks pending in the QMAN arbitration are
                                                                 not affected by this bit)
                                                                 This registers gets the value of 0 after QX_RST is set */
        uint32_t qx_cont_frame         : 1;  /**< [ 30: 30](R/W) Enable the QMAN to continue reading new task descriptors before completely
                                                                 processing the last task of the previous frame
                                                                 0-The QMAN stalls at the last task of the TFrame, waiting for it to complete
                                                                 before accessing the queue to read the next task TFrame.
                                                                 1-The QMAN continues reading the next task without waiting for the last task at
                                                                 the previous TFrame to complete.
                                                                 When using a shared queue, it is advisable to set QX_CONT_FRAME=0. This prevents
                                                                 the QMAN from seizing a new TFrame before completing the previous one. */
        uint32_t reserved_13_29        : 17;
        uint32_t qx_depth              : 13; /**< [ 12:  0](R/W) The number of DMA descriptors that Queue X can hold. It is restricted to
                                                                 configure QX_DEPTH to 0 or 1.
                                                                 Each descriptor consumes 16 bytes.
                                                                 The queue contains up to QX_DEPTH+1 descriptors.
                                                                 When writing descriptors to the queue (not using the simplified interface) the
                                                                 user should not write more than QX_DEPTH descriptors. */
#else /* Word 0 - Little Endian */
        uint32_t qx_depth              : 13; /**< [ 12:  0](R/W) The number of DMA descriptors that Queue X can hold. It is restricted to
                                                                 configure QX_DEPTH to 0 or 1.
                                                                 Each descriptor consumes 16 bytes.
                                                                 The queue contains up to QX_DEPTH+1 descriptors.
                                                                 When writing descriptors to the queue (not using the simplified interface) the
                                                                 user should not write more than QX_DEPTH descriptors. */
        uint32_t reserved_13_29        : 17;
        uint32_t qx_cont_frame         : 1;  /**< [ 30: 30](R/W) Enable the QMAN to continue reading new task descriptors before completely
                                                                 processing the last task of the previous frame
                                                                 0-The QMAN stalls at the last task of the TFrame, waiting for it to complete
                                                                 before accessing the queue to read the next task TFrame.
                                                                 1-The QMAN continues reading the next task without waiting for the last task at
                                                                 the previous TFrame to complete.
                                                                 When using a shared queue, it is advisable to set QX_CONT_FRAME=0. This prevents
                                                                 the QMAN from seizing a new TFrame before completing the previous one. */
        uint32_t qx_en                 : 1;  /**< [ 31: 31](R/W) Enable bit for activating the queue.
                                                                 0-Queue is disabled
                                                                 1-Queue is enabled
                                                                 This register is used for activating the queue after all other configuration
                                                                 registers and data base variables are initialized and the queue is loaded with
                                                                 at least one descriptor.
                                                                 This bit is reset automatically when the queue is empty (QX_RPTR==QX_WPTR) and
                                                                 the queue enabled counter (QXEN_CNT) indicates queue contains enabled tasks.
                                                                 Manually resetting this register disables the queue from attempting to send new
                                                                 tasks to DDMA (tasks in the DDMA or tasks pending in the QMAN arbitration are
                                                                 not affected by this bit)
                                                                 This registers gets the value of 0 after QX_RST is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_en_depth_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_en_depth_reg bdk_cbpx_queuemanager_qx_en_depth_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822800ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(a,b) bdk_cbpx_queuemanager_qx_en_depth_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(a,b) "CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_EN_DEPTH_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_first_addr_reg
 *
 * CBP Queuemanager Q First Addr Reg Register
 */
union bdk_cbpx_queuemanager_qx_first_addr_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_first_addr_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_first_addr         : 32; /**< [ 31:  0](R/W) First address of queue X
                                                                 The queue uses wrap around FIFO addressing
                                                                 The four LSBs of this register are always replaced with 4h0 (Queue is 16 Byte aligned) */
#else /* Word 0 - Little Endian */
        uint32_t qx_first_addr         : 32; /**< [ 31:  0](R/W) First address of queue X
                                                                 The queue uses wrap around FIFO addressing
                                                                 The four LSBs of this register are always replaced with 4h0 (Queue is 16 Byte aligned) */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_first_addr_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_first_addr_reg bdk_cbpx_queuemanager_qx_first_addr_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822804ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(a,b) bdk_cbpx_queuemanager_qx_first_addr_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(a,b) "CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_FIRST_ADDR_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#_rptr_int_reg
 *
 * CBP Queuemanager Q Rptr Int Reg Register
 */
union bdk_cbpx_queuemanager_qx_rptr_int_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qx_rptr_int_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qx_rptr_int           : 17; /**< [ 16:  0](RO) Queue X internal queues read pointer.
                                                                 This register is reset with the value of 0 when QX_RST configuration register is set.
                                                                 The QX_RPTR_INT is 16 bytes aligned (QX_RPTR_INT [3:0]=0x0).
                                                                 This registers gets the value of 0 after QX_RST is set. */
#else /* Word 0 - Little Endian */
        uint32_t qx_rptr_int           : 17; /**< [ 16:  0](RO) Queue X internal queues read pointer.
                                                                 This register is reset with the value of 0 when QX_RST configuration register is set.
                                                                 The QX_RPTR_INT is 16 bytes aligned (QX_RPTR_INT [3:0]=0x0).
                                                                 This registers gets the value of 0 after QX_RST is set. */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qx_rptr_int_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qx_rptr_int_reg bdk_cbpx_queuemanager_qx_rptr_int_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822818ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QX_RPTR_INT_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(a,b) bdk_cbpx_queuemanager_qx_rptr_int_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(a,b) "CBPX_QUEUEMANAGER_QX_RPTR_INT_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QX_RPTR_INT_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_queuemanager_q#en_cnt_reg
 *
 * CBP Queuemanager Qen Cnt Reg Register
 */
union bdk_cbpx_queuemanager_qxen_cnt_reg
{
    uint32_t u;
    struct bdk_cbpx_queuemanager_qxen_cnt_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qx_status             : 1;  /**< [ 31: 31](RO) Queue X status indication.
                                                                 This register indicates a queue full status.
                                                                 Queue not full
                                                                 Queue full
                                                                 This bit is used as a semaphore for using the queue descriptor push configuration registers.
                                                                 if QX_STATUS returns a value of "0" the semaphore is locked and any other read
                                                                 of QX_STATUS (where X can be any queue number) will return the value of "1".
                                                                 The semaphore is released only after a new task descriptor is pushed to the
                                                                 queue (by writing to the QPUSH_NUM register).
                                                                 Alternatively it is possible to release the semaphore by writing the value of
                                                                 "1" to the QPUSH_STATUS_RLS field at the QPUSH_NUM register (new task is not
                                                                 pushed to the queue).
                                                                 A user attempting to push a new descriptor to queue X must first read this
                                                                 register and only if the queue is not full it may write the new descriptor to
                                                                 QPUSH_DSC_EXT_PTR, QPUSH_DSC_INT_PTR,QPUSH_DSC_TCTL and QPUSH_DSC_TFRAME_LEN
                                                                 followed by writing queue number to the QPUSH_NUM register.
                                                                 This registe gets the value of 0 after QX_RST is set */
        uint32_t qx_wd_wait_f          : 1;  /**< [ 30: 30](RO/H) Indicates queue X is in a wait state until an upload transaction completes.
                                                                 Queue X waits for this bit to be reset before continue with the next task in the queue. */
        uint32_t reserved_14_29        : 16;
        uint32_t qx_en_cnt             : 14; /**< [ 13:  0](RO/H) Queue X descriptor enable counter
                                                                 This counter indicates the number of enabled descriptors in the queue.
                                                                 This registers gets the value of 0 after QX_RST is set */
#else /* Word 0 - Little Endian */
        uint32_t qx_en_cnt             : 14; /**< [ 13:  0](RO/H) Queue X descriptor enable counter
                                                                 This counter indicates the number of enabled descriptors in the queue.
                                                                 This registers gets the value of 0 after QX_RST is set */
        uint32_t reserved_14_29        : 16;
        uint32_t qx_wd_wait_f          : 1;  /**< [ 30: 30](RO/H) Indicates queue X is in a wait state until an upload transaction completes.
                                                                 Queue X waits for this bit to be reset before continue with the next task in the queue. */
        uint32_t qx_status             : 1;  /**< [ 31: 31](RO) Queue X status indication.
                                                                 This register indicates a queue full status.
                                                                 Queue not full
                                                                 Queue full
                                                                 This bit is used as a semaphore for using the queue descriptor push configuration registers.
                                                                 if QX_STATUS returns a value of "0" the semaphore is locked and any other read
                                                                 of QX_STATUS (where X can be any queue number) will return the value of "1".
                                                                 The semaphore is released only after a new task descriptor is pushed to the
                                                                 queue (by writing to the QPUSH_NUM register).
                                                                 Alternatively it is possible to release the semaphore by writing the value of
                                                                 "1" to the QPUSH_STATUS_RLS field at the QPUSH_NUM register (new task is not
                                                                 pushed to the queue).
                                                                 A user attempting to push a new descriptor to queue X must first read this
                                                                 register and only if the queue is not full it may write the new descriptor to
                                                                 QPUSH_DSC_EXT_PTR, QPUSH_DSC_INT_PTR,QPUSH_DSC_TCTL and QPUSH_DSC_TFRAME_LEN
                                                                 followed by writing queue number to the QPUSH_NUM register.
                                                                 This registe gets the value of 0 after QX_RST is set */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_queuemanager_qxen_cnt_reg_s cn; */
};
typedef union bdk_cbpx_queuemanager_qxen_cnt_reg bdk_cbpx_queuemanager_qxen_cnt_reg_t;

static inline uint64_t BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=15) && (b<=7)))
        return 0x87e044822814ll + 0x40000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7);
    __bdk_csr_fatal("CBPX_QUEUEMANAGER_QXEN_CNT_REG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(a,b) bdk_cbpx_queuemanager_qxen_cnt_reg_t
#define bustype_BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(a,b) "CBPX_QUEUEMANAGER_QXEN_CNT_REG"
#define busnum_BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(a,b) (a)
#define arguments_BDK_CBPX_QUEUEMANAGER_QXEN_CNT_REG(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) cbp#_swou_barrier
 *
 * CBP Swou Barrier Register
 */
union bdk_cbpx_swou_barrier
{
    uint32_t u;
    struct bdk_cbpx_swou_barrier_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t int_act               : 1;  /**< [  7:  7](R/W) Internal Barrier Activation:
                                                                 0: no barrier operation or operation completed
                                                                 1: barrier operation performing on the port
                                                                 This bit is cleared by hardware after the operation completes */
        uint32_t axdomain_f            : 2;  /**< [  6:  5](R/W) Barrier Activation AxDOMAIN value for read and write transactions */
        uint32_t axprot                : 3;  /**< [  4:  2](R/W) Barrier Activation AxPROT value for read and write transactions */
        uint32_t axi_act               : 1;  /**< [  1:  1](R/W) AXI Barrier Activation:
                                                                 0: no barrier operation or operation completed
                                                                 1: barrier operation performing on the port
                                                                 This bit is cleared by hardware after the operation completes */
        uint32_t axi_bar               : 1;  /**< [  0:  0](R/W) External system:
                                                                 0: Memory barrier
                                                                 1: synchronization barrier */
#else /* Word 0 - Little Endian */
        uint32_t axi_bar               : 1;  /**< [  0:  0](R/W) External system:
                                                                 0: Memory barrier
                                                                 1: synchronization barrier */
        uint32_t axi_act               : 1;  /**< [  1:  1](R/W) AXI Barrier Activation:
                                                                 0: no barrier operation or operation completed
                                                                 1: barrier operation performing on the port
                                                                 This bit is cleared by hardware after the operation completes */
        uint32_t axprot                : 3;  /**< [  4:  2](R/W) Barrier Activation AxPROT value for read and write transactions */
        uint32_t axdomain_f            : 2;  /**< [  6:  5](R/W) Barrier Activation AxDOMAIN value for read and write transactions */
        uint32_t int_act               : 1;  /**< [  7:  7](R/W) Internal Barrier Activation:
                                                                 0: no barrier operation or operation completed
                                                                 1: barrier operation performing on the port
                                                                 This bit is cleared by hardware after the operation completes */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_swou_barrier_s cn; */
};
typedef union bdk_cbpx_swou_barrier bdk_cbpx_swou_barrier_t;

static inline uint64_t BDK_CBPX_SWOU_BARRIER(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_SWOU_BARRIER(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482334cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_SWOU_BARRIER", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_SWOU_BARRIER(a) bdk_cbpx_swou_barrier_t
#define bustype_BDK_CBPX_SWOU_BARRIER(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_SWOU_BARRIER(a) "CBPX_SWOU_BARRIER"
#define busnum_BDK_CBPX_SWOU_BARRIER(a) (a)
#define arguments_BDK_CBPX_SWOU_BARRIER(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_swou_ccocr
 *
 * CBP Swou Ccocr Register
 * Note: In the case of no-cache hardware configuration, this register is read-only and
 * is tied to 0x0.
 */
union bdk_cbpx_swou_ccocr
{
    uint32_t u;
    struct bdk_cbpx_swou_ccocr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t nospl                 : 16; /**< [ 31: 16](R/W) Number of cache lines per line */
        uint32_t reserved_8_15         : 8;
        uint32_t os                    : 1;  /**< [  7:  7](R/W) Operation Size:
                                                                 0: Address-based
                                                                 1: Entire cache */
        uint32_t reserved_6            : 1;
        uint32_t ot                    : 4;  /**< [  5:  2](R/W) Operation Type:
                                                                 0001: Pre-fetched
                                                                 0010: Lock
                                                                 0011: Unlock
                                                                 0100: Invalidate
                                                                 0101: Flush
                                                                 0110: Flush and Invalidate */
        uint32_t l1dco                 : 1;  /**< [  1:  1](R/W) L1 Data cache operation:
                                                                 0: No operation or operation completed
                                                                 1: Operation performed on L1 Data cache
                                                                 This bit is cleared by hardware after the operation completes. */
        uint32_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0            : 1;
        uint32_t l1dco                 : 1;  /**< [  1:  1](R/W) L1 Data cache operation:
                                                                 0: No operation or operation completed
                                                                 1: Operation performed on L1 Data cache
                                                                 This bit is cleared by hardware after the operation completes. */
        uint32_t ot                    : 4;  /**< [  5:  2](R/W) Operation Type:
                                                                 0001: Pre-fetched
                                                                 0010: Lock
                                                                 0011: Unlock
                                                                 0100: Invalidate
                                                                 0101: Flush
                                                                 0110: Flush and Invalidate */
        uint32_t reserved_6            : 1;
        uint32_t os                    : 1;  /**< [  7:  7](R/W) Operation Size:
                                                                 0: Address-based
                                                                 1: Entire cache */
        uint32_t reserved_8_15         : 8;
        uint32_t nospl                 : 16; /**< [ 31: 16](R/W) Number of cache lines per line */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_swou_ccocr_s cn; */
};
typedef union bdk_cbpx_swou_ccocr bdk_cbpx_swou_ccocr_t;

static inline uint64_t BDK_CBPX_SWOU_CCOCR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_SWOU_CCOCR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823348ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_SWOU_CCOCR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_SWOU_CCOCR(a) bdk_cbpx_swou_ccocr_t
#define bustype_BDK_CBPX_SWOU_CCOCR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_SWOU_CCOCR(a) "CBPX_SWOU_CCOCR"
#define busnum_BDK_CBPX_SWOU_CCOCR(a) (a)
#define arguments_BDK_CBPX_SWOU_CCOCR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_swou_ccosar
 *
 * CBP Swou Ccosar Register
 * Note: In the case of no-cache hardware configuration, this register is read-only,
 * and is tied to 0x0.
 */
union bdk_cbpx_swou_ccosar
{
    uint32_t u;
    struct bdk_cbpx_swou_ccosar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ccosar                : 26; /**< [ 31:  6](R/W) Cache Operations Start Address. */
        uint32_t ccosar_lsb            : 6;  /**< [  5:  0](RO) Cache Operations Start Address LSB's (tied to 0x0). */
#else /* Word 0 - Little Endian */
        uint32_t ccosar_lsb            : 6;  /**< [  5:  0](RO) Cache Operations Start Address LSB's (tied to 0x0). */
        uint32_t ccosar                : 26; /**< [ 31:  6](R/W) Cache Operations Start Address. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_swou_ccosar_s cn; */
};
typedef union bdk_cbpx_swou_ccosar bdk_cbpx_swou_ccosar_t;

static inline uint64_t BDK_CBPX_SWOU_CCOSAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_SWOU_CCOSAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823340ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_SWOU_CCOSAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_SWOU_CCOSAR(a) bdk_cbpx_swou_ccosar_t
#define bustype_BDK_CBPX_SWOU_CCOSAR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_SWOU_CCOSAR(a) "CBPX_SWOU_CCOSAR"
#define busnum_BDK_CBPX_SWOU_CCOSAR(a) (a)
#define arguments_BDK_CBPX_SWOU_CCOSAR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_swou_ccoslr
 *
 * CBP Swou Ccoslr Register
 */
union bdk_cbpx_swou_ccoslr
{
    uint32_t u;
    struct bdk_cbpx_swou_ccoslr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ssz                   : 16; /**< [ 31: 16](R/W) Skip Size. Number of blocks to skip.
                                                                 During 1D operations, should be 0.
                                                                 During 2D operations, should contain the number of elements to skip over (must not be 0). */
        uint32_t nol                   : 16; /**< [ 15:  0](R/W) Number of lines (must not be 0). */
#else /* Word 0 - Little Endian */
        uint32_t nol                   : 16; /**< [ 15:  0](R/W) Number of lines (must not be 0). */
        uint32_t ssz                   : 16; /**< [ 31: 16](R/W) Skip Size. Number of blocks to skip.
                                                                 During 1D operations, should be 0.
                                                                 During 2D operations, should contain the number of elements to skip over (must not be 0). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_swou_ccoslr_s cn; */
};
typedef union bdk_cbpx_swou_ccoslr bdk_cbpx_swou_ccoslr_t;

static inline uint64_t BDK_CBPX_SWOU_CCOSLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_SWOU_CCOSLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044823344ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_SWOU_CCOSLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_SWOU_CCOSLR(a) bdk_cbpx_swou_ccoslr_t
#define bustype_BDK_CBPX_SWOU_CCOSLR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_SWOU_CCOSLR(a) "CBPX_SWOU_CCOSLR"
#define busnum_BDK_CBPX_SWOU_CCOSLR(a) (a)
#define arguments_BDK_CBPX_SWOU_CCOSLR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_uop_uop_par
 *
 * CBP Uop Uop Par Register
 * Note: Reading the UOP_STS clears all the bits in the register.
 */
union bdk_cbpx_uop_uop_par
{
    uint32_t u;
    struct bdk_cbpx_uop_uop_par_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t par                   : 32; /**< [ 31:  0](RO) Undefined Opcode Packet Address: This field contains the address of the last
                                                                 packet with undefined opcode in it. */
#else /* Word 0 - Little Endian */
        uint32_t par                   : 32; /**< [ 31:  0](RO) Undefined Opcode Packet Address: This field contains the address of the last
                                                                 packet with undefined opcode in it. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_uop_uop_par_s cn; */
};
typedef union bdk_cbpx_uop_uop_par bdk_cbpx_uop_uop_par_t;

static inline uint64_t BDK_CBPX_UOP_UOP_PAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_UOP_UOP_PAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482205cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_UOP_UOP_PAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_UOP_UOP_PAR(a) bdk_cbpx_uop_uop_par_t
#define bustype_BDK_CBPX_UOP_UOP_PAR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_UOP_UOP_PAR(a) "CBPX_UOP_UOP_PAR"
#define busnum_BDK_CBPX_UOP_UOP_PAR(a) (a)
#define arguments_BDK_CBPX_UOP_UOP_PAR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_uop_uop_sts
 *
 * CBP Uop Uop Sts Register
 * Note: Reading the UOP_STS clears all the bits in the register.
 */
union bdk_cbpx_uop_uop_sts
{
    uint32_t u;
    struct bdk_cbpx_uop_uop_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t mav                   : 1;  /**< [ 13: 13](RO) Memory Alignment Violation */
        uint32_t vmuop                 : 1;  /**< [ 12: 12](RO) VM unit Undefined Opcode */
        uint32_t vduop                 : 1;  /**< [ 11: 11](RO) VD unit Undefined Opcode */
        uint32_t vbuop                 : 1;  /**< [ 10: 10](RO) VB unit Undefined Opcode */
        uint32_t vauop                 : 1;  /**< [  9:  9](RO) VA unit Undefined Opcode */
        uint32_t pcuuop                : 1;  /**< [  8:  8](RO) PCU unit Undefined Opcode */
        uint32_t scuop                 : 1;  /**< [  7:  7](RO) SC unit Undefined Opcode */
        uint32_t luop                  : 1;  /**< [  6:  6](RO) L unit Undefined Opcode */
        uint32_t suop                  : 1;  /**< [  5:  5](RO) S unit Undefined Opcode */
        uint32_t m1uop                 : 1;  /**< [  4:  4](RO) M10 unit Undefined Opcode */
        uint32_t m0uop                 : 1;  /**< [  3:  3](RO) M0 unit Undefined Opcode */
        uint32_t ls1uop                : 1;  /**< [  2:  2](RO) LS1 unit Undefined Opcode */
        uint32_t ls0uop                : 1;  /**< [  1:  1](RO) LS0 unit Undefined Opcode */
        uint32_t syuop                 : 1;  /**< [  0:  0](RO) System-level Undefined Opcode */
#else /* Word 0 - Little Endian */
        uint32_t syuop                 : 1;  /**< [  0:  0](RO) System-level Undefined Opcode */
        uint32_t ls0uop                : 1;  /**< [  1:  1](RO) LS0 unit Undefined Opcode */
        uint32_t ls1uop                : 1;  /**< [  2:  2](RO) LS1 unit Undefined Opcode */
        uint32_t m0uop                 : 1;  /**< [  3:  3](RO) M0 unit Undefined Opcode */
        uint32_t m1uop                 : 1;  /**< [  4:  4](RO) M10 unit Undefined Opcode */
        uint32_t suop                  : 1;  /**< [  5:  5](RO) S unit Undefined Opcode */
        uint32_t luop                  : 1;  /**< [  6:  6](RO) L unit Undefined Opcode */
        uint32_t scuop                 : 1;  /**< [  7:  7](RO) SC unit Undefined Opcode */
        uint32_t pcuuop                : 1;  /**< [  8:  8](RO) PCU unit Undefined Opcode */
        uint32_t vauop                 : 1;  /**< [  9:  9](RO) VA unit Undefined Opcode */
        uint32_t vbuop                 : 1;  /**< [ 10: 10](RO) VB unit Undefined Opcode */
        uint32_t vduop                 : 1;  /**< [ 11: 11](RO) VD unit Undefined Opcode */
        uint32_t vmuop                 : 1;  /**< [ 12: 12](RO) VM unit Undefined Opcode */
        uint32_t mav                   : 1;  /**< [ 13: 13](RO) Memory Alignment Violation */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_uop_uop_sts_s cn; */
};
typedef union bdk_cbpx_uop_uop_sts bdk_cbpx_uop_uop_sts_t;

static inline uint64_t BDK_CBPX_UOP_UOP_STS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_UOP_UOP_STS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822058ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_UOP_UOP_STS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_UOP_UOP_STS(a) bdk_cbpx_uop_uop_sts_t
#define bustype_BDK_CBPX_UOP_UOP_STS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_UOP_UOP_STS(a) "CBPX_UOP_UOP_STS"
#define busnum_BDK_CBPX_UOP_UOP_STS(a) (a)
#define arguments_BDK_CBPX_UOP_UOP_STS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_uop_xci_cor
 *
 * CBP Uop Xci Cor Register
 * Note:
 *         The CODE_ECC_INT signal may not be detected if an error occurs before
 * configuring the INT_COUNT field. The user is encouraged to read the value of the ECC
 * Code Address Register, ECADD (CPM Address 0x0050) after configuring the INT_COUNT to
 * check if ECC error was detected.
 *         The CODE_TAG_ECC_INT signal may not be detected if an error occurs before
 * configuring the INT_COUNT field. The user is encouraged to read the value of the ECC
 * Code TAG Address Register, ECTADD (CPM Address 0x0054) after configuring the
 * INT_COUNT to check if ECC error was detected.
 *         To detect assertion of the UOP_INT signal before INT_COUNT is configured,
 * the rising edge of the UOP_INT signal should be detected even when the signal length
 * is 1 cycle.
 */
union bdk_cbpx_uop_xci_cor
{
    uint32_t u;
    struct bdk_cbpx_uop_xci_cor_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t int_count             : 4;  /**< [  3:  0](R/W) Number of cycles to hold the interrupts and acknowledge indication set.
                                                                 The number of clocks is INT_COUNT + 1 */
#else /* Word 0 - Little Endian */
        uint32_t int_count             : 4;  /**< [  3:  0](R/W) Number of cycles to hold the interrupts and acknowledge indication set.
                                                                 The number of clocks is INT_COUNT + 1 */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_uop_xci_cor_s cn; */
};
typedef union bdk_cbpx_uop_xci_cor bdk_cbpx_uop_xci_cor_t;

static inline uint64_t BDK_CBPX_UOP_XCI_COR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_UOP_XCI_COR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822060ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_UOP_XCI_COR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_UOP_XCI_COR(a) bdk_cbpx_uop_xci_cor_t
#define bustype_BDK_CBPX_UOP_XCI_COR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_UOP_XCI_COR(a) "CBPX_UOP_XCI_COR"
#define busnum_BDK_CBPX_UOP_XCI_COR(a) (a)
#define arguments_BDK_CBPX_UOP_XCI_COR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cid_cnt
 *
 * CBP Wrapper Cid Cnt Register
 */
union bdk_cbpx_wrapper_cid_cnt
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cid_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t rev                   : 28; /**< [ 31:  4](RO) Read only. Revision code. */
        uint32_t cid_cnt               : 4;  /**< [  3:  0](R/W) Sets the frequency at which the ContextID is sent to the ETM. If cid_en is
                                                                 asserted then ContextID data can be sent every (cid_cnt[3:0]+1) cycles. If
                                                                 CID_CNT=0, then predicate data can be sent every cycle as ContextID data (and
                                                                 therefore predicate data is never sent as Normal Data). */
#else /* Word 0 - Little Endian */
        uint32_t cid_cnt               : 4;  /**< [  3:  0](R/W) Sets the frequency at which the ContextID is sent to the ETM. If cid_en is
                                                                 asserted then ContextID data can be sent every (cid_cnt[3:0]+1) cycles. If
                                                                 CID_CNT=0, then predicate data can be sent every cycle as ContextID data (and
                                                                 therefore predicate data is never sent as Normal Data). */
        uint32_t rev                   : 28; /**< [ 31:  4](RO) Read only. Revision code. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cid_cnt_s cn; */
};
typedef union bdk_cbpx_wrapper_cid_cnt bdk_cbpx_wrapper_cid_cnt_t;

static inline uint64_t BDK_CBPX_WRAPPER_CID_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CID_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221acll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CID_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CID_CNT(a) bdk_cbpx_wrapper_cid_cnt_t
#define bustype_BDK_CBPX_WRAPPER_CID_CNT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CID_CNT(a) "CBPX_WRAPPER_CID_CNT"
#define busnum_BDK_CBPX_WRAPPER_CID_CNT(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CID_CNT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp0_end
 *
 * CBP Wrapper Cmp0 End Register
 */
union bdk_cbpx_wrapper_cmp0_end
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp0_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp0_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #0 end address */
#else /* Word 0 - Little Endian */
        uint32_t comp0_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #0 end address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp0_end_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp0_end bdk_cbpx_wrapper_cmp0_end_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP0_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP0_END(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822194ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP0_END", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP0_END(a) bdk_cbpx_wrapper_cmp0_end_t
#define bustype_BDK_CBPX_WRAPPER_CMP0_END(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP0_END(a) "CBPX_WRAPPER_CMP0_END"
#define busnum_BDK_CBPX_WRAPPER_CMP0_END(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP0_END(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp0_start
 *
 * CBP Wrapper Cmp0 Start Register
 */
union bdk_cbpx_wrapper_cmp0_start
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp0_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp0_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #0 start address */
#else /* Word 0 - Little Endian */
        uint32_t comp0_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #0 start address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp0_start_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp0_start bdk_cbpx_wrapper_cmp0_start_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP0_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP0_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822190ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP0_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP0_START(a) bdk_cbpx_wrapper_cmp0_start_t
#define bustype_BDK_CBPX_WRAPPER_CMP0_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP0_START(a) "CBPX_WRAPPER_CMP0_START"
#define busnum_BDK_CBPX_WRAPPER_CMP0_START(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP0_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp1_end
 *
 * CBP Wrapper Cmp1 End Register
 */
union bdk_cbpx_wrapper_cmp1_end
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp1_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp1_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #1 end address */
#else /* Word 0 - Little Endian */
        uint32_t comp1_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #1 end address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp1_end_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp1_end bdk_cbpx_wrapper_cmp1_end_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP1_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP1_END(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482219cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP1_END", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP1_END(a) bdk_cbpx_wrapper_cmp1_end_t
#define bustype_BDK_CBPX_WRAPPER_CMP1_END(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP1_END(a) "CBPX_WRAPPER_CMP1_END"
#define busnum_BDK_CBPX_WRAPPER_CMP1_END(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP1_END(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp1_start
 *
 * CBP Wrapper Cmp1 Start Register
 */
union bdk_cbpx_wrapper_cmp1_start
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp1_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp1_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #1 start address */
#else /* Word 0 - Little Endian */
        uint32_t comp1_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #1 start address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp1_start_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp1_start bdk_cbpx_wrapper_cmp1_start_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP1_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP1_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822198ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP1_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP1_START(a) bdk_cbpx_wrapper_cmp1_start_t
#define bustype_BDK_CBPX_WRAPPER_CMP1_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP1_START(a) "CBPX_WRAPPER_CMP1_START"
#define busnum_BDK_CBPX_WRAPPER_CMP1_START(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP1_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp2_end
 *
 * CBP Wrapper Cmp2 End Register
 */
union bdk_cbpx_wrapper_cmp2_end
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp2_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp2_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #2 end address */
#else /* Word 0 - Little Endian */
        uint32_t comp2_end             : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #2 end address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp2_end_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp2_end bdk_cbpx_wrapper_cmp2_end_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP2_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP2_END(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221a4ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP2_END", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP2_END(a) bdk_cbpx_wrapper_cmp2_end_t
#define bustype_BDK_CBPX_WRAPPER_CMP2_END(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP2_END(a) "CBPX_WRAPPER_CMP2_END"
#define busnum_BDK_CBPX_WRAPPER_CMP2_END(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP2_END(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp2_start
 *
 * CBP Wrapper Cmp2 Start Register
 */
union bdk_cbpx_wrapper_cmp2_start
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp2_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp2_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #2 start address */
#else /* Word 0 - Little Endian */
        uint32_t comp2_start           : 32; /**< [ 31:  0](WO) 32-bit Data Address Range Comparator #2 start address */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp2_start_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp2_start bdk_cbpx_wrapper_cmp2_start_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP2_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP2_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221a0ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP2_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP2_START(a) bdk_cbpx_wrapper_cmp2_start_t
#define bustype_BDK_CBPX_WRAPPER_CMP2_START(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP2_START(a) "CBPX_WRAPPER_CMP2_START"
#define busnum_BDK_CBPX_WRAPPER_CMP2_START(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP2_START(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_cmp_cfg
 *
 * CBP Wrapper Cmp Cfg Register
 */
union bdk_cbpx_wrapper_cmp_cfg
{
    uint32_t u;
    struct bdk_cbpx_wrapper_cmp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t br_all                : 1;  /**< [  7:  7](WO) Test mode: when asserted remap all loop foldback indications as indirect branches. */
        uint32_t br_fld                : 1;  /**< [  6:  6](WO) Specify mapping of bkrep foldback branch indication to ETM. Treat the last
                                                                 instruction of the last iteration of a loop as a change of flow. NB: this bit
                                                                 should be set prior to starting a trace run. */
        uint32_t cmp2_cfg              : 2;  /**< [  5:  4](WO) "Address selection for range comparator #2
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
        uint32_t cmp1_cfg              : 2;  /**< [  3:  2](WO) "Address selection for range comparator #1
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
        uint32_t cmp0_cfg              : 2;  /**< [  1:  0](WO) "Address selection for range comparator #0
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
#else /* Word 0 - Little Endian */
        uint32_t cmp0_cfg              : 2;  /**< [  1:  0](WO) "Address selection for range comparator #0
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
        uint32_t cmp1_cfg              : 2;  /**< [  3:  2](WO) "Address selection for range comparator #1
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
        uint32_t cmp2_cfg              : 2;  /**< [  5:  4](WO) "Address selection for range comparator #2
                                                                 00=Program Address
                                                                 01=LS0 Address
                                                                 10=LS1 Address
                                                                 11=Reserved" */
        uint32_t br_fld                : 1;  /**< [  6:  6](WO) Specify mapping of bkrep foldback branch indication to ETM. Treat the last
                                                                 instruction of the last iteration of a loop as a change of flow. NB: this bit
                                                                 should be set prior to starting a trace run. */
        uint32_t br_all                : 1;  /**< [  7:  7](WO) Test mode: when asserted remap all loop foldback indications as indirect branches. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_cmp_cfg_s cn; */
};
typedef union bdk_cbpx_wrapper_cmp_cfg bdk_cbpx_wrapper_cmp_cfg_t;

static inline uint64_t BDK_CBPX_WRAPPER_CMP_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_CMP_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822184ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_CMP_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_CMP_CFG(a) bdk_cbpx_wrapper_cmp_cfg_t
#define bustype_BDK_CBPX_WRAPPER_CMP_CFG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_CMP_CFG(a) "CBPX_WRAPPER_CMP_CFG"
#define busnum_BDK_CBPX_WRAPPER_CMP_CFG(a) (a)
#define arguments_BDK_CBPX_WRAPPER_CMP_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_ls0_cfg
 *
 * CBP Wrapper Ls0 Cfg Register
 */
union bdk_cbpx_wrapper_ls0_cfg
{
    uint32_t u;
    struct bdk_cbpx_wrapper_ls0_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t ls0_tr_cfg            : 3;  /**< [  7:  5](WO) Select which ext_trigger signals to apply to LS0 address filtering
                                                                 000=No filtering on external triggers
                                                                 ls0_tr_cfg[5]=1 Filter on ext_trigger[0]
                                                                 ls0_tr_cfg[6]=1 Filter on ext_trigger[1]
                                                                 ls0_tr_cfg[7]=1 Filter on ext_trigger[2]
                                                                 Selected external triggers are logically ORed with the selected range comparators */
        uint32_t ls0_lg                : 2;  /**< [  4:  3](WO) "Select logical operators to combine comparator in-range indications
                                                                 00= comparators (#0 AND #1) AND #2 in-range indications
                                                                 01= comparators (#0 AND #1) OR #2 in-range indications
                                                                 10=comparators (#0 OR #1) AND #2 in-range indications
                                                                 11=comparators (#0 OR #1) OR #2 in-range indications" */
        uint32_t ls0_cmp_cfg           : 3;  /**< [  2:  0](WO) "Select which comparator in-range indications to apply to LS0 address filtering
                                                                 ls0_cmp_cfg[0]=1 Filter LS0 accesses on comparator #0 in-range indication cr0
                                                                 ls0_cmp_cfg[1]=1 Filter LS0 accesses on comparator #1 in-range indication cr1
                                                                 ls0_cmp_cfg[2]=1 Filter LS0 accesses on comparator #2 in-range indication cr2
                                                                 Where more than 1 comparator is selected the in-range indications are combined
                                                                 according to the logical operation specified by ls0_lg" */
#else /* Word 0 - Little Endian */
        uint32_t ls0_cmp_cfg           : 3;  /**< [  2:  0](WO) "Select which comparator in-range indications to apply to LS0 address filtering
                                                                 ls0_cmp_cfg[0]=1 Filter LS0 accesses on comparator #0 in-range indication cr0
                                                                 ls0_cmp_cfg[1]=1 Filter LS0 accesses on comparator #1 in-range indication cr1
                                                                 ls0_cmp_cfg[2]=1 Filter LS0 accesses on comparator #2 in-range indication cr2
                                                                 Where more than 1 comparator is selected the in-range indications are combined
                                                                 according to the logical operation specified by ls0_lg" */
        uint32_t ls0_lg                : 2;  /**< [  4:  3](WO) "Select logical operators to combine comparator in-range indications
                                                                 00= comparators (#0 AND #1) AND #2 in-range indications
                                                                 01= comparators (#0 AND #1) OR #2 in-range indications
                                                                 10=comparators (#0 OR #1) AND #2 in-range indications
                                                                 11=comparators (#0 OR #1) OR #2 in-range indications" */
        uint32_t ls0_tr_cfg            : 3;  /**< [  7:  5](WO) Select which ext_trigger signals to apply to LS0 address filtering
                                                                 000=No filtering on external triggers
                                                                 ls0_tr_cfg[5]=1 Filter on ext_trigger[0]
                                                                 ls0_tr_cfg[6]=1 Filter on ext_trigger[1]
                                                                 ls0_tr_cfg[7]=1 Filter on ext_trigger[2]
                                                                 Selected external triggers are logically ORed with the selected range comparators */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_ls0_cfg_s cn; */
};
typedef union bdk_cbpx_wrapper_ls0_cfg bdk_cbpx_wrapper_ls0_cfg_t;

static inline uint64_t BDK_CBPX_WRAPPER_LS0_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_LS0_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822188ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_LS0_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_LS0_CFG(a) bdk_cbpx_wrapper_ls0_cfg_t
#define bustype_BDK_CBPX_WRAPPER_LS0_CFG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_LS0_CFG(a) "CBPX_WRAPPER_LS0_CFG"
#define busnum_BDK_CBPX_WRAPPER_LS0_CFG(a) (a)
#define arguments_BDK_CBPX_WRAPPER_LS0_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_ls1_cfg
 *
 * CBP Wrapper Ls1 Cfg Register
 */
union bdk_cbpx_wrapper_ls1_cfg
{
    uint32_t u;
    struct bdk_cbpx_wrapper_ls1_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t ls1_tr_cfg            : 3;  /**< [  7:  5](WO) Select which ext_trigger signals to apply to LS1 address filtering
                                                                 000=No filtering on external triggers
                                                                 ls1_tr_cfg[5]=1 Filter on ext_trigger[0]
                                                                 ls1_tr_cfg[6]=1 Filter on ext_trigger[1]
                                                                 ls1_tr_cfg[7]=1 Filter on ext_trigger[2]
                                                                 Selected external triggers are logically ORed with the selected range comparators */
        uint32_t ls1_lg                : 2;  /**< [  4:  3](WO) "Select logical operators to combine comparator in-range indications
                                                                 00= comparators (#0 AND #1) AND #2 in-range indications
                                                                 01= comparators (#0 AND #1) OR #2 in-range indications
                                                                 10=comparators (#0 OR #1) AND #2 in-range indications
                                                                 11=comparators (#0 OR #1) OR #2 in-range indications" */
        uint32_t ls1_cmp_cfg           : 3;  /**< [  2:  0](WO) "Select which comparator in-range indications to apply to LS1 address filtering
                                                                 ls1_cmp_cfg[0]=1 Filter LS1 accesses on comparator #0 in-range indication cr0
                                                                 ls1_cmp_cfg[1]=1 Filter LS1 accesses on comparator #1 in-range indication cr1
                                                                 ls1_cmp_cfg[2]=1 Filter LS1 accesses on comparator #2 in-range indication cr2
                                                                 Where more than 1 comparator is selected the in-range indications are combined
                                                                 according to the logical operation specified by ls1_lg" */
#else /* Word 0 - Little Endian */
        uint32_t ls1_cmp_cfg           : 3;  /**< [  2:  0](WO) "Select which comparator in-range indications to apply to LS1 address filtering
                                                                 ls1_cmp_cfg[0]=1 Filter LS1 accesses on comparator #0 in-range indication cr0
                                                                 ls1_cmp_cfg[1]=1 Filter LS1 accesses on comparator #1 in-range indication cr1
                                                                 ls1_cmp_cfg[2]=1 Filter LS1 accesses on comparator #2 in-range indication cr2
                                                                 Where more than 1 comparator is selected the in-range indications are combined
                                                                 according to the logical operation specified by ls1_lg" */
        uint32_t ls1_lg                : 2;  /**< [  4:  3](WO) "Select logical operators to combine comparator in-range indications
                                                                 00= comparators (#0 AND #1) AND #2 in-range indications
                                                                 01= comparators (#0 AND #1) OR #2 in-range indications
                                                                 10=comparators (#0 OR #1) AND #2 in-range indications
                                                                 11=comparators (#0 OR #1) OR #2 in-range indications" */
        uint32_t ls1_tr_cfg            : 3;  /**< [  7:  5](WO) Select which ext_trigger signals to apply to LS1 address filtering
                                                                 000=No filtering on external triggers
                                                                 ls1_tr_cfg[5]=1 Filter on ext_trigger[0]
                                                                 ls1_tr_cfg[6]=1 Filter on ext_trigger[1]
                                                                 ls1_tr_cfg[7]=1 Filter on ext_trigger[2]
                                                                 Selected external triggers are logically ORed with the selected range comparators */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_ls1_cfg_s cn; */
};
typedef union bdk_cbpx_wrapper_ls1_cfg bdk_cbpx_wrapper_ls1_cfg_t;

static inline uint64_t BDK_CBPX_WRAPPER_LS1_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_LS1_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04482218cll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_LS1_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_LS1_CFG(a) bdk_cbpx_wrapper_ls1_cfg_t
#define bustype_BDK_CBPX_WRAPPER_LS1_CFG(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_LS1_CFG(a) "CBPX_WRAPPER_LS1_CFG"
#define busnum_BDK_CBPX_WRAPPER_LS1_CFG(a) (a)
#define arguments_BDK_CBPX_WRAPPER_LS1_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_mode
 *
 * CBP Wrapper Mode Register
 */
union bdk_cbpx_wrapper_mode
{
    uint32_t u;
    struct bdk_cbpx_wrapper_mode_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_11_31        : 21;
        uint32_t br_all                : 1;  /**< [ 10: 10](WO) Active high. Output all branches as indirect branches (excluding bkrep fold indications). */
        uint32_t b2i_lc0               : 1;  /**< [  9:  9](WO) Active high. Trace optimization for bkrep2i loop count=0 */
        uint32_t b2i_fld               : 1;  /**< [  8:  8](WO) Active high. Trace optimization for bkrep2i loop count=1 */
        uint32_t wr_reset              : 1;  /**< [  7:  7](WO) Active high. Single shot. When asserted, the Pipeline Align, Control and
                                                                 Sequencer and ETM Interface are reset. */
        uint32_t wr_en                 : 1;  /**< [  6:  6](WO) Active high. When asserted, the wrapper functionality is enabled. */
        uint32_t etmx2                 : 1;  /**< [  5:  5](WO) Should be constant zero */
        uint32_t cid_en                : 1;  /**< [  4:  4](WO) Active high. Predicate flags can be output as ContextID data. If negated,
                                                                 predicate data is transferred to the ETM as normal data only. */
        uint32_t no_stall              : 1;  /**< [  3:  3](WO) Active high. When asserted, the wrapper does not stall the core and a priority
                                                                 mechanism is implemented to determine which CEVA-XC information is traced in
                                                                 cases where not all selected data can be transferred to the ETM. Priority is:
                                                                 Predicate, LS0, LS1 */
        uint32_t pr_trace              : 1;  /**< [  2:  2](WO) Active high. Trace predicate data */
        uint32_t ls0_trace             : 1;  /**< [  1:  1](WO) Active high. Trace data from LS0 */
        uint32_t ls1_trace             : 1;  /**< [  0:  0](WO) Active high. Trace data from LS1 */
#else /* Word 0 - Little Endian */
        uint32_t ls1_trace             : 1;  /**< [  0:  0](WO) Active high. Trace data from LS1 */
        uint32_t ls0_trace             : 1;  /**< [  1:  1](WO) Active high. Trace data from LS0 */
        uint32_t pr_trace              : 1;  /**< [  2:  2](WO) Active high. Trace predicate data */
        uint32_t no_stall              : 1;  /**< [  3:  3](WO) Active high. When asserted, the wrapper does not stall the core and a priority
                                                                 mechanism is implemented to determine which CEVA-XC information is traced in
                                                                 cases where not all selected data can be transferred to the ETM. Priority is:
                                                                 Predicate, LS0, LS1 */
        uint32_t cid_en                : 1;  /**< [  4:  4](WO) Active high. Predicate flags can be output as ContextID data. If negated,
                                                                 predicate data is transferred to the ETM as normal data only. */
        uint32_t etmx2                 : 1;  /**< [  5:  5](WO) Should be constant zero */
        uint32_t wr_en                 : 1;  /**< [  6:  6](WO) Active high. When asserted, the wrapper functionality is enabled. */
        uint32_t wr_reset              : 1;  /**< [  7:  7](WO) Active high. Single shot. When asserted, the Pipeline Align, Control and
                                                                 Sequencer and ETM Interface are reset. */
        uint32_t b2i_fld               : 1;  /**< [  8:  8](WO) Active high. Trace optimization for bkrep2i loop count=1 */
        uint32_t b2i_lc0               : 1;  /**< [  9:  9](WO) Active high. Trace optimization for bkrep2i loop count=0 */
        uint32_t br_all                : 1;  /**< [ 10: 10](WO) Active high. Output all branches as indirect branches (excluding bkrep fold indications). */
        uint32_t reserved_11_31        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_mode_s cn; */
};
typedef union bdk_cbpx_wrapper_mode bdk_cbpx_wrapper_mode_t;

static inline uint64_t BDK_CBPX_WRAPPER_MODE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_MODE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e044822180ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_MODE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_MODE(a) bdk_cbpx_wrapper_mode_t
#define bustype_BDK_CBPX_WRAPPER_MODE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_MODE(a) "CBPX_WRAPPER_MODE"
#define busnum_BDK_CBPX_WRAPPER_MODE(a) (a)
#define arguments_BDK_CBPX_WRAPPER_MODE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cbp#_wrapper_pred_addr
 *
 * CBP Wrapper Pred Addr Register
 */
union bdk_cbpx_wrapper_pred_addr
{
    uint32_t u;
    struct bdk_cbpx_wrapper_pred_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pred_addr             : 32; /**< [ 31:  0](WO) 32-bit Data Address with which predicate flags are output to the ETM */
#else /* Word 0 - Little Endian */
        uint32_t pred_addr             : 32; /**< [ 31:  0](WO) 32-bit Data Address with which predicate flags are output to the ETM */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cbpx_wrapper_pred_addr_s cn; */
};
typedef union bdk_cbpx_wrapper_pred_addr bdk_cbpx_wrapper_pred_addr_t;

static inline uint64_t BDK_CBPX_WRAPPER_PRED_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CBPX_WRAPPER_PRED_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0448221a8ll + 0x40000ll * ((a) & 0xf);
    __bdk_csr_fatal("CBPX_WRAPPER_PRED_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CBPX_WRAPPER_PRED_ADDR(a) bdk_cbpx_wrapper_pred_addr_t
#define bustype_BDK_CBPX_WRAPPER_PRED_ADDR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CBPX_WRAPPER_PRED_ADDR(a) "CBPX_WRAPPER_PRED_ADDR"
#define busnum_BDK_CBPX_WRAPPER_PRED_ADDR(a) (a)
#define arguments_BDK_CBPX_WRAPPER_PRED_ADDR(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_CBP_H__ */
