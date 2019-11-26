/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <ctype.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "dram-internal.h"

/**
 * Read the entire contents of a DIMM SPD and store it in the device tree. The
 * current DRAM config is also updated, so future SPD accesses used the cached
 * copy.
 *
 * @param node   Node the DRAM config is for
 * @param cfg    Current DRAM config. Updated with SPD data
 * @param lmc    LMC to read DIMM for
 * @param dimm   DIMM slot for SPD to read
 *
 * @return Zero on success, negative on failure
 */
int read_entire_spd(bdk_node_t node, dram_config_t *cfg, int lmc, int dimm)
{
    /* If pointer to data is provided, use it, otherwise read from SPD over twsi */
    if (cfg->config[lmc].dimm_config_table[dimm].spd_ptr)
        return 0;
    if (!cfg->config[lmc].dimm_config_table[dimm].spd_addr)
        return -1;

    /* Figure out how to access the SPD */
    int spd_addr = cfg->config[lmc].dimm_config_table[dimm].spd_addr;
    int bus = spd_addr >> 12;
    int address = spd_addr & 0x7f;

    bdk_device_t *twsi_device = bdk_device_lookup(node, BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), bus);

    /* Figure out the size we will read */
    int64_t dev_type = bdk_device_twsi_read_ia(twsi_device, address, DDR4_SPD_KEY_BYTE_DEVICE_TYPE, 1, 1);
    if (dev_type < 0)
    {
        cfg->config[lmc].dimm_config_table[dimm].spd_addr = 0;
        return -1; /* No DIMM */
    }
    int spd_size = (dev_type == 0x0c) ? 512 : 256;

    /* Allocate storage */
    uint32_t *spd_buf = malloc(spd_size);
    if (!spd_buf)
        return -1;
    uint32_t *ptr = spd_buf;

    for (int bank = 0; bank < (spd_size >> 8); bank++)
    {
        /* this should only happen for DDR4, which has a second bank of 256 bytes */
        if (bank)
            bdk_device_twsi_write_ia(twsi_device, 0x36 | bank, 0, 2, 1, 0);
        int bank_size = 256;
        for (int i = 0; i < bank_size; i += 4)
        {
            int64_t data = bdk_device_twsi_read_ia(twsi_device, address, i, 4, 1);
            if (data < 0)
            {
                free(spd_buf);
                bdk_error("Failed to read SPD data at 0x%x\n", i + (bank << 8));
                /* Restore the bank to zero */
                if (bank)
                    bdk_device_twsi_write_ia(twsi_device, 0x36 | 0, 0, 2, 1, 0);
                return -1;
            }
            else
                *ptr++ = bdk_be32_to_cpu(data);
        }
        /* Restore the bank to zero */
        if (bank)
            bdk_device_twsi_write_ia(twsi_device, 0x36 | 0, 0, 2, 1, 0);
    }

    /* Store the SPD in the device tree */
    bdk_config_set_blob(spd_size, spd_buf, BDK_CONFIG_DDR_SPD_DATA, dimm, lmc, node);
    cfg->config[lmc].dimm_config_table[dimm].spd_ptr = (void*)spd_buf;

    return 0;
}

/* Read an DIMM SPD value, either using TWSI to read it from the DIMM, or
 * from a provided array.
 */
int read_spd(bdk_node_t node, const dimm_config_t *dimm_config, int spd_field)
{
    /* The init code calls read_entire_spd(), so we should always
       have a cached copy */
    if (!dimm_config->spd_ptr)
        bdk_fatal("DRAM: SPD not already loaded during read_spd() call\n");
    return dimm_config->spd_ptr[spd_field];
}

static uint16_t ddr_crc16(const uint8_t *ptr, int count)
{
    /* From DDR4 SPD specification */
    int crc, i;
    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int)*ptr++ << 8;
        for (i = 0; i < 8; ++i)
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
    }
    return crc & 0xFFFF;
}

static int validate_spd_checksum_ddr(const uint8_t *spd_data, int twsi_addr, int silent)
{
    int crc_bytes = 126;
    uint16_t crc_comp;
    int ret = 1;
    /* Check byte 0 to see how many bytes checksum is over */
    if (spd_data[0] & 0x80)
        crc_bytes = 117;

    crc_comp = ddr_crc16(spd_data, crc_bytes);

    if (spd_data[DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_LOWER_NIBBLE] != (crc_comp & 0xff) ||
        spd_data[DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_UPPER_NIBBLE] != (crc_comp >> 8))
    {
        if (!silent) {
            printf("DDR SPD CRC error, spd addr: 0x%x, calculated crc: 0x%04x, read crc: 0x%02x%02x\n",
		   twsi_addr, crc_comp,
		   spd_data[DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_UPPER_NIBBLE],
		   spd_data[DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_LOWER_NIBBLE]);
	}
        ret = 0;
    }
    return ret;
}

static int validate_spd_checksum(const uint8_t *spd_data, int twsi_addr, int silent)
{
    int rv;

    debug_print("Validating DIMM at address 0x%x\n", twsi_addr);

    if (!twsi_addr) return 1; /* return OK if we are not doing real DIMMs */

    /* Look up module type to determine if  DDR4 */
    rv = spd_data[2];

    if (rv == 0xC) /* this is DDR4, do same */
        return validate_spd_checksum_ddr(spd_data, twsi_addr, silent);

    if (!silent)
        printf("Unrecognized DIMM type: 0x%x at spd address: 0x%x\n",
	       rv, twsi_addr);

    return 0;
}


int validate_dimm(bdk_node_t node, const dimm_config_t *dimm_config)
{
    int spd_addr;

    spd_addr = dimm_config->spd_addr;

    debug_print("Validating dimm spd addr: 0x%02x spd ptr: %x\n",
		spd_addr, dimm_config->spd_ptr);

    // if the slot is not possible
    if (!spd_addr && !dimm_config->spd_ptr)
        return -1;

    {
        int val0, val1;
        int ddr_type = get_ddr_type(node, dimm_config);

        switch (ddr_type)
        {
	    case DDR4_DRAM:              /* DDR4 */

		debug_print("Validating DDR%d DIMM\n", ((dimm_type >> 2) & 3) + 1);

#define DENSITY_BANKS DDR4_SPD_DENSITY_BANKS
#define ROW_COL_BITS  DDR4_SPD_ADDRESSING_ROW_COL_BITS

		val0 = read_spd(node, dimm_config, DENSITY_BANKS);
		val1 = read_spd(node, dimm_config, ROW_COL_BITS);
		if (val0 < 0 && val1 < 0) {
		    debug_print("Error reading SPD for DIMM\n");
		    return 0; /* Failed to read dimm */
		}
		if (val0 == 0xff && val1 == 0xff) {
		    ddr_print("Blank or unreadable SPD for DIMM\n");
		    return 0; /* Blank SPD or otherwise unreadable device */
		}

		/* Don't treat bad checksums as fatal. */
		validate_spd_checksum(dimm_config->spd_ptr, spd_addr, 0);
		break;

	    case 0x00:              /* Terminator detected. Fail silently. */
                return 0;

            default:
		debug_print("Unknown DIMM type 0x%x for DIMM @ 0x%x\n",
			     dimm_type, dimm_config->spd_addr);
                return 0;      /* Failed to read dimm */
        }
    }

    return 1;
}

int get_dimm_part_number(char *buffer, bdk_node_t node,
                         const dimm_config_t *dimm_config)
{
    int i;
    int c;
    int skipping = 1;
    int strlen   = 0;

#define PART_LIMIT  19
#define PART_NUMBER DDR4_SPD_MODULE_PART_NUMBER

    for (i = 0; i < PART_LIMIT; ++i) {

	c = (read_spd(node, dimm_config, PART_NUMBER + i) & 0xff);
	if (c == 0) // any null, we are done
	    break;

	/* Skip leading spaces. */
	if (skipping) {
	    if (isspace(c))
		continue;
	    else
		skipping = 0;
	}

	/* Put non-null non-leading-space-skipped char into buffer */
	buffer[strlen] = c;
	++strlen;
    }

    if (strlen > 0) {
	i = strlen - 1; // last char put into buf
	while (i >= 0 && isspace((int)buffer[i])) { // still in buf and a space
	    --i;
	    --strlen;
	}
    }
    buffer[strlen] = 0;       /* Insure that the string is terminated */

    return strlen;
}

uint32_t get_dimm_serial_number(bdk_node_t node, const dimm_config_t *dimm_config)
{
    uint32_t serial_number = 0;

#define SERIAL_NUMBER DDR4_SPD_MODULE_SERIAL_NUMBER

    for (int i = 0, j = 24; i < 4; ++i, j -= 8) {
        serial_number |= ((read_spd(node, dimm_config, SERIAL_NUMBER + i) & 0xff) << j);
    }

    return serial_number;
}

static uint32_t get_dimm_checksum(bdk_node_t node, const dimm_config_t *dimm_config)
{
    uint32_t spd_chksum;

#define LOWER_NIBBLE DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_LOWER_NIBBLE
#define UPPER_NIBBLE DDR4_SPD_CYCLICAL_REDUNDANCY_CODE_UPPER_NIBBLE

    spd_chksum  =   0xff & read_spd(node, dimm_config, LOWER_NIBBLE);
    spd_chksum |= ((0xff & read_spd(node, dimm_config, UPPER_NIBBLE)) << 8);

    return spd_chksum;
}

static
void report_common_dimm(bdk_node_t node, const dimm_config_t *dimm_config, int dimm,
			const char **dimm_types, char *volt_str,
                        int ddr_interface_num, int num_ranks, int dram_width,
                        int dimm_size_mb, int spd_package)
{
    int spd_ecc;
    unsigned spd_module_type;
    uint32_t serial_number;
    char part_number[21]; /* 20 bytes plus string terminator is big enough for either */
    char *sn_str;

    spd_module_type = get_dimm_module_type(node, dimm_config);
    spd_ecc = get_dimm_ecc(node, dimm_config);

    (void) get_dimm_part_number(part_number, node, dimm_config);

    serial_number = get_dimm_serial_number(node, dimm_config);
    if ((serial_number != 0) && (serial_number != 0xffffffff)) {
        sn_str = "s/n";
    } else {
        serial_number = get_dimm_checksum(node, dimm_config);
        sn_str = "chksum";
    }

    // FIXME: add output of DIMM rank/width, as in: 2Rx4, 1Rx8, etc
    printf("N%d.LMC%d.DIMM%d: %d MB, DDR4 %s %s %s, p/n: %s, %s: %u, %s\n",
           node, ddr_interface_num, dimm, dimm_size_mb,
           dimm_types[spd_module_type],
           printable_rank_spec(num_ranks, dram_width, spd_package),
           (spd_ecc ? "ECC" : "non-ECC"), part_number,
           sn_str, serial_number, volt_str);
}

const char *ddr4_dimm_types[16] = {
    /* 0000 */ "Extended",
    /* 0001 */ "RDIMM",
    /* 0010 */ "UDIMM",
    /* 0011 */ "SO-DIMM",
    /* 0100 */ "LRDIMM",
    /* 0101 */ "Mini-RDIMM",
    /* 0110 */ "Mini-UDIMM",
    /* 0111 */ "Reserved",
    /* 1000 */ "72b-SO-RDIMM",
    /* 1001 */ "72b-SO-UDIMM",
    /* 1010 */ "Reserved",
    /* 1011 */ "Reserved",
    /* 1100 */ "16b-SO-DIMM",
    /* 1101 */ "32b-SO-DIMM",
    /* 1110 */ "Reserved",
    /* 1111 */ "Reserved"
};

static
void report_ddr4_dimm(bdk_node_t node, const dimm_config_t *dimm_config,
                      int dimm, int ddr_interface_num, int num_ranks,
                      int dram_width, int dimm_size_mb)
{
    int spd_voltage, spd_package;
    char *volt_str;

    spd_voltage = read_spd(node, dimm_config, DDR4_SPD_MODULE_NOMINAL_VOLTAGE);
    if ((spd_voltage == 0x01) || (spd_voltage & 0x02))
	volt_str = "1.2V";
    if ((spd_voltage == 0x04) || (spd_voltage & 0x08))
	volt_str = "TBD1 V";
    if ((spd_voltage == 0x10) || (spd_voltage & 0x20))
	volt_str = "TBD2 V";

    spd_package = read_spd(node, dimm_config, DDR4_SPD_PACKAGE_TYPE);
    report_common_dimm(node, dimm_config, dimm, ddr4_dimm_types,
                       volt_str, ddr_interface_num,
                       num_ranks, dram_width, dimm_size_mb,
                       spd_package);
}

void report_dimm(bdk_node_t node, const dimm_config_t *dimm_config,
                 int dimm, int ddr_interface_num, int num_ranks,
                 int dram_width, int dimm_size_mb)
{
    report_ddr4_dimm(node, dimm_config, dimm, ddr_interface_num,
                     num_ranks, dram_width, dimm_size_mb);
}

static int
get_ddr4_spd_speed(bdk_node_t node, const dimm_config_t *dimm_config)
{
    int spdMTB = 125;
    int spdFTB = 1;

    int tCKAVGmin
	  = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MINIMUM_CYCLE_TIME_TCKAVGMIN)
	  + spdFTB * (signed char) read_spd(node, dimm_config, DDR4_SPD_MIN_CYCLE_TIME_FINE_TCKAVGMIN);

    return pretty_psecs_to_mts(tCKAVGmin);
}

static int
speed_bin_down(int speed)
{
    int ret = -1;
    if (speed == 3200)      ret = 2933;
    else if (speed == 2933) ret = 2666;
    else if (speed == 2666) ret = 2400;
    else if (speed == 2400) ret = 2133;
    else if (speed == 2133) ret = 1866;
    else if (speed == 1866) ret = 1600;
    else if (speed == 1600) ret = 1333;
    else if (speed == 1333) ret = 1066;
    else if (speed == 1066) ret = 800;
    return ret;
}

int
dram_get_default_spd_speed(bdk_node_t node, const ddr_configuration_t *ddr_config)
{
    int lmc, dimm;
    int speed, ret_speed = 0;
    int dimm_speed[8] = { 0, }, dimm_count = 0;
    int dimms_per_lmc = 0;
    int cpu_mts = (bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000) * 2;
    int new_speed;
    int num_lmcs = __bdk_dram_get_num_lmc(node);

    for (lmc = 0; lmc < num_lmcs; lmc++) {
        for (dimm = 0; dimm < DDR_CFG_T_MAX_DIMMS; dimm++) {
            const dimm_config_t *dimm_config = &ddr_config[lmc].dimm_config_table[dimm];
            if (/*dimm_config->spd_addr ||*/ dimm_config->spd_ptr) {
                speed = get_ddr4_spd_speed(node, dimm_config);
                //printf("N%d.LMC%d.DIMM%d: SPD speed %d\n", node, lmc, dimm, speed);
                dimm_speed[dimm_count] = speed;
                dimm_count++;
                if (lmc == 0)
                    dimms_per_lmc++;
            }
        }
    }

    // all DIMMs must be same speed
    speed = dimm_speed[0];
    for (dimm = 1; dimm < dimm_count; dimm++) {
        if (dimm_speed[dimm] != speed) {
            ret_speed = -1;
            goto finish_up;
        }
    }

    // if 2400 or greater, use 2133, on CN8XXX
    if (bdk_is_model(OCTEONTX_CN8XXX) && (speed >= 2400))
        speed = 2133;

    // if greater than 3200, use 3200 on CN9XXX
    if (bdk_is_model(OCTEONTX_CN9XXX) && (speed > 3200))
        speed = 3200;

    // FIXME: limit top speed on CN9XXX temporarily...
    if (bdk_is_model(OCTEONTX_CN9XXX) && (speed > 2400))
        speed = 2400;

    // use next speed down if 2DPC...
    if (dimms_per_lmc > 1) {
        new_speed = speed_bin_down(speed);
        if (new_speed < 0) {
            printf("N%d.LMC%d.DIMM%d: WARNING: unable to downgrade %d speed for 2DPC\n",
                   node, lmc, dimm, speed);
            goto return_speed;
        }
        speed = new_speed;
    }

    // make sure the DDR speed is slower than the CPU on CN8XXX...
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        int print_warning = 0;

        new_speed = speed; // start where we are...
        while ((new_speed > 0) && (cpu_mts < new_speed)) { // FIXME? allow same speed?
            print_warning = 1;
            new_speed = speed_bin_down(new_speed);
        }
        if (new_speed < 0) {
            printf("N%d: WARNING: unable to downgrade %d speed below CPU\n",
                   node, speed);
            ret_speed = -1;
            goto finish_up;
        }
        if (print_warning) {
            printf("\nN%d: WARNING: AUTO DDR speed (%ld) greater than CPU speed (%ld); using %ld \n\n",
                   node, mts_to_hertz(speed), mts_to_hertz(cpu_mts), mts_to_hertz(new_speed));
            speed = new_speed;
        }
    }

    // Update the in-memory config to match the automatically calculated speed
    bdk_config_set_int(speed, BDK_CONFIG_DDR_SPEED, node);

    // Finally, do filtering for CN8XXX jittery PLL
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        if (speed == 2133)
            speed = 2100;
        else if (speed == 1866)
            speed = 1880;
    }

return_speed:
    // OK, return what we have, or error...
    ret_speed = (speed > 0) ? (int)mts_to_hertz(speed) : -1;

 finish_up:
    //printf("N%d: Returning default SPD speed %d\n", node, ret_speed);
    return ret_speed;
}
