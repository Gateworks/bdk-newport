/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for configuring DRAM.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup dram DRAM related functions
 * @{
 */

/**
 * Structure used for CN9XXX to map a LMC controller to the correct location on
 * the chip.
 */
typedef struct
{
    int node;   /* The node for the DRAM controller */
    int lmc;    /* The DRAM controller number */
    int mcc;    /* The MCC index for the DRAM controller */
    int lmcoe;  /* The MCC LMCOE index for the controller */
} bdk_dram_lmc_map_t;

/**
 * Given a node and LMC, return a map to where it is located on the chip. Needed
 * for CN9XXX parts to determine which MCC to use.
 *
 * @param node   Node for LMC
 * @param lmc    LMC to lookup
 *
 * @return LMC and MCC information
 */
extern bdk_dram_lmc_map_t bdk_dram_get_lmc_map(bdk_node_t node, int lmc);

/**
 * CALL directly from LUA DDR Menu item
 *
 * Lookup a DRAM configuration by name and initialize dram with it
 *
 * @param node   Node to configure
 * @param ddr_clock_override
 *               If non zero, override the DRAM frequency specified in the config with
 *               this value
 *
 * @return Amount of DRAM in MB, or negative on failure
 */
extern int bdk_dram_config(bdk_node_t node, int ddr_clock_override);

/**
 * Do DRAM configuration tuning
 *
 * @param node   Node to tune
 *
 * @return Success or Fail
 */
extern int bdk_dram_tune(int node);

/**
 * Do DRAM Margin all tests
 *
 * @param node   Node to tune
 *
 * @return None
 */
extern void bdk_dram_margin(int node);

/**
 * Get the amount of DRAM configured for a node. This is read from the LMC
 * controller after DRAM is setup.
 *
 * @param node   Node to query
 *
 * @return Size in megabytes
 */
extern uint64_t bdk_dram_get_size_mbytes(int node);

/**
 * Return the string of info about the current node's DRAM configuration.
 *
 * @param node   node to retrieve
 *
 * @return String or NULL
 */
extern const char* bdk_dram_get_info_string(int node);

/**
 * Return the highest address initialized by the BDK when running out of
 * cache. The space below this address may contain valid date before DRAM
 * is setup. Space at and after this address is unused before DRAM, and must
 * be zeroed before use.
 *
 * @return Size of the BDK cached area in bytes
 */
extern uint64_t bdk_dram_get_top_of_cache(void);

/**
 * Return the highest address currently used by the BDK. This address will
 * be about 4MB above the top of the BDK to make sure small growths between the
 * call and its use don't cause corruption. Any call to memory allocation can
 * change this value.
 *
 * @return Size of the BDK in bytes
 */
extern uint64_t bdk_dram_get_top_of_bdk(void);

/**
 * Return true if DRAM has been configured
 *
 * @return Boolean
 */
extern int __bdk_is_dram_enabled(bdk_node_t node);

extern int __bdk_dram_get_num_lmc(bdk_node_t node);
extern int __bdk_dram_get_lmc_mask(bdk_node_t node);
extern int __bdk_dram_is_lmc_in_dreset(bdk_node_t node, int lmc);
extern int __bdk_dram_is_rdimm(bdk_node_t node, int lmc);
extern uint32_t __bdk_dram_get_row_mask(bdk_node_t node, int lmc);
extern uint32_t __bdk_dram_get_col_mask(bdk_node_t node, int lmc);
extern int __bdk_dram_get_num_bank_bits(bdk_node_t node, int lmc);

/** @} */
