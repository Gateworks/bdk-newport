/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-pcieep.h"
#include "libbdk-arch/bdk-csrs-rom.h"
#include "libbdk-arch/bdk-csrs-scr.h"
#include "libbdk-hal/qlm/bdk-qlm-common.h"
#include "libbdk-hal/qlm/bdk-qlm-common-gsern.h"
#include "libcavm-gsern/cavm-gsern-api.h"
#include "libcavm-gsern/cavm-gsern-settings.h"
#include "libcavm-gsern/cavm-gsern-init.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(SCR_SCRIPT);

static const int NONTRUSTED_CLIB_ADDRESS = 0x10400;
static const int TRUSTED_CLIB_ADDRESS = 0x10600;
static const int SCR_ADDRESS = 0x5000;
#define SCR_MAX_SIZE (16384 / (int)sizeof(union bdk_scr_generic_s))
static union bdk_scr_generic_s scr_script[SCR_MAX_SIZE];
static int scr_size = 0;

typedef struct {
        uint64_t muxpost;
        uint64_t cpostb;
        uint64_t cposta;
        uint64_t enpost;
        uint64_t muxmain;
        uint64_t cmaind ;
        uint64_t enmain;
        uint64_t muxpre;
        uint64_t cpreb;
        uint64_t cprea;
        uint64_t enpre;
} tx_tap_drv_override_t;

/* Compose a table of PCIE preset values, two GEN        */
static tx_tap_drv_override_t tx_tap_drv_override_gen123[11] = {
    {0x0, 0x5, 0x5, 0x3, 0xF, 0x5, 0xF, 0x2, 0x5, 0x0, 0x2 }, /* Preset 0 ALSO GEN2 6DB */
    {0x0, 0x0, 0x7, 0x1, 0xF, 0x7, 0xF, 0x2, 0x7, 0x0, 0x2 }, /* Preset 1 ALSO GEN1 and GEN2 3.5 DB */
    {0x0, 0x4, 0x4, 0x3, 0xF, 0x6, 0xF, 0x2, 0x6, 0x0, 0x2 }, /* Preset 2 */
    {0x2, 0x5, 0x5, 0x3, 0xF, 0x5, 0xF, 0x2, 0x5, 0x0, 0x2 }, /* Preset 3 */
    {0x2, 0x7, 0x0, 0x2, 0xF, 0x7, 0xF, 0x2, 0x7, 0x0, 0x2 }, /* Preset 4 */
    {0x2, 0x5, 0x0, 0x2, 0xF, 0x6, 0xF, 0x2, 0x5, 0x4, 0x3 }, /* Preset 5 */
    {0x2, 0x5, 0x0, 0x2, 0xF, 0x5, 0xF, 0x2, 0x5, 0x5, 0x3 }, /* Preset 6 */
    {0x2, 0x4, 0x3, 0x3, 0xF, 0x4, 0xF, 0x0, 0x4, 0x4, 0x3 }, /* Preset 7 */
    {0x0, 0x0, 0x5, 0x1, 0xF, 0x5, 0xF, 0x2, 0x5, 0x5, 0x3 }, /* Preset 8 */
    {0x0, 0x0, 0x0, 0x0, 0xF, 0x7, 0xF, 0x2, 0x7, 0x7, 0x3 }, /* Preset 9 */
    {0x0, 0x7, 0x7, 0x3, 0xF, 0x7, 0xF, 0x0, 0x0, 0x0, 0x0 }, /* Preset 10 */
};


/**
 * Initialize a new memory script for creation
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_init(void)
{
    scr_size = 0;
    memset(scr_script, 0xff, sizeof(scr_script));
    return 0;
}

/**
 * Calculate the checksum of the current script
 *
 * @return Checksum
 */
uint32_t bdk_scr_chksum(void)
{
    uint32_t rom_script_size = scr_size * sizeof(scr_script[0]);
    uint32_t rom_script_chksum = 0;

    /* Calc the checksum */
    const uint32_t *ptr;
    for (ptr = (const uint32_t *)scr_script;
         ptr < ((const uint32_t *)scr_script + rom_script_size/sizeof(uint32_t));
         ptr++)
    {
        rom_script_chksum += *ptr;
        rom_script_chksum += (rom_script_chksum < (*ptr)) ? 1 : 0; /* Wrap overflow. */
    }
    return rom_script_chksum;
}

/**
 * Read the script from the boot flash
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_read(void)
{
    FILE *inf = fopen("/boot", "r");
    if (!inf)
    {
        bdk_error("Failed to open boot device\n");
        return -1;
    }
    if (fseek(inf, SCR_ADDRESS, SEEK_SET))
    {
        fclose(inf);
        bdk_error("Failed to seek to the boot device location\n");
        return -1;
    }
    if (fread(scr_script, sizeof(scr_script), 1, inf) != 1)
    {
        fclose(inf);
        bdk_error("Failed to read the script from the boot device\n");
        return -1;
    }

    /* Start assuming the script is max size, then trim off entries
       that are all 0xff */
    scr_size = SCR_MAX_SIZE;
    while (scr_size &&
           (scr_script[scr_size - 1].u[0] == (uint64_t)-1) &&
           (scr_script[scr_size - 1].u[1] == (uint64_t)-1))
        scr_size--;

    fclose(inf);
    return 0;
}

/**
 * Write the current script to the boot flash
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_write(void)
{
    uint32_t rom_script_size = scr_size * sizeof(scr_script[0]);
    uint32_t rom_script_offset = SCR_ADDRESS;
    uint32_t rom_script_chksum = bdk_scr_chksum();

    /* Open the boot device at the script's location */
    FILE *outf = fopen("/boot", "w");
    if (!outf)
    {
        bdk_error("Failed to open boot device\n");
        return -1;
    }
    if (fseek(outf, SCR_ADDRESS, SEEK_SET))
    {
        fclose(outf);
        bdk_error("Failed to seek to the boot device location\n");
        return -1;
    }

    /* Fill the unused script area with 0xff to be flash friendly */
    memset(&scr_script[scr_size], 0xff, sizeof(scr_script) - scr_size * sizeof(scr_script[0]));

    if (fwrite(scr_script, sizeof(scr_script), 1, outf) != 1)
    {
        fclose(outf);
        bdk_error("Failed to write the script to the boot device\n");
        return -1;
    }

    printf("Rom Script: offset %d (0x%x), size %d (0x%x), chksum %d (0x%x)\n",
        rom_script_offset, rom_script_offset,
        rom_script_size, rom_script_size,
        rom_script_chksum, rom_script_chksum);

    /* Update the script info in both CLIBs */
    int address = NONTRUSTED_CLIB_ADDRESS;
    for (int i = 0; i < 2; i++)
    {

        address += 256 / 8; /* rom_script_size starts at bit 256 */
        if (fseek(outf, address, SEEK_SET))
        {
            fclose(outf);
            bdk_error("Failed to seek to the boot device location\n");
            return -1;
        }
        uint32_t tmp = bdk_cpu_to_le32(rom_script_size);
        if (fwrite(&tmp, sizeof(tmp), 1, outf) != 1)
        {
            fclose(outf);
            bdk_error("Failed to write script size to the boot device\n");
            return -1;
        }
        tmp = bdk_cpu_to_le32(rom_script_offset);
        if (fwrite(&tmp, sizeof(tmp), 1, outf) != 1)
        {
            fclose(outf);
            bdk_error("Failed to write script offset to the boot device\n");
            return -1;
        }
        tmp = bdk_cpu_to_le32(rom_script_chksum);
        if (fwrite(&tmp, sizeof(tmp), 1, outf) != 1)
        {
            fclose(outf);
            bdk_error("Failed to write script checksum to the boot device\n");
            return -1;
        }
        address = TRUSTED_CLIB_ADDRESS;
    }

    fclose(outf);
    return 0;
}

/**
 * Display the current script
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_display(void)
{
    const char *CMP_TYPE[8] = {"EQ", "LE", "LT", "NE", "GE", "GT", "?", "?"};
    for (int i = 0; i < scr_size; i++)
    {
        switch (scr_script[i].s.op)
        {
            case 0xc1: /* Compare and exit */
            {
                union bdk_scr_cmp_and_exit_s *scr = (union bdk_scr_cmp_and_exit_s *)&scr_script[i];
                printf("%2d) Compare and exit CMP_TYPE=%s RSL64=%d MASK=0x%lx\n",
                    i, CMP_TYPE[scr->s.cmp_type], scr->s.rsl64, scr->s.mask);
                break;
            }
            case 0xc2: /* Compare and jump */
            {
                union bdk_scr_cmp_and_jump_s *scr = (union bdk_scr_cmp_and_jump_s *)&scr_script[i];
                printf("%2d) Compare and jump CMP_TYPE=%s RSL64=%d MASK=0x%lx JUMP_TRUE=%d JUMP_FALSE=%d\n",
                    i, CMP_TYPE[scr->s.cmp_type], scr->s.rsl64, scr->s.mask, scr->s.jump_true, scr->s.jump_false);
                break;
            }
            case 0xc3: /* Compare and spin */
            {
                union bdk_scr_cmp_and_spin_s *scr = (union bdk_scr_cmp_and_spin_s *)&scr_script[i];
                printf("%2d) Compare and spin CMP_TYPE=%s RSL64=%d MASK=0x%lx TIMEOUT=%dns\n",
                    i, CMP_TYPE[scr->s.cmp_type], scr->s.rsl64, scr->s.mask, scr->s.time_out * 10);
                break;
            }
            case 0x00: /* Exit */
            {
                printf("%2d) Exit\n", i);
                break;
            }
            case 0xc4: /* NoOp */
            {
                printf("%2d) NoOp\n", i);
                break;
            }
            case 0xc5: /* Setup */
            {
                union bdk_scr_setup_cmp_s *scr = (union bdk_scr_setup_cmp_s *)&scr_script[i];
                printf("%2d) Setup compare ADDR=0x%lx CMP_DATA=0x%lx\n", i, (uint64_t)scr->s.addr, scr->s.cmp_data);
                break;
            }
            case 0xc6: /* Wait */
            {
                union bdk_scr_wait_s *scr = (union bdk_scr_wait_s *)&scr_script[i];
                printf("%2d) Wait %dns\n", i, scr->s.count * 10);
                break;
            }
            case 0xc7: /* Write32 */
            {
                union bdk_scr_write32_s *scr = (union bdk_scr_write32_s *)&scr_script[i];
                printf("%2d) Write32 ADDR=0x%lx DATA=0x%lx\n", i, (uint64_t)scr->s.addr, (uint64_t)scr->s.data);
                break;
            }
            case 0xc8: /* Write64 */
            {
                union bdk_scr_write64_s *scr = (union bdk_scr_write64_s *)&scr_script[i];
                printf("%2d) Write64 ADDR=0x%lx DATA=0x%lx\n", i, (uint64_t)scr->s.addr, scr->s.data);
                break;
            }
            default:
                printf("%2d) INVALID\n", i);
                break;
        }
    }
    return 0;
}

/**
 * Add a new CSR write to the current script
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param value   Value to write
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_add_write(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t value)
{
    if (scr_size >= SCR_MAX_SIZE)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    if (size == 8)
    {
        volatile union bdk_scr_write64_s *scr = (union bdk_scr_write64_s *)&scr_script[scr_size++];
        scr->u[0] = 0;
        scr->u[1] = 0;
        scr->s.addr = address;
        scr->s.data = value;
        scr->s.op = 0xc8;
    }
    else if (size == 4)
    {
        volatile union bdk_scr_write32_s *scr = (union bdk_scr_write32_s *)&scr_script[scr_size++];
        scr->u[0] = 0;
        scr->u[1] = 0;
        scr->s.addr = address;
        scr->s.data = value;
        scr->s.op = 0xc7;
    }
    else
        bdk_fatal("SCRIPT: Unexpected size\n");
    return 0;
}

/**
 * Add a script step to poll a CSR for status
 *
 * @param type       Type of CSR being written
 * @param busnum     Bus number from CSR
 * @param size       Size of the CSR
 * @param address    Address of the CSR
 * @param mask       Mask for which bits to look at
 * @param value      Value to compare with
 * @param scr_cmp_type_e
 *                   Compare type
 * @param timeout_ns Timeout in nanoseconds
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_add_poll(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e, int timeout_ns)
{
    if (scr_size >= SCR_MAX_SIZE - 1)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    volatile union bdk_scr_setup_cmp_s *setup = (union bdk_scr_setup_cmp_s *)&scr_script[scr_size++];
    setup->u[0] = 0;
    setup->u[1] = 0;
    setup->s.addr = address;
    setup->s.cmp_data = value;
    setup->s.op = 0xc5;

    volatile union bdk_scr_cmp_and_spin_s *spin = (union bdk_scr_cmp_and_spin_s *)&scr_script[scr_size++];
    spin->u[0] = 0;
    spin->u[1] = 0;
    spin->s.cmp_type = scr_cmp_type_e;
    spin->s.mask = mask;
    spin->s.rsl64 = (size == 8);
    spin->s.time_out = (timeout_ns + 9) / 10;
    spin->s.op = 0xc3;

    return 0;
}

/**
 * Add a wait
 *
 * @param timeout_ns Timeout in nanoseconds
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_add_wait(int timeout_ns)
{
    if (scr_size >= SCR_MAX_SIZE)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    volatile union bdk_scr_wait_s *wait = (union bdk_scr_wait_s *)&scr_script[scr_size++];
    wait->u[0] = 0;
    wait->u[1] = 0;
    wait->s.count = (timeout_ns + 9) / 10;
    wait->s.op = 0xc6;
    return 0;
}

/**
 * Add a script step to poll a CSR for status an exit
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param mask    Mask for which bits to look at
 * @param value   Value to compare with
 * @param scr_cmp_type_e
 *                Compare type
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_add_cmp_exit(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e)
{
    if (scr_size >= SCR_MAX_SIZE - 1)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    volatile union bdk_scr_setup_cmp_s *setup = (union bdk_scr_setup_cmp_s *)&scr_script[scr_size++];
    setup->u[0] = 0;
    setup->u[1] = 0;
    setup->s.addr = address;
    setup->s.cmp_data = value;
    setup->s.op = 0xc5;

    volatile union bdk_scr_cmp_and_exit_s *cmp = (union bdk_scr_cmp_and_exit_s *)&scr_script[scr_size++];
    cmp->u[0] = 0;
    cmp->u[1] = 0;
    cmp->s.cmp_type = scr_cmp_type_e;
    cmp->s.mask = mask;
    cmp->s.rsl64 = (size == 8);
    cmp->s.op = 0xc1;

    return 0;
}

/**
 * Add a script step to poll a CSR for status and jump to a location. The location
 * can be update with bdk_scr_update_jump()
 *
 * @param type    Type of CSR being written
 * @param busnum  Bus number from CSR
 * @param size    Size of the CSR
 * @param address Address of the CSR
 * @param mask    Mask for which bits to look at
 * @param value   Value to compare with
 * @param scr_cmp_type_e
 *                Compare type
 * @param jump    Jump off set as location into script. Pass 0 if it will be updated later
 *
 * @return Zero or positive on success, negative on failure. The non-negative return value
 *         is the handle to pass to bdk_scr_update_jump()
 */
int bdk_scr_add_cmp_jump(bdk_csr_type_t type, int busnum, int size, uint64_t address, uint64_t mask, uint64_t value, int scr_cmp_type_e, int jump)
{
    if (scr_size >= SCR_MAX_SIZE - 1)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    volatile union bdk_scr_setup_cmp_s *setup = (union bdk_scr_setup_cmp_s *)&scr_script[scr_size++];
    setup->u[0] = 0;
    setup->u[1] = 0;
    setup->s.addr = address;
    setup->s.cmp_data = value;
    setup->s.op = 0xc5;

    volatile union bdk_scr_cmp_and_jump_s *cmp = (union bdk_scr_cmp_and_jump_s *)&scr_script[scr_size++];
    cmp->u[0] = 0;
    cmp->u[1] = 0;
    cmp->s.cmp_type = scr_cmp_type_e;
    cmp->s.mask = mask;
    cmp->s.rsl64 = (size == 8);
    cmp->s.op = 0xc2;
    cmp->s.jump_false = scr_size;
    cmp->s.jump_true = jump;

    return scr_size - 1;
}

/**
 * Update the jump location for a existing compare and jump
 *
 * @param handle Handle returned by bdk_scr_add_cmp_jump()
 * @param jump   New jump address
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_update_jump(int handle, int jump)
{
    if ((handle < 0) || (handle >= scr_size))
    {
        bdk_error("SCRIPT: Script invalid handle\n");
        return -1;
    }
    if ((jump < 0) || (jump > scr_size))
    {
        bdk_error("SCRIPT: Script invalid jump\n");
        return -1;
    }
    union bdk_scr_cmp_and_jump_s *cmp = (union bdk_scr_cmp_and_jump_s *)&scr_script[handle];
    if (cmp->s.op != 0xc2)
    {
        bdk_error("SCRIPT: Script invalid jump\n");
        return -1;
    }
    cmp->s.jump_true = jump;
    return 0;
}

/**
 * Add a script step to exit the script
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_add_exit(void)
{
    if (scr_size >= SCR_MAX_SIZE)
    {
        bdk_error("SCRIPT: Script has reached its max size\n");
        return -1;
    }

    volatile union bdk_scr_exit_s *scr = (union bdk_scr_exit_s *)&scr_script[scr_size++];
    scr->u[0] = 0;
    scr->u[1] = 0;
    return 0;
}

#define SCR_ADD_WRITE(csr, code_block) do { \
        uint64_t _tmp_address = csr; \
        typedef_##csr c = {.u = 0}; \
        code_block; \
        bdk_scr_add_write(bustype_##csr, busnum_##csr, sizeof(typedef_##csr), _tmp_address, c.u); \
    } while (0)

#define SCR_ADD_PCIEEP_WRITE(pem, tbl, csr, code_block, options) do { \
        typedef_##csr c = {.u = 0}; \
        if (sizeof(c) != 4) \
            bdk_fatal("SCR_ADD_PCIEEP_WRITE not 4 bytes"); \
        code_block; \
        uint64_t _tmp_t_address = BDK_PEMX_CFG_TBLX(pem, tbl); \
        typedef_BDK_PEMX_CFG_TBLX(pem, tbl) t = {.u = 0}; \
        t.s.data = c.u; \
        t.s.offset = csr; \
        t.s.wmask = 0xf; /* Can be written in options */ \
        options; \
        if (t.s.shadow) { \
            if (bustype_##csr != BDK_CSR_TYPE_PCICONFIGEP_SHADOW) \
                bdk_fatal("SCR_ADD_PCIEEP_WRITE invalid CSR"); \
        } else { \
            if (bustype_##csr != BDK_CSR_TYPE_PCICONFIGEP) \
                bdk_fatal("SCR_ADD_PCIEEP_WRITE invalid CSR"); \
        } \
        bdk_scr_add_write(bustype_BDK_PEMX_CFG_TBLX(pem, tbl), \
        busnum_BDK_PEMX_CFG_TBLX(pem, tbl), \
        sizeof(typedef_BDK_PEMX_CFG_TBLX(pem, tbl)), _tmp_t_address, t.u); \
    } while (0)

/**
 * A number of the GSERN settings are encoded in a bitfield where bit 0 is Gen1
 * and bit 3 is Gen4. This function looks up the bit values for a setting and sets
 * the correct mode mask bits.
 *
 * @param setting_array
 *               Array from cavm-gsern-settings.h
 *
 * @return Mask for Gen* modes
 */
static int build_mode_mask(const int setting_array[])
{
    int mask = setting_array[GSERN_PCIE_02500000000];   /* Gen 1 */
    mask |= setting_array[GSERN_PCIE_05000000000] << 1; /* Gen 2 */
    mask |= setting_array[GSERN_PCIE_08000000000] << 2; /* Gen 3 */
    mask |= setting_array[GSERN_PCIE_16000000000] << 3; /* Gen 4 */
    return mask;
}

static int scr_setup_qlm(int pem, int qlm, int width, int speed, int txpreset)
{
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
    enum gsern_lane_modes mode =
        (speed == 2500) ? GSERN_PCIE_02500000000 :
        (speed == 5000) ? GSERN_PCIE_05000000000 :
        (speed == 8000) ? GSERN_PCIE_08000000000 :
        GSERN_PCIE_16000000000;

    const int BROADCAST = 4; /* Broadcast across all lanes */
    bool use_dual = (width == 8);
    bool use_quad = (width == 16);

    /* adpt_wait is tha max of a number of other values plus 16 */
    int adpt_wait = MAX(gsern_lane_vga_timer_max, gsern_lane_dfe_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctlez_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctle_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctlelte_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_afeos_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_blwc_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_prevga_gn_timer_max);
    adpt_wait += 16;
    if (adpt_wait > 0x3ffff)
        adpt_wait = 0x3ffff;

    /* Figure out the mask of the QLM/DLMs used for this PCIe */
    int txdivrst_algn_qlm_mask = 0;
    if (use_quad)
        txdivrst_algn_qlm_mask = 0xf;
    else if (use_dual)
    {
        if (qlm == 2 || qlm == 3)
            txdivrst_algn_qlm_mask = 0xc;
        else
            txdivrst_algn_qlm_mask = 0x3;
    }

    /* The lane masks used for synchronization. Currently the BDK
       doesn't allow widths less than the QLM/DLM */
    int txdivrst_algn_lane_mask = bdk_build_mask(4);

    int txdivclk_mux_sel_ovrride = 0; /* 1 lane */
    switch (width)
    {
        case 2:
            txdivclk_mux_sel_ovrride = 1;
            break;
        case 4:
            txdivclk_mux_sel_ovrride = 2;
            break;
        case 8:
            txdivclk_mux_sel_ovrride = 3;
            break;
        case 16:
            txdivclk_mux_sel_ovrride = 4;
            break;
    }

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, BROADCAST),
        c.s.cal_cp_mult = 1;
        c.s.cp = 0xc;
        c.s.cp_overide = 0;
        c.s.band_ppm = 2;
        c.s.band = 0x10;
        c.s.band_limits = 0;
        c.s.band_overide = 0;
        c.s.bg_div16 = 0;
        c.s.bg_clk_en = 0;
        c.s.dither_en = 1;
        c.s.cal_sel = 0;
        c.s.vco_sel = 0;
        c.s.sdm_en = 0;
        c.s.post_div = 3;
        c.s.div_n = 0x64;
        c.s.div_f = 0);
    /* Need to add more configuration options for the GSERNX_LANEX_RSTCLKMSK_BCFG  */
    /* txdivrst_algn_qlm_mask and txdivrst_algn_lane_mask when PEM is configured */
    /* for x8 with two QLMs, x4 with one QLM or two DLMs, and x2 with one DLM */
    /* the Txdivclk alignment by QLM and DLM will change */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RSTCLKMSK_BCFG(qlm, BROADCAST),
        c.s.txdivrst_algn_qlm_mask = txdivrst_algn_qlm_mask;
        c.s.txdivrst_algn_lane_mask = txdivrst_algn_lane_mask;
        c.s.txdivrst_algn_wait_en = 0;
        c.s.txdivrst_algn_wait = 0xff);
    /* Need to add more configuration options for the GSERNX_LANEX_SRCMX_BCFG  */
    /* txdivclk_mux_sel_ovrride when PEM is configured */
    /* for x8 with two QLMs, x4 with one QLM or two DLMs, and x2 with one DLM */
    /* the Txdivclk alignment by QLM and DLM will change */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, BROADCAST),
        c.s.en_hldcdrfsm_on_idle = 1;
        c.s.en_pauseadpt_on_idle = 1;
        c.s.trn_sclk_cgt_on = 0;
        c.s.trn_tx_cgt_on = 0;
        c.s.trn_rx_cgt_on = 0;
        c.s.ocx_tx_cgt_on = 0;
        c.s.ocx_rx_cgt_on = 0;
        c.s.sata_tx_cgt_on = 0;
        c.s.sata_rx_cgt_on = 0;
        c.s.pcie_tx_cgt_on = 0;
        c.s.pcie_rx_cgt_on = 0;
        c.s.pat_tx_cgt_on = 0;
        c.s.pat_rx_cgt_on = 0;
        c.s.cgx_tx_cgt_on = 0;
        c.s.cgx_rx_cgt_on = 0;
        c.s.txdivclk_mux_sel_ovrride_en = 1;
        c.s.txdivclk_mux_sel_ovrride = txdivclk_mux_sel_ovrride;
        c.s.tx_ctrl_sel = 1;
        c.s.tx_data_sel = 1);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_LT_BCFG(qlm, BROADCAST),
        c.s.inj_err_cnt_rst_n = 0;
        c.s.inj_err_cnt_en = 0;
        c.s.inj_err_cnt_len = 0;
        c.s.inj_err_burst_en = 0;
        c.s.inj_err_burst_len = 0;
        c.s.pat_dp_width = 3;
        c.s.prbs_dp_width = 3;
        c.s.rx_dp_width = 3;
        c.s.tx_dp_width = 3;
        c.s.core_loopback_mode = 0;
        c.s.sloop_mode = 0;
        c.s.bitstuff_rx_drop_even = 0;
        c.s.bitstuff_rx_en = 0;
        c.s.inv_rx_polarity = 0;
        c.s.reverse_rx_bit_order = 1;
        c.s.fifo_algn_qlm_mask_rsvd = 0;
        c.s.fifo_algn_lane_mask_rsvd = 0;
        c.s.fifo_bypass_en = 0;
        c.s.tx_fifo_pop_start_addr = 6;
        c.s.fifo_rst_n = 1;
        c.s.bitstuff_tx_en = 0;
        c.s.inv_tx_polarity = 0;
        c.s.reverse_tx_bit_order = 1);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, BROADCAST),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 1;
        c.s.binsrch_margin = 5;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 3;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, BROADCAST),
        c.s.rxcdrfsmi = gsern_lane_rxcdrfsmi;
        c.s.rx_dcc_iboost = gsern_lane_rx_dcc_iboost[mode];
        c.s.rx_dcc_lowf = gsern_lane_rx_dcc_lowf[mode];
        c.s.bstuff = 0;
        c.s.rx_idle_lowf = 1;
        c.s.idle_os_bitlen = 0;
        c.s.idle_os_ovrd_en = 0;
        c.s.refset = 8;
        c.s.idle_os_ovrd = 0;
        c.s.en_idle_cal = 1;
        c.s.rxelecidle = 0;
        c.s.rxcdrhold = 0;
        c.s.rxcdrramp = 0;
        c.s.en_sh_lb = 0;
        c.s.erc = gsern_lane_erc[mode];
        c.s.term = gsern_lane_term[mode];
        c.s.en_rt85 = 0;
        c.s.en_lb = 0;
        c.s.en_rterm = 1);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_IDLE_CAL_CFG(qlm, BROADCAST),
        c.s.idle_recal_disable = 0;
        c.s.idle_recal_oob_mode_disable = 0;
        c.s.idle_oob_adder_counter_clear = 0;
        c.s.max_oob_adder_count = 4;
        c.s.oob_delay_adder_count = 0x10000);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, BROADCAST),
        c.s.voter_sp_mask = gsern_lane_voter_sp_mask[mode];
        c.s.rst_n = 1;
        c.s.clk_sel = 2;
        c.s.trunc = 3;
        c.s.limit = 0;
        c.s.eoffs = gsern_lane_eoffs[mode];
        c.s.qoffs = gsern_lane_qoffs[mode];
        c.s.inc2 = gsern_lane_inc2[mode];
        c.s.inc1 = gsern_lane_inc1[mode]);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST1_BCFG(qlm, BROADCAST),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 0;
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 1;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = 0;
        c.s.rx_rst_dcc_i = 0;
        c.s.rx_rst_dcc_e = 0;
        c.s.idle = 0;
        c.s.rx_rst_qac_q = 0;
        c.s.rx_rst_qac_e = 0;
        c.s.rx_rst_blwc = 0;
        c.s.rx_rst_cdrfsm = 0;
        c.s.rx_rst_voter = 0;
        c.s.rx_rst_div_e = 0;
        c.s.rx_rst_div = 0;
        c.s.rx_rst_interp_q = 0;
        c.s.rx_rst_interp_i = 0;
        c.s.rx_rst_interp_e = 0;
        c.s.rx_pd_interp_q = 1;
        c.s.rx_pd_interp_i = 1;
        c.s.rx_pd_interp_e = 1;
        c.s.rx_pd_dfe_x = gsern_lane_rx_pd_dfe_x;
        c.s.rx_pd_dfe_q = gsern_lane_rx_pd_dfe_q;
        c.s.rx_pd_dfe_i = gsern_lane_rx_pd_dfe_i;
        c.s.rx_pd_dfe_e = gsern_lane_rx_pd_dfe_e;
        c.s.rx_pd_dcc_q = 1;
        c.s.rx_pd_dcc_i = 1;
        c.s.rx_pd_dcc_e = 1;
        c.s.rx_pd_biasdac = 1;
        c.s.rx_pd_afe = 1;
        c.s.rx_en_cdrfsm = 0;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 0;
        c.s.fracn_reset = 0;
        c.s.ssc_reset = 0;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_4_BCFG(qlm, BROADCAST),
        c.s.edgesel_even_ovrd_en = gsern_lane_edgesel_even_ovrd_en;
        c.s.edgesel_even_ovrd = gsern_lane_edgesel_even_ovrd;
        c.s.edgesel_odd_ovrd_en = gsern_lane_edgesel_odd_ovrd_en;
        c.s.edgesel_odd_ovrd = gsern_lane_edgesel_odd_ovrd;
        c.s.en_os_afe_ovrd_en = 0;
        c.s.en_os_afe_ovrd = 0;
        c.s.os_afe_odd_ovrd_en = gsern_lane_os_afe_odd_ovrd_en;
        c.s.os_afe_odd_ovrd = gsern_lane_os_afe_odd_ovrd;
        c.s.os_afe_even_ovrd_en = gsern_lane_os_afe_even_ovrd_en[mode];
        c.s.os_afe_even_ovrd = gsern_lane_os_afe_even_ovrd;
        c.s.ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[mode];
        c.s.ctle_lte_gain_ovrd_en = gsern_lane_ctle_lte_gain_ovrd_en;
        c.s.ctle_lte_gain_ovrd = gsern_lane_ctle_lte_gain_ovrd[mode];
        c.s.ctle_zero_ovrd_en = gsern_lane_ctle_zero_ovrd_en;
        c.s.ctle_zero_ovrd = gsern_lane_ctle_zero_ovrd[mode];
        c.s.ctle_gain_ovrd_en = gsern_lane_ctle_gain_ovrd_en[mode];
        c.s.ctle_gain_ovrd = gsern_lane_ctle_gain_ovrd[mode];
        c.s.vga_gain_ovrd_en = gsern_lane_vga_gain_ovrd_en[mode];
        c.s.vga_gain_ovrd = gsern_lane_vga_gain_ovrd[mode]);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, BROADCAST),
        c.s.rxcdrfsmi = gsern_lane_rxcdrfsmi;
        c.s.rx_dcc_iboost = gsern_lane_rx_dcc_iboost[mode];
        c.s.rx_dcc_lowf = gsern_lane_rx_dcc_lowf[mode];
        c.s.bstuff = 0;
        c.s.rx_idle_lowf = 1;
        c.s.idle_os_bitlen = 0;
        c.s.idle_os_ovrd_en = 0;
        c.s.refset = 8;
        c.s.idle_os_ovrd = 0;
        c.s.en_idle_cal = 1;
        c.s.rxelecidle = 0;
        c.s.rxcdrhold = 0;
        c.s.rxcdrramp = 0;
        c.s.en_sh_lb = 0;
        c.s.erc = gsern_lane_erc[mode];
        c.s.term = gsern_lane_term[mode];
        c.s.en_rt85 = 0;
        c.s.en_lb = 0;
        c.s.en_rterm = 1);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_8_BCFG(qlm, BROADCAST),
        c.s.dfe_edgemode_ovrd = 0;
        c.s.dfe_edgemode_ovrd_en = 0;
        c.s.subrate_scale = 7;
        c.s.subrate_init = gsern_lane_subrate_init[mode];
        c.s.subrate_final = gsern_lane_subrate_final[mode]);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_13_BCFG(qlm, BROADCAST),
        c.s.afeos_subrate_scale = 7;
        c.s.afeos_subrate_init = gsern_lane_afeos_subrate_init[mode];
        c.s.afeos_subrate_final = gsern_lane_afeos_subrate_final[mode]);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_20_BCFG(qlm, BROADCAST),
        c.s.blwc_subrate_scale = 7;
        c.s.blwc_subrate_init = gsern_lane_blwc_subrate_init;
        c.s.blwc_subrate_final = gsern_lane_blwc_subrate_final);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_21_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_subrate_now_ovrd_en = 0;
        c.s.prevga_gn_subrate_now_ovrd = 0;
        c.s.prevga_gn_subrate_scale = 7;
        c.s.prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[mode];
        c.s.prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[mode]);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_9_BCFG(qlm, BROADCAST),
        c.s.ctlelte_deadband = gsern_lane_ctlelte_deadband;
        c.s.ctlez_deadband = gsern_lane_ctlez_deadband;
        c.s.ctle_deadband = gsern_lane_ctle_deadband;
        c.s.dfe_deadband = gsern_lane_dfe_deadband;
        c.s.vga_deadband = gsern_lane_vga_deadband);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_19_BCFG(qlm, BROADCAST),
        c.s.blwc_leak_sgn = gsern_lane_blwc_leak_sgn;
        c.s.blwc_updn_len = gsern_lane_blwc_updn_len;
        c.s.blwc_deadband = gsern_lane_blwc_deadband;
        c.s.blwc_deadband_inc = 0;
        c.s.blwc_leak = gsern_lane_blwc_leak;
        c.s.blwc_mu = gsern_lane_blwc_mu;
        c.s.blwc_timer_max = gsern_lane_blwc_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_23_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_leak_sgn = gsern_lane_prevga_gn_leak_sgn;
        c.s.prevga_gn_deadband = gsern_lane_prevga_gn_deadband;
        c.s.prevga_gn_deadband_inc = 0;
        c.s.prevga_gn_leak = gsern_lane_prevga_gn_leak;
        c.s.prevga_gn_mu = gsern_lane_prevga_gn_mu;
        c.s.prevga_gn_timer_max = gsern_lane_prevga_gn_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_12_BCFG(qlm, BROADCAST),
        c.s.afeos_leak_sgn = gsern_lane_afeos_leak_sgn;
        c.s.afeos_deadband = gsern_lane_afeos_deadband;
        c.s.afeos_deadband_inc = 0;
        c.s.afeos_leak = gsern_lane_afeos_leak;
        c.s.afeos_mu = gsern_lane_afeos_mu;
        c.s.afeos_timer_max = gsern_lane_afeos_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_14_BCFG(qlm, BROADCAST),
        c.s.c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[mode];
        c.s.c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[mode];
        c.s.dfe_c1_deadband = gsern_lane_dfe_c1_deadband;
        c.s.dfe_c1_deadband_inc = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST_CNT4_BCFG(qlm, BROADCAST),
        c.s.svc_clk_freq = 0;
        c.s.blwc_reset_wait = 0xf;
        c.s.dfe_afe_oscal_wait = gsern_lane_dfe_afe_oscal_wait);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_6_BCFG(qlm, BROADCAST),
        c.s.ctlez_leak = gsern_lane_ctlez_leak;
        c.s.ctlez_mu = gsern_lane_ctlez_mu;
        c.s.ctlez_timer_max = gsern_lane_ctlez_timer_max;
        c.s.ctle_leak = gsern_lane_ctle_leak;
        c.s.ctle_mu = gsern_lane_ctle_mu;
        c.s.ctle_timer_max = gsern_lane_ctle_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_6A_BCFG(qlm, BROADCAST),
        c.s.ctlelte_leak_sgn = gsern_lane_ctlelte_leak_sgn;
        c.s.ctlelte_leak = gsern_lane_ctlelte_leak;
        c.s.ctlelte_mu = gsern_lane_ctlelte_mu;
        c.s.ctlelte_timer_max = gsern_lane_ctlelte_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_5_BCFG(qlm, BROADCAST),
        c.s.ctle_leak_sgn = gsern_lane_ctle_leak_sgn;
        c.s.ctlez_leak_sgn = gsern_lane_ctlez_leak_sgn;
        c.s.dfe_c1_leak_sgn = gsern_lane_dfe_c1_leak_sgn;
        c.s.vga_leak_sgn = gsern_lane_vga_leak_sgn;
        c.s.dfe_c1_leak = gsern_lane_dfe_c1_leak;
        c.s.dfe_c1_mu = gsern_lane_dfe_c1_mu;
        c.s.vga_leak = gsern_lane_vga_leak;
        c.s.vga_mu = gsern_lane_vga_mu;
        c.s.vga_timer_max = gsern_lane_vga_timer_max;
        c.s.cont_dfe_leak_en = 0;
        c.s.dfe_leak_sgn = gsern_lane_dfe_leak_sgn;
        c.s.dfe_leak = gsern_lane_dfe_leak;
        c.s.dfe_mu = gsern_lane_dfe_mu;
        c.s.dfe_timer_max = gsern_lane_dfe_timer_max);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_1_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_ovrd_en = gsern_lane_prevga_gn_ovrd_en[mode];
        c.s.prevga_gn_ovrd = gsern_lane_prevga_gn_ovrd[mode];
        c.s.blwc_ovrd_en = gsern_lane_blwc_ovrd_en[mode];
        c.s.blwc_ovrd = gsern_lane_blwc_ovrd;
        c.s.c15_ovrd_en = gsern_lane_c15_ovrd_en;
        c.s.c15_ovrd = gsern_lane_c15_ovrd;
        c.s.c14_ovrd_en = gsern_lane_c14_ovrd_en;
        c.s.c14_ovrd = gsern_lane_c14_ovrd;
        c.s.c13_ovrd_en = gsern_lane_c13_ovrd_en;
        c.s.c13_ovrd = gsern_lane_c13_ovrd;
        c.s.c12_ovrd_en = gsern_lane_c12_ovrd_en;
        c.s.c12_ovrd = gsern_lane_c12_ovrd;
        c.s.c11_ovrd_en = gsern_lane_c11_ovrd_en;
        c.s.c11_ovrd = gsern_lane_c11_ovrd;
        c.s.c10_ovrd_en = gsern_lane_c10_ovrd_en;
        c.s.c10_ovrd = gsern_lane_c10_ovrd);

    int c1_limit_lo = bdk_is_model(OCTEONTX_CN96XX_PASS1_X) ?
        gsern_lane_c1_limit_lo_cn96xx[mode] :
        gsern_lane_c1_limit_lo_cnf95xx[mode];

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_15_BCFG(qlm, BROADCAST),
        c.s.c5_limit_hi = gsern_lane_c5_limit_hi[mode];
        c.s.c4_limit_hi = gsern_lane_c4_limit_hi[mode];
        c.s.c3_limit_hi = gsern_lane_c3_limit_hi[mode];
        c.s.c2_limit_hi = gsern_lane_c2_limit_hi[mode];
        c.s.c1_limit_hi = gsern_lane_c1_limit_hi[mode];
        c.s.c5_limit_lo = gsern_lane_c5_limit_lo[mode];
        c.s.c4_limit_lo = gsern_lane_c4_limit_lo[mode];
        c.s.c3_limit_lo = gsern_lane_c3_limit_lo[mode];
        c.s.c2_limit_lo = gsern_lane_c2_limit_lo[mode];
        c.s.c1_limit_lo = c1_limit_lo);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, BROADCAST),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 1;
        c.s.binsrch_margin = 5;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 3;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 1;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 1;
        c.s.rst_tx_rst_sm = 1;
        c.s.rst_pll_rst_sm = 1;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 0;
        c.s.tx_dcc_pdb = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_ITRIM_3_BCFG(qlm, BROADCAST),
        c.s.trim15_ovrd_en = gsern_lane_trim15_ovrd_en;
        c.s.trim14_ovrd_en = gsern_lane_trim14_ovrd_en;
        c.s.trim13_ovrd_en = gsern_lane_trim13_ovrd_en;
        c.s.trim12_ovrd_en = gsern_lane_trim12_ovrd_en;
        c.s.trim11_ovrd_en = gsern_lane_trim11_ovrd_en;
        c.s.trim10_ovrd_en = gsern_lane_trim10_ovrd_en;
        c.s.trim9_ovrd_en = gsern_lane_trim9_ovrd_en;
        c.s.trim8_ovrd_en = gsern_lane_trim8_ovrd_en;
        c.s.trim7_ovrd_en = gsern_lane_trim7_ovrd_en;
        c.s.trim6_ovrd_en = gsern_lane_trim6_ovrd_en;
        c.s.trim5_ovrd_en = gsern_lane_trim5_ovrd_en;
        c.s.trim4_ovrd_en = gsern_lane_trim4_ovrd_en;
        c.s.trim3_ovrd_en = gsern_lane_trim3_ovrd_en;
        c.s.trim2_ovrd_en = gsern_lane_trim2_ovrd_en;
        c.s.trim1_ovrd_en = gsern_lane_trim1_ovrd_en);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_ITRIM_4_BCFG(qlm, BROADCAST),
        c.s.trim31_ovrd_en = gsern_lane_trim31_ovrd_en;
        c.s.trim30_ovrd_en = gsern_lane_trim30_ovrd_en;
        c.s.trim29_ovrd_en = gsern_lane_trim29_ovrd_en;
        c.s.trim28_ovrd_en = gsern_lane_trim28_ovrd_en;
        c.s.trim27_ovrd_en = gsern_lane_trim27_ovrd_en;
        c.s.trim26_ovrd_en = gsern_lane_trim26_ovrd_en;
        c.s.trim25_ovrd_en = gsern_lane_trim25_ovrd_en;
        c.s.trim24_ovrd_en = gsern_lane_trim24_ovrd_en;
        c.s.trim23_ovrd_en = gsern_lane_trim23_ovrd_en;
        c.s.trim22_ovrd_en = gsern_lane_trim22_ovrd_en;
        c.s.trim21_ovrd_en = gsern_lane_trim21_ovrd_en;
        c.s.trim20_ovrd_en = gsern_lane_trim20_ovrd_en;
        c.s.trim19_ovrd_en = gsern_lane_trim19_ovrd_en;
        c.s.trim18_ovrd_en = gsern_lane_trim18_ovrd_en;
        c.s.trim17_ovrd_en = gsern_lane_trim17_ovrd_en;
        c.s.trim16_ovrd_en = gsern_lane_trim16_ovrd_en);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_ITRIM_5_BCFG(qlm, BROADCAST),
        c.s.trim45_ovrd_en = gsern_lane_trim45_ovrd_en;
        c.s.trim44_ovrd_en = gsern_lane_trim44_ovrd_en;
        c.s.trim43_ovrd_en = gsern_lane_trim43_ovrd_en;
        c.s.trim42_ovrd_en = gsern_lane_trim42_ovrd_en;
        c.s.trim41_ovrd_en = gsern_lane_trim41_ovrd_en;
        c.s.trim40_ovrd_en = gsern_lane_trim40_ovrd_en;
        c.s.trim39_ovrd_en = gsern_lane_trim39_ovrd_en;
        c.s.trim38_ovrd_en = gsern_lane_trim38_ovrd_en;
        c.s.trim37_ovrd_en = gsern_lane_trim37_ovrd_en;
        c.s.trim36_ovrd_en = gsern_lane_trim36_ovrd_en;
        c.s.trim35_ovrd_en = gsern_lane_trim35_ovrd_en;
        c.s.trim34_ovrd_en = gsern_lane_trim34_ovrd_en;
        c.s.trim33_ovrd_en = gsern_lane_trim33_ovrd_en;
        c.s.trim32_ovrd_en = gsern_lane_trim32_ovrd_en);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 1;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 1;
        c.s.rst_tx_rst_sm = 1;
        c.s.rst_pll_rst_sm = 1;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 0;
        c.s.tx_dcc_pdb = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RX_10_BCFG(qlm, BROADCAST),
        c.s.ctlelte_deadband_inc = 0;
        c.s.ctlez_deadband_inc = 0;
        c.s.ctle_deadband_inc = 0;
        c.s.dfe_deadband_inc = 2;
        c.s.vga_deadband_inc = 2);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_TX_1_BCFG(qlm, BROADCAST),
        c.s.tx_acjtag = 0;
        c.s.tx_dacj = 0;
        c.s.tx_enloop = 0;
        c.s.nvlink = 0;
        c.s.rx_mod4 = 0;
        c.s.rx_post4 = 0;
        c.s.mod4 = gsern_lane_mod4[mode];
        c.s.div20 = gsern_lane_div20[mode];
        c.s.tx_enfast = gsern_lane_tx_enfast[mode];
        c.s.tx_encm = gsern_lane_tx_encm);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST1_BCFG(qlm, BROADCAST),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 0;
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 0;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = 0;
        c.s.rx_rst_dcc_i = 0;
        c.s.rx_rst_dcc_e = 0;
        c.s.idle = 0;
        c.s.rx_rst_qac_q = 0;
        c.s.rx_rst_qac_e = 0;
        c.s.rx_rst_blwc = 0;
        c.s.rx_rst_cdrfsm = 0;
        c.s.rx_rst_voter = 0;
        c.s.rx_rst_div_e = 0;
        c.s.rx_rst_div = 0;
        c.s.rx_rst_interp_q = 0;
        c.s.rx_rst_interp_i = 0;
        c.s.rx_rst_interp_e = 0;
        c.s.rx_pd_interp_q = 0;
        c.s.rx_pd_interp_i = 0;
        c.s.rx_pd_interp_e = 0;
        c.s.rx_pd_dfe_x = gsern_lane_rx_pd_dfe_x;
        c.s.rx_pd_dfe_q = gsern_lane_rx_pd_dfe_q;
        c.s.rx_pd_dfe_i = gsern_lane_rx_pd_dfe_i;
        c.s.rx_pd_dfe_e = gsern_lane_rx_pd_dfe_e;
        c.s.rx_pd_dcc_q = 0;
        c.s.rx_pd_dcc_i = 0;
        c.s.rx_pd_dcc_e = 0;
        c.s.rx_pd_biasdac = 0;
        c.s.rx_pd_afe = 0;
        c.s.rx_en_cdrfsm = 1;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 2;
        c.s.lock_wait = 2;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 0;
        c.s.fracn_reset = 0;
        c.s.ssc_reset = 0;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 1;
        c.s.pwdn = 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 0;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 0;
        c.s.rst_tx_rst_sm = 0;
        c.s.rst_pll_rst_sm = 0;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 1;
        c.s.tx_dcc_pdb = 1);
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_BIAS_BCFG(qlm),
        c.s.dac1 = (cavm_gsern_voltage > 950) ? 0xf : 0x8;
        c.s.dac0 = 8;
        c.s.bias = 1;
        c.s.bypass = 0;
        c.s.bias_pwdn = 0);

    bdk_scr_add_wait(2500);

    /* Skip REFCLK setup as already done */
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_PLL_2_BCFG(qlm),
        c.s.mio_refclk_en = 1;
        c.s.lock_check_cnt_ovrd_en = 0;
        c.s.lock_check_cnt_ovrd = 0;
        c.s.vcm_sel = 0;
        c.s.cp_boost = 0;
        c.s.ssc_sata_mode = 2;
        c.s.ssc_ppm = 0;
        c.s.pnr_refclk_en = 1;
        c.s.ssc_en = 0;
        c.s.ref_clk_bypass = 1;
        c.s.pfd_offset = 0;
        c.s.opamp = 0;
        c.s.res = 0;
        c.s.vco_bias = 4;
        c.s.cal_dac_low = 4;
        c.s.cal_dac_mid = 8;
        c.s.cal_dac_high = 0xc);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_PCS_BCFG(qlm, BROADCAST),
        c.u = 0xccccccc280649543ull;
        c.s.do_afeos_adpt = build_mode_mask(gsern_lane_do_afeos_adpt);
        c.s.do_ctlelte_adpt = build_mode_mask(gsern_lane_do_ctlelte_adpt);
        c.s.do_ctlez_adpt = build_mode_mask(gsern_lane_do_ctlez_adpt);
        c.s.do_ctle_adpt = build_mode_mask(gsern_lane_do_ctle_adpt);
        c.s.do_dfe_adpt = build_mode_mask(gsern_lane_do_dfe_adpt);
        c.s.do_vga_adpt = build_mode_mask(gsern_lane_do_vga_adpt);
        c.s.do_blwc_adpt = build_mode_mask(gsern_lane_do_blwc_adpt));
    /* The PEM/QLM combination determines which pipe must be selected */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_PCS2_BCFG(qlm, BROADCAST),
        c.u = 0xf00000000000fcull;
        c.s.pipe_tx_sel = ((pem == 2) && (qlm == 3)) ? 2 : 0;
        c.s.do_prevga_gn_adpt = build_mode_mask(gsern_lane_do_prevga_gn_adpt));
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_PCS3_BCFG(qlm, BROADCAST),
        c.u = 0xb0cf003cfffull;
        c.s.tx_enfast = build_mode_mask(gsern_lane_tx_enfast);
        c.s.do_afeos_final = build_mode_mask(gsern_lane_do_afeos_final);
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final ? 0xf : 0;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final ? 0xf : 0;
        c.s.do_ctle_final = gsern_lane_do_ctle_final ? 0xf : 0;
        c.s.do_dfe_final = build_mode_mask(gsern_lane_do_dfe_final);
        c.s.do_vga_final = build_mode_mask(gsern_lane_do_vga_final);
        c.s.do_blwc_final = build_mode_mask(gsern_lane_do_blwc_final);
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final ? 0xf : 0);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_PCS3_BCFG(qlm, 0),
        c.u = 0xb0cf003cfffull;
        c.s.tx_enfast = build_mode_mask(gsern_lane_tx_enfast);
        c.s.do_afeos_final = build_mode_mask(gsern_lane_do_afeos_final);
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final ? 0xf : 0;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final ? 0xf : 0;
        c.s.do_ctle_final = gsern_lane_do_ctle_final ? 0xf : 0;
        c.s.do_dfe_final = build_mode_mask(gsern_lane_do_dfe_final);
        c.s.do_vga_final = build_mode_mask(gsern_lane_do_vga_final);
        c.s.do_blwc_final = build_mode_mask(gsern_lane_do_blwc_final);
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final ? 0xf : 0;
        c.s.lane_is_0 = (qlm ==0) || (qlm == 6));
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_RST_CNT1_BCFG(qlm),
        c.s.cal_en_wait = 7;
        c.s.pre_cal_en_wait = 2;
        c.s.pre_pwup_wait = 0x3ff);
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_RST_CNT2_BCFG(qlm),
        c.s.pre_run_wait = 7;
        c.s.pre_pll_sm_reset_wait = 1;
        c.s.pre_pdiv_reset_wait = 5;
        c.s.pre_pll_reset_wait = 2);
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.domain_rst_en = 0;
        c.s.rst_pll_rst_sm = 1;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 1;
        c.s.fracn_reset = 1;
        c.s.ssc_reset = 1;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);
    SCR_ADD_WRITE(BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.domain_rst_en = 0;
        c.s.rst_pll_rst_sm = 0;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 1;
        c.s.fracn_reset = 1;
        c.s.ssc_reset = 1;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);

    /* Adjust presence detection timeout */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, BROADCAST),
        c.s.sample_wait = 4;
        c.s.tx_disable = 1;
        c.s.samn_en = 1;
        c.s.samp_en = 1;
        c.s.rxd_en = 1);

    /* Errata GSERN-36412: GSER IDLE GLITCH
       For EP mode: force X8 rx detect, this is the only way that
       the TAP override can be applied at same time and EP will work
       in a mode without code intervention, with the exception of SCP.
       Assume this code ONLY runs for EP configuration.
       */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
    {
        /* Adjust presence detection timeout     */
        /* add lane swizzle                      */
        /* Typically, width is 4                 */
        /* Because of lane swizzle, upper lanes  */
        /* This will only work for x4,x8 and x16 */
        SCR_ADD_WRITE(BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm,BROADCAST),
            c.s.sample_wait = 4;
            c.s.tx_disable = 1;
            c.s.samn_en = 1;
            c.s.samp_en = 1;
            c.s.ovrride_det_en = 1;
            c.s.ovrride_det    = 1;
            c.s.rxd_en = 1);

        /* Preset table includes GEN1,GEN2, so add 2 to get correct table index */
        /* The transmitter bias is in the table, but we want to control the     */
        /* amplitude, since some receivers may not be able to handle that drive */

        /* NOTE: Do not set the en_tx_bs values in this register, set them       */
        /* In the GSERNX_LANEX_PCIE_TXBIAS_BCFG                                  */
        /* We only want to override the de-emphasis values                       */

        tx_tap_drv_override_t *tbl_ptr = (tx_tap_drv_override_t *)&tx_tap_drv_override_gen123[txpreset];
        SCR_ADD_WRITE(BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm,BROADCAST),
            c.s.muxpost   = tbl_ptr->muxpost;
            c.s.cpostb    = tbl_ptr->cpostb;
            c.s.cposta    = tbl_ptr->cposta;
            c.s.enpost    = tbl_ptr->enpost;
            c.s.muxmain   = tbl_ptr->muxmain;
            c.s.cmaind    = tbl_ptr->cmaind;
            c.s.enmain    = tbl_ptr->enmain;
            c.s.muxpre    = tbl_ptr->muxpre;
            c.s.cpreb     = tbl_ptr->cpreb;
            c.s.cprea     = tbl_ptr->cprea;
            c.s.enpre     = tbl_ptr->enpre;
            c.s.en_tx_drv = 1);
    }
    else
    {
        /* Adjust presence detection timeout */
        SCR_ADD_WRITE(BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, BROADCAST),
            c.s.sample_wait = 4;
            c.s.tx_disable = 1;
            c.s.samn_en = 1;
            c.s.samp_en = 1;
            c.s.rxd_en = 1);
    }

    /* Idle Detect Threshold
        Set GEN1,GEN2,GEN3,GEN4
        This change Aligns With Joe Vulih recommendation to
        Use a value of '4' for REFSET.  The value of 8
        Was causing issues with EP mode with adaptation failures
        This value is also same as ethernet */

    /* Use the value from device tree to allow changes across platforms */
    /* The same value is used for GEN1,GEN2,GEN3 and GEN4 speeds */
    int serdes_recalibration_refset_pcie_value = bdk_config_get_int(BDK_CONFIG_PCIE_IDLE_REFSET_VALUE, BDK_NODE_0, qlm);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXIDL1A_BCFG(qlm, BROADCAST),
        c.s.l1 = 1;
        c.s.l0 = 1;
        c.s.rx_idle_lowf = 1;
        c.s.refset = serdes_recalibration_refset_pcie_value);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXIDL2A_BCFG(qlm, BROADCAST),
        c.s.l1 = 1;
        c.s.l0 = 1;
        c.s.rx_idle_lowf = 1;
        c.s.refset = serdes_recalibration_refset_pcie_value);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXIDL3A_BCFG(qlm, BROADCAST),
        c.s.l1 = 1;
        c.s.l0 = 1;
        c.s.rx_idle_lowf = 1;
        c.s.refset = serdes_recalibration_refset_pcie_value);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXIDL4A_BCFG(qlm, BROADCAST),
        c.s.l1 = 1;
        c.s.l0 = 1;
        c.s.rx_idle_lowf = 1;
        c.s.refset = serdes_recalibration_refset_pcie_value);

    /* Adjust PCIe per Gen Rx equalization settings */
    /* PCIe Gen1 */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ1_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g1_erc = gsern_lane_erc[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g1_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_02500000000];
        c.s.pcie_g1_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g1_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_02500000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ1_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_02500000000];
        c.s.pcie_g1_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_02500000000];
        c.s.pcie_g1_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_02500000000];
        c.s.pcie_g1_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_02500000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ1_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_limit_lo = c1_limit_lo);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ1_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_02500000000];
        c.s.pcie_g1_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_02500000000];
        c.s.pcie_g1_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g1_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen2 */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ2_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g2_erc = gsern_lane_erc[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g2_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_05000000000];
        c.s.pcie_g2_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g2_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_05000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ2_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_05000000000];
        c.s.pcie_g2_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_05000000000];
        c.s.pcie_g2_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_05000000000];
        c.s.pcie_g2_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_05000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ2_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_limit_lo = c1_limit_lo);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ2_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_05000000000];
        c.s.pcie_g2_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_05000000000];
        c.s.pcie_g2_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g2_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen3 */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ3_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g3_erc = gsern_lane_erc[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g3_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_08000000000];
        c.s.pcie_g3_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g3_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_08000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ3_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_08000000000];
        c.s.pcie_g3_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_08000000000];
        c.s.pcie_g3_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_08000000000];
        c.s.pcie_g3_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_08000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ3_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_limit_lo = c1_limit_lo);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ3_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_08000000000];
        c.s.pcie_g3_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_08000000000];
        c.s.pcie_g3_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g3_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen4 */
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ4_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g4_erc = gsern_lane_erc[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g4_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_16000000000];
        c.s.pcie_g4_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g4_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_16000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ4_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_16000000000];
        c.s.pcie_g4_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_16000000000];
        c.s.pcie_g4_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_16000000000];
        c.s.pcie_g4_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_16000000000]);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ4_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_limit_lo = c1_limit_lo);

    SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_RXEQ4_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_16000000000];
        c.s.pcie_g4_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_16000000000];
        c.s.pcie_g4_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g4_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* Tell software the QLM mode */
    bdk_qlm_modes_t qlm_mode;
    const char *ep_string = "PCIE_X4-EP";
    switch (width)
    {
        case 1:
            qlm_mode = BDK_QLM_MODE_PCIE_X1;
            break;
        case 2:
            qlm_mode = BDK_QLM_MODE_PCIE_X2;
            break;
        case 4:
            qlm_mode = BDK_QLM_MODE_PCIE_X4;
            break;
        case 8:
            qlm_mode = BDK_QLM_MODE_PCIE_X8;
            ep_string = "PCIE_X8-EP";
            break;
        default:
            qlm_mode = BDK_QLM_MODE_PCIE_X16;
            ep_string = "PCIE_X16-EP";
            break;
    }

    // Find out what to use for the PCIe Bias Strength      */
    // Note: this is for EP only, RC is handled already     */
    int node = 0;
    int lane = 0;
    int tx_bs = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_BS, ep_string, speed, node, qlm, lane);
    if (tx_bs > 0)
    {
        SCR_ADD_WRITE(BDK_GSERNX_LANEX_PCIE_TXBIAS_BCFG(qlm, BROADCAST),
            c.s.tx_margin_h4 = 0x0;
            c.s.tx_margin_h3 = 0x5;
            c.s.tx_margin_h2 = 0xa;
            c.s.tx_margin_h1 = 0x11;
            c.s.tx_bias_half = 0x16;
            c.s.tx_margin_f4 = 0x7;
            c.s.tx_margin_f3 = 0x11;
            c.s.tx_margin_f2 = 0x1b;
            c.s.tx_margin_f1 = 0x2a;
            c.s.tx_bias_full = tx_bs);
    }

    bdk_qlm_state_lane_t qlm_state = __bdk_qlm_build_state(qlm_mode, speed, BDK_QLM_MODE_FLAG_ENDPOINT);
    SCR_ADD_WRITE(BDK_GSERNX_LANEX_SCRATCHX(qlm, BROADCAST, 0),
        c.u = qlm_state.u);

    return 0;
}

static int scr_setup_pem(int pem, int width, int speed)
{
    SCR_ADD_WRITE(BDK_RST_CTLX(pem),
        c.s.reset_type = 0; /* Chip and core reset */
        c.s.rst_pwrdwn = 0; /* Don't cause internal reset on power down */
        c.s.prst_pwrdwn = 0; /* Don't reset PEM on power down */
        c.s.pf_flr_chip = 0; /* FLR doesn't cause chip reset */
        c.s.prst_link = 0; /* Don't reset PEM on loss of link */
        c.s.rst_link = 0; /* Don't reset on loss of link */
        c.s.rst_drv = 0; /* Reset is an input, don't drive */
        c.s.rst_rcv = 1; /* Receive reset from RC */
        c.s.rst_chip = 0); /* Don't reset the chip on reset from RC */
    SCR_ADD_WRITE(BDK_RST_SOFT_PRSTX(pem), /* zero */);
    SCR_ADD_WRITE(BDK_PEMX_CLK_EN(pem), /* zero */);
    SCR_ADD_WRITE(BDK_PEMX_ON(pem),
        c.s.pemon = 1);

    /* Wait for PEM reset complete */
    bdk_pemx_on_t pemx_on;
    pemx_on.u = 0;
    pemx_on.s.pemoor = 1;
    pemx_on.s.pemon = 1;

    const int PEM_TIMEOUT_NS = 1000;
    bdk_scr_add_poll(bustype_BDK_PEMX_ON(pem), pem, 8, BDK_PEMX_ON(pem), pemx_on.u, pemx_on.u, BDK_SCR_CMP_TYPE_E_NE, PEM_TIMEOUT_NS);

    SCR_ADD_WRITE(BDK_PEMX_CTL_STATUS(pem),
        c.s.clk_req_n = 1;
        c.s.rdy_entr_l23 = 1);
    SCR_ADD_WRITE(BDK_PEMX_LTR_VALX(pem,0),
        c.s.ns_lat = 0x2423;
        c.s.snoop_lat = 0xfff1);
    SCR_ADD_WRITE(BDK_PEMX_LTR_VALX(pem,1),
        c.s.ns_lat = 0xc718;
        c.s.snoop_lat = 0x3caa);
    SCR_ADD_WRITE(BDK_PEMX_EBUS_CTL(pem),
        c.s.ebo_stf = 1;
        c.s.vf_bar2_sel = 1;
        c.s.vf_bar4_sel = 1;
        c.s.vf_bar0_sel = 1;
        c.s.pf_bar0_sel = 1;
        c.s.atomic_dis = 1;
        c.s.vdm_dis = 1);
    /* Program the EROM size in the PEM */
    int erom_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_ROM_SIZE, BDK_NODE_0, pem);
    if (erom_bits > 0)
    {
        if (erom_bits > 22)
            erom_bits = 22;
        if (erom_bits < 16)
            erom_bits = 16;
        SCR_ADD_WRITE(BDK_PEMX_EROM_SIZE(pem),
            c.s.erom_siz = erom_bits - 15);
    }
    return 0;
}

static int scr_setup_pcieep(int pem, int width, int speed)
{
    const int num_pfs = bdk_config_get_int(BDK_CONFIG_PCIE_EP_NUM_PFS, BDK_NODE_0, pem); /* Can be 1-16 */
    const int num_vfs = bdk_config_get_int(BDK_CONFIG_PCIE_EP_NUM_VFS, BDK_NODE_0, pem); /* Can be 0-16 */
    int tbl = 0;
    /* Fill autoplay table */
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_C_RCV_CREDIT(pem),
        c.s.vc0_cds = 1;
        c.s.vc0_chs = 1;
        c.s.queue_mode = 2;
        c.s.header_credits = 0;
        c.s.data_credits = 0,
        /* table options */);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_TIMER_CTL(pem),
        c.s.flmsf = 1;
        c.s.updft = 0;
        c.s.tmanlt = 0;
        c.s.tmrt = 8;
        c.s.mfuncn = num_pfs - 1,
        /* table options */);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SYMB_TIMER(pem),
        c.s.m_cfg0_filt = 0;
        c.s.m_io_filt = 0;
        c.s.msg_ctrl = 0;
        c.s.m_cpl_ecrc_filt = 0;
        c.s.m_ecrc_filt = 0;
        c.s.m_cpl_len_err = 0;
        c.s.m_cpl_attr_err = 0;
        c.s.m_cpl_tc_err = 0;
        c.s.m_cpl_fun_err = 0;
        c.s.m_cpl_rid_err = 0;
        c.s.m_cpl_tag_err = 0;
        c.s.m_lk_filt = 0;
        c.s.m_cfg1_filt = 1;
        c.s.m_bar_match = 0;
        c.s.m_pois_filt = 1;
        c.s.m_fun = 0;
        c.s.dfcwt = 0;
        c.s.eidle_timer = 0;
        c.s.skpiv = 0x140,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_ID(pem),
        c.u = bdk_config_get_int(BDK_CONFIG_PCIE_EP_ID, BDK_NODE_0, pem),
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_MSIX_CAP_CNTRL(pem),
        c.s.msixen = 1;
        c.s.funm = 0;
        c.s.msixts = 0x4f;
        c.s.ncp = 0x0;
        c.s.msixcid = 0x11,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    /* Program BAR0 mask. Program BAR0 for 8MB and enabled */
    int bar0_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 0, BDK_NODE_0, pem);
    if (bar0_bits == -1)
        bar0_bits = 23; /* 8MB */
    int bar0_enable = (bar0_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR0_MASKL(pem),
        c.s.lmask = bdk_build_mask(bar0_bits) >> 1; /* ENB uses low bit */
        c.s.enb = bar0_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR0_MASKU(pem),
        c.u = bdk_build_mask(bar0_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!bar0_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR0L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    /* Program BAR2 mask. Program BAR2 for 256MB and enabled */
    int bar2_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 2, BDK_NODE_0, pem);
    if (bar2_bits == -1)
        bar2_bits = 28; /* 256MB */
    int bar2_enable = (bar2_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR2_MASKL(pem),
        c.s.lmask = bdk_build_mask(bar2_bits) >> 1; /* ENB uses low bit */
        c.s.enb = bar2_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR2_MASKU(pem),
        c.u = bdk_build_mask(bar2_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!bar2_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR2L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    /* Program BAR4 mask. Program BAR4 for 64MB and enabled */
    int bar4_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_BAR_SIZE, 4, BDK_NODE_0, pem);
    if (bar4_bits == -1)
        bar4_bits = 26; /* 64MB */
    int bar4_enable = (bar4_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR4_MASKL(pem),
        c.s.lmask = bdk_build_mask(bar4_bits) >> 1; /* ENB uses low bit */
        c.s.enb = bar4_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR4_MASKU(pem),
        c.u = bdk_build_mask(bar4_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!bar4_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_BAR4L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    /* Program EROM mask. Program EROM for 4KB and enabled */
    int erom_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_ROM_SIZE, BDK_NODE_0, pem);
    int erom_enable = (erom_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_EROM_MASK(pem),
        c.s.mask = bdk_build_mask(erom_bits) >> 1; /* ENB uses low bit */
        c.s.enb = erom_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    /* If we have an expansion rom declared, enable it  */
    if (erom_enable)
    {
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_EBAR(pem),
            c.s.er_en = 1,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_INT(pem),
        c.s.ml = 0;
        c.s.mg = 0;
        c.s.inta = 1;
        c.s.il = 0xff,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_ARI_FO(pem),
        c.s.vfs = 1;
        c.s.fo = 0x10,
        /* table options */
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_FO(pem),
        c.s.vfs = 1;
        c.s.fo = 0x100,
        /* table options */);
    tbl++;
    int sriov_bar0_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 0, BDK_NODE_0, pem);
    if (sriov_bar0_bits == -1)
        sriov_bar0_bits = 20; /* 1MB */
    int sriov_bar0_enable = (sriov_bar0_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR0_MASKL(pem),
        c.s.lmask = bdk_build_mask(sriov_bar0_bits) >> 1; /* ENB uses low bit */
        c.s.enb = sriov_bar0_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR0_MASKU(pem),
        c.u = bdk_build_mask(sriov_bar0_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!sriov_bar0_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR0L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    int sriov_bar2_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 2, BDK_NODE_0, pem);
    if (sriov_bar2_bits == -1)
        sriov_bar2_bits = 0; /* Disabled */
    int sriov_bar2_enable = (sriov_bar2_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR2_MASKL(pem),
        c.s.lmask = bdk_build_mask(sriov_bar2_bits) >> 1; /* ENB uses low bit */
        c.s.enb = sriov_bar2_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR2_MASKU(pem),
        c.u = bdk_build_mask(sriov_bar2_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!sriov_bar2_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR2L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    int sriov_bar4_bits = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_BAR_SIZE, 4, BDK_NODE_0, pem);
    if (sriov_bar4_bits == -1)
        sriov_bar4_bits = 0; /* Disabled */
    int sriov_bar4_enable = (sriov_bar4_bits > 0);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR4_MASKL(pem),
        c.s.lmask = bdk_build_mask(sriov_bar4_bits) >> 1; /* ENB uses low bit */
        c.s.enb = sriov_bar4_enable,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR4_MASKU(pem),
        c.u = bdk_build_mask(sriov_bar4_bits) >> 32,
        /* table options */
        t.s.broadcast = 1;
        t.s.shadow = 1);
    tbl++;
    if (!sriov_bar4_enable)
    {
        /* Disable lower bits on disabled BAR */
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_BAR4L(pem),
            c.u = 0,
            /* table options */
            t.s.broadcast = 1);
        tbl++;
    }
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_REV(pem),
        c.u = bdk_config_get_int(BDK_CONFIG_PCIE_EP_REV, BDK_NODE_0, pem),
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_MSIX_PBA(pem),
        c.s.msixpoffs = 0x800;
        c.s.msixpbir = 0,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SN_DW1(pem),
        c.s.dsn_dw1 = 0,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SN_DW2(pem),
        c.s.dsn_dw2 = 0,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_RASDP_DE_ME(pem),
        c.s.auto_lnk_dn_en = 0;
        c.s.err_mode_en = 1,
        /* table options */);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_RBAR_CAP(pem),
        c.s.srs = 0xfffffff,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_RBAR_CTL(pem),
        c.s.esrs = 0x7f;
        c.s.rbars = (bar2_bits) ? bar2_bits - 20 : 0;
        c.s.nrbar = 1;
        c.s.rbari = 2,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_DEV(pem),
        c.s.vfdev = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SRIOV_DEV, BDK_NODE_0, pem),
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_VFS(pem),
        c.s.tvf = num_vfs; /* Total number of VFs */
        c.s.ivf = num_vfs, /* Initial number of VFs */
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_RBAR_CAP_HDR(pem),
        c.s.nco = 0x4c8;
        c.s.cv = 1;
        c.s.pcieec = 0x15,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PTM_CAP(pem),
        c.s.clkg = 0x10;
        c.s.rtc = 0;
        c.s.rsc = 0;
        c.s.rqc = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PTM_REQ_TLAT(pem),
        c.s.rtl = 0x20,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PTM_REQ_RLAT(pem),
        c.s.rrl = 0x40,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    int lme;
    switch (width)
    {
        case 1:
            lme = 1;
            break;
        case 2:
            lme = 3;
            break;
        case 4:
            lme = 7;
            break;
        case 8:
            lme = 15;
            break;
        default:
            lme = 31;
            break;
    }
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PORT_CTL(pem),
        c.s.xlr_en = 0;
        c.s.ex_synch = 0;
        c.s.clcrc_en = 0;
        c.s.beacon_en = 0;
        c.s.cle = 0;
        c.s.lme = lme;
        c.s.link_rate = 1;
        c.s.flm = 0;
        c.s.ldis = 0;
        c.s.dllle = 1;
        c.s.ra = 0;
        c.s.le = 0;
        c.s.sd = 0;
        c.s.omr = 0,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    int mls;
    switch (speed)
    {
        case 2500:
            mls = 1;
            break;
        case 5000:
            mls = 2;
            break;
        case 8000:
            mls = 3;
            break;
        default:
            mls = 4;
            break;
    }

    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_LINK_CAP(pem),
        c.s.pnum = 0;
        c.s.aspm = 1;
        c.s.lbnc = 0;
        c.s.dllarc = 0;
        c.s.sderc = 0;
        c.s.cpm = 0;
        c.s.l1el = 6;
        c.s.l0el = 7;
        c.s.aslpms = 0;
        c.s.mlw = width;
        c.s.mls = mls,
        /* table options */
        t.s.broadcast = 1);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_LINK_CTL2(pem),
        c.s.tls = mls,
        /* table options */);
    tbl++;
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PTM_CAP(pem),
        c.s.clkg = 0x10;
        c.s.rtc = 0;
        c.s.rsc = 0;
        c.s.rqc = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    for (int pf = 1; pf < num_pfs; pf++)
    {
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_ARI_FO(pem),
            c.s.vfs = 1;
            c.s.fo = 0x10 + pf * 0xf,
            /* table options */
            t.s.pf = pf;
            t.s.shadow = 1);
        tbl++;
        SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SRIOV_FO(pem),
            c.s.vfs = 1;
            c.s.fo = 0x100 + pf * 0xff,
            /* table options */
            t.s.pf = pf);
        tbl++;
    }

    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_HIDE_PF(pem),
        c.s.hide_pf15 = (num_pfs > 15) ? 0 : 2;
        c.s.hide_pf14 = (num_pfs > 14) ? 0 : 2;
        c.s.hide_pf13 = (num_pfs > 13) ? 0 : 2;
        c.s.hide_pf12 = (num_pfs > 12) ? 0 : 2;
        c.s.hide_pf11 = (num_pfs > 11) ? 0 : 2;
        c.s.hide_pf10 = (num_pfs > 10) ? 0 : 2;
        c.s.hide_pf9 = (num_pfs > 9) ? 0 : 2;
        c.s.hide_pf8 = (num_pfs > 8) ? 0 : 2;
        c.s.hide_pf7 = (num_pfs > 7) ? 0 : 2;
        c.s.hide_pf6 = (num_pfs > 6) ? 0 : 2;
        c.s.hide_pf5 = (num_pfs > 5) ? 0 : 2;
        c.s.hide_pf4 = (num_pfs > 4) ? 0 : 2;
        c.s.hide_pf3 = (num_pfs > 3) ? 0 : 2;
        c.s.hide_pf2 = (num_pfs > 2) ? 0 : 2;
        c.s.hide_pf1 = (num_pfs > 1) ? 0 : 2;
        c.s.hide_pf0 = (num_pfs > 0) ? 0 : 2,
        /* table options */);
    tbl++;

    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_SUBSYS(pem),
        c.u = bdk_config_get_int(BDK_CONFIG_PCIE_EP_SUBSYS, BDK_NODE_0, pem),
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    int ep_gen3_prv = bdk_config_get_int(BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR, BDK_NODE_0, pem);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_GEN3_EQ_CTL(pem),
        c.s.scefpm = 1;
        c.s.iif = 0;
        c.s.prv = ep_gen3_prv;
        c.s.eq_redo_en = 1;
        c.s.p23td = 1;
        c.s.bt = 0;
        c.s.fm = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    /* Setup shadow register for GEN4, set rss bit */
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PHY_GEN3_CTL(pem),
        c.s.rss = 1;
        c.s.rxeq_rgrdless_rsts = 1;
        c.s.erd = 1;
        c.s.ecrd = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    /* Now write PRV value, same as GEN3 */
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_GEN3_EQ_CTL(pem),
        c.s.scefpm = 1;
        c.s.iif = 0;
        c.s.prv = ep_gen3_prv;
        c.s.eq_redo_en = 1;
        c.s.p23td = 1;
        c.s.bt = 0;
        c.s.fm = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    /* clear rss bit when done */
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_PHY_GEN3_CTL(pem),
        c.s.rss = 0;
        c.s.rxeq_rgrdless_rsts = 1;
        c.s.erd = 1;
        c.s.ecrd = 1,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    int ep_gen2_deemph = bdk_config_get_int(BDK_CONFIG_PCIE_GEN2_DEEMPHASIS, BDK_NODE_0, pem);
    SCR_ADD_PCIEEP_WRITE(pem, tbl, BDK_PCIEEPX_GEN2_PORT(pem),
        c.s.gen1_ei_inf = 0;
        c.s.s_d_e = ep_gen2_deemph;
        c.s.ctcrb = 0;
        c.s.cpyts = 0;
        c.s.dsc = 0;
        c.s.alaneflip = 1;
        c.s.pdetlane = 0;
        c.s.nlanes = 1;
        c.s.n_fts = 0x7d,
        /* table options */
        t.s.broadcast = 1);
    tbl++;

    SCR_ADD_WRITE(BDK_PEMX_CFG_TBL_SIZE(pem),
        c.s.size = tbl);
    return 0;
}

/**
 * Create a default script for use in booting
 *
 * @return Zero on success, negative on failure
 */
int bdk_scr_create_default(void)
{
    if (bdk_scr_init())
        return -1;

    /* Get QLM0 modes */
    bdk_qlm_modes_t qlm0_mode = BDK_QLM_MODE_DISABLED;
    int qlm0_freq = 0;
    bdk_qlm_clock_t qlm0_clk = BDK_QLM_CLK_LAST;
    int qlm0_term = -1;
    bdk_qlm_mode_flags_t qlm0_flags = BDK_QLM_MODE_FLAG_NONE;
    const char *cfg_val = bdk_config_get_str(BDK_CONFIG_QLM_MODE, BDK_NODE_0, 0, 0);
    if (cfg_val)
    {
        qlm0_mode = bdk_qlm_cfg_string_to_mode(cfg_val);
        qlm0_freq = bdk_config_get_int(BDK_CONFIG_QLM_FREQ, BDK_NODE_0, 0, 0);
        qlm0_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 0);
        qlm0_term = bdk_config_get_int(BDK_CONFIG_QLM_CLK_TERM, BDK_NODE_0, 0);
        if (strstr(cfg_val, "-EP"))
            qlm0_flags = BDK_QLM_MODE_FLAG_ENDPOINT;
    }

    /* Get QLM3 modes */
    bdk_qlm_modes_t qlm3_mode = BDK_QLM_MODE_DISABLED;
    int qlm3_freq = 0;
    bdk_qlm_clock_t qlm3_clk = BDK_QLM_CLK_LAST;
    int qlm3_term = -1;
    bdk_qlm_mode_flags_t qlm3_flags = BDK_QLM_MODE_FLAG_NONE;
    cfg_val = bdk_config_get_str(BDK_CONFIG_QLM_MODE, BDK_NODE_0, 3, 0);
    if (cfg_val)
    {
        qlm3_mode = bdk_qlm_cfg_string_to_mode(cfg_val);
        qlm3_freq = bdk_config_get_int(BDK_CONFIG_QLM_FREQ, BDK_NODE_0, 3, 0);
        qlm3_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 3);
        qlm3_term = bdk_config_get_int(BDK_CONFIG_QLM_CLK_TERM, BDK_NODE_0, 3);
        if (strstr(cfg_val, "-EP"))
            qlm3_flags = BDK_QLM_MODE_FLAG_ENDPOINT;

    }

    /* Get QLM6 modes */
    bdk_qlm_modes_t qlm6_mode = BDK_QLM_MODE_DISABLED;
    int qlm6_freq = 0;
    bdk_qlm_clock_t qlm6_clk = BDK_QLM_CLK_LAST;
    int qlm6_term = -1;
    bdk_qlm_mode_flags_t qlm6_flags = BDK_QLM_MODE_FLAG_NONE;
    cfg_val = bdk_config_get_str(BDK_CONFIG_QLM_MODE, BDK_NODE_0, 6, 0);
    if (cfg_val)
    {
        qlm6_mode = bdk_qlm_cfg_string_to_mode(cfg_val);
        qlm6_freq = bdk_config_get_int(BDK_CONFIG_QLM_FREQ, BDK_NODE_0, 6, 0);
        qlm6_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 6);
        qlm6_term = bdk_config_get_int(BDK_CONFIG_QLM_CLK_TERM, BDK_NODE_0, 6);
        if (strstr(cfg_val, "-EP"))
            qlm6_flags = BDK_QLM_MODE_FLAG_ENDPOINT;
    }

    int width0 = 0;
    if ((qlm0_flags & BDK_QLM_MODE_FLAG_ENDPOINT) &&
        (qlm0_mode >= BDK_QLM_MODE_PCIE_X1) &&
        (qlm0_mode <= BDK_QLM_MODE_PCIE_X16))
        width0 = 1 << (qlm0_mode - BDK_QLM_MODE_PCIE_X1);
    int width2 = 0;
    if ((qlm3_flags & BDK_QLM_MODE_FLAG_ENDPOINT) &&
        (qlm3_mode >= BDK_QLM_MODE_PCIE_X1) &&
        (qlm3_mode <= BDK_QLM_MODE_PCIE_X16))
        width2 = 1 << (qlm3_mode - BDK_QLM_MODE_PCIE_X1);
    else if ((qlm6_flags & BDK_QLM_MODE_FLAG_ENDPOINT) &&
        (qlm6_mode >= BDK_QLM_MODE_PCIE_X1) &&
        (qlm6_mode <= BDK_QLM_MODE_PCIE_X16))
        width2 = 1 << (qlm6_mode - BDK_QLM_MODE_PCIE_X1);

    /* Determine if PEM2 is on either QLM3 or QLM6 */
    bool isqlm3 = ((qlm3_mode >= BDK_QLM_MODE_PCIE_X1) && (qlm3_mode <= BDK_QLM_MODE_PCIE_X16));
    int pem2qlm = isqlm3 ? 3 : 6;
    bdk_qlm_clock_t clk2 = isqlm3 ? qlm3_clk : qlm6_clk;
    int clk_term2 = isqlm3 ? qlm3_term : qlm6_term;
    int freq2 = isqlm3 ? qlm3_freq : qlm6_freq;

    /* Setup common reference clocks */
    BDK_CSR_INIT(refc_ctl, BDK_NODE_0, BDK_RST_REFC_CTL);

    if (qlm0_clk == BDK_QLM_CLK_COMMON_1)
    {
        refc_ctl.s.cclk1_sel = qlm0_term & 3;
        refc_ctl.s.cclk1_pwdn = 0;
    }
    else if (clk2 == BDK_QLM_CLK_COMMON_1)
    {
        refc_ctl.s.cclk1_sel = clk_term2 & 3;
        refc_ctl.s.cclk1_pwdn = 0;
    }

    if (qlm0_clk == BDK_QLM_CLK_COMMON_2)
    {
        refc_ctl.s.cclk2_sel = qlm0_term & 3;
        refc_ctl.s.cclk2_pwdn = 0;
    }
    else if (clk2 == BDK_QLM_CLK_COMMON_2)
    {
        refc_ctl.s.cclk2_sel = clk_term2 & 3;
        refc_ctl.s.cclk2_pwdn = 0;
    }
    SCR_ADD_WRITE(BDK_RST_REFC_CTL,
        c = refc_ctl);

    /* Loop through PEM0 and PEM2, provided they are to be configured   */
    for (int pem = 0; pem <= 2; pem += 2)
    {
        /* if pem0 not to be configured, continue */
        if ((pem == 0) && (width0 == 0))
              continue;

        /* if pem0 not to be configured, continue */
        if ((pem == 2) && (width2 == 0))
              continue;

        /* Pick settings based on which PEM */
        int qlm = (pem) ? pem2qlm : 0; /* PEM0 is QLM0+, PEM2 is specified */
        int width = (pem) ? width2 : width0;
        int freq = (pem) ? freq2 : qlm0_freq;

        /* Read the device tree entries to see if we are overriding */
        /* EP Transmit Preset Override Only Valid for T96           */
        int txpreset=0;
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
        {
            int endpoint_tx_preset = bdk_config_get_int(BDK_CONFIG_PCIE_ENDPOINT_TX_PRESET_OVERRIDE, BDK_NODE_0, pem);

            /* If GEN1 - use preset 1, which is 3.5 db */
            if (freq <= 2500)
                txpreset = 1;
            else if (freq <= 5000)
            {
                txpreset = (endpoint_tx_preset >= 0) ? endpoint_tx_preset  : 0 ;
                /* GEN1 uses preset 1, GEN2 uses preset 0 for -6 db or 1 for -3.5 db */
                if (txpreset > 1)
                {
                    printf ("Warning: Endpoint Preset for GEN2 can only be 0 or 1,default to 0 (-6 db)\n");
                    txpreset = 0;
                }
            }
            else if (freq >= 8000)
            {
                txpreset = (endpoint_tx_preset >= 0) ? endpoint_tx_preset  : 0;
                if (txpreset > 10)
                {
                    printf("Warning: GEN3 Endpoint Preset Can only be 0 to 10, default to 4\n");
                    txpreset = 4;
                }
            }
        }

        bdk_qlm_clock_t clk = (pem) ? clk2 : qlm0_clk;

        /* Check for width of 0 so we don't erroneous script with nothing in it */
        /* Which causes a problem during reboot */
        if ((width0 == 0) && (width2 == 0))
        {
            printf ("Error, Width is zero\n");
            return -1;
        }

        BDK_TRACE(QLM, "EP config PEM%d, QLM%d, width %d, freq %d, tx preset %d, clk %d\n",
            pem, qlm, width, freq, txpreset, clk);

        /* Check the GPIO strap for EP mode */
        int strap = (pem == 2) ? BDK_GPIO_STRAP_PIN_E_PCIE2_EP_MODE : BDK_GPIO_STRAP_PIN_E_PCIE0_EP_MODE;
        int jump_handle = bdk_scr_add_cmp_jump(bustype_BDK_GPIO_STRAP, 0,
            sizeof(bdk_gpio_strap_t), BDK_GPIO_STRAP, 1ull << strap, 1ull << strap,
            BDK_SCR_CMP_TYPE_E_NE, 0);
        if (jump_handle < 0)
            return -1;

        /* Skip init if PEM is already on. Likely after a soft reset */
        int jump_handle_pem = bdk_scr_add_cmp_jump(bustype_BDK_PEMX_ON(pem), pem,
            sizeof(bdk_pemx_on_t), BDK_PEMX_ON(pem), 1, 0,
            BDK_SCR_CMP_TYPE_E_NE, 0);
        if (jump_handle_pem < 0)
            return -1;

        /* Setup QLM reference clock */
        int clk_term = bdk_config_get_int(BDK_CONFIG_QLM_CLK_TERM, BDK_NODE_0, qlm);
        int cclksel = 0;

        /* Errata 36827: select local clock first to get an initial lock.
           This is so that we at least have a center spread clock reference.
           This has to happen early during initialization */
        int save_cclksel = 0;
        switch (clk)
        {
            case BDK_QLM_CLK_COMMON_0:
                cclksel = 0;
                save_cclksel = 0;
                break;
            case BDK_QLM_CLK_COMMON_1:
                save_cclksel = 1;
                /* This is a modification to use the common clock 0 local
                   reference clock, and then switch to common clock 1 at end
                   of initialization */
                cclksel = 0;
                break;
            case BDK_QLM_CLK_COMMON_2:
                cclksel = 2;
                save_cclksel = 2;
                break;
            case BDK_QLM_CLK_EXTERNAL:
            case BDK_QLM_CLK_LAST:
                cclksel = 3;
                save_cclksel = 3;
                break;
        }

        /* Setup each QLM */
        int num_qlms = (width < 4) ? 1 : width / 4;

        for (int i = 0; i < num_qlms ; i++)
        {
            SCR_ADD_WRITE(BDK_GSERNX_COMMON_REFCLK_BCFG(qlm + i),
                c.s.hcsl = (clk_term == 3);
                c.s.oct = (clk_term != 0);
                c.s.pwdn = 0; /* Always power on */
                c.s.cclksel = cclksel);

            BDK_TRACE(PCIE, "Setup PEM%d/QLM%d Speed=%d TxPreset=%d\n", pem, qlm + i, freq, txpreset);
            if (scr_setup_qlm(pem, qlm+i, width, freq, txpreset))
                return -1;
        }
        BDK_TRACE(PCIE, "Setup PEM %d \n", pem);
        SCR_ADD_WRITE(BDK_PEMX_CFG(pem),
            c.cn9.pipe_grp_ptr = ((pem == 0) || (pem2qlm == 3)) ? 0 : 2;
            c.cn9.pipe = ((pem == 0) || (pem2qlm == 3)) ? 0 : 2;
            c.cn9.lanes = (width <= 2) ? 0 :
            (width == 4) ? 1 :
            (width == 8) ? 2 :
            3);

        if (scr_setup_pem(pem, width, freq))
            return -1;

        BDK_TRACE(PCIE, "Setup PCIEEP %d \n", pem);
        if (scr_setup_pcieep(pem, width, freq))
            return -1;

        /* Initiate AUTOPLAY */
        SCR_ADD_WRITE(BDK_PEMX_CTL_STATUS(pem),
            c.cn9.auto_mode = 1;
            c.cn9.play = 1;
            c.cn9.ccrs = 1;
            c.cn9.clk_req_n = 1;
            c.cn9.rdy_entr_l23 = 1);

        /* Errata 36827: select local clock first to get an initial lock
            Restore the original clock selection request */
        if (save_cclksel != cclksel)
        {
            BDK_TRACE(PCIE, "PEM%d Revert Clock Selection(clk)=%d Set RefClkConfig=%d\n", pem, clk, save_cclksel);

            for (int i = 0; i < num_qlms ; i++)
            {
                SCR_ADD_WRITE(BDK_GSERNX_COMMON_REFCLK_BCFG(qlm + i),
                    c.s.hcsl = (clk_term == 3);
                    c.s.oct = (clk_term != 0);
                    c.s.pwdn = 0; /* Always power on */
                    c.s.cclksel = save_cclksel);
            }
        }

        if (bdk_scr_update_jump(jump_handle, scr_size))
            return -1;
        if (bdk_scr_update_jump(jump_handle_pem, scr_size))
            return -1;
    }

    if (bdk_scr_add_exit())
        return -1;

    return 0;
}
