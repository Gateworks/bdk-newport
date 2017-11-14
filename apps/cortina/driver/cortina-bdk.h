/***********************license start***********************************
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
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#ifndef __CORTINA_BDK_H__
#define __CORTINA_BDK_H__

#include <bdk.h>

/**
 * @file
 *
 * Cortina BDK driver api.
 *
 */

/* Make a CS api 'slice' from MDIO bus, phy and dev)  These are decoded
 * cs_rtos.c by the Thunder specific read/write functions. */
#define MK_SLICE(node, bus, phy, chn) (((node & 0xff) << 28) | ((bus & 0xff) << 24) | ((phy & 0xffff) << 8) | (chn & 0xff))

#define SLICE_TO_NODE(s) (((s) >> 28) & 0xF)
#define SLICE_TO_BUS(s)  (((s) >> 24) & 0xF)
#define SLICE_TO_PHY(s)  (((s) >> 8 ) & 0xFFFF)
#define SLICE_TO_DIE(s)  ( (s)        & 0x01)

void dump_modes(bdk_node_t node, int bus_id, int phy_id);

int bdk_cortina_get_fw_date(bdk_node_t node, int bus_id, int phy_id, int die_id,
                            uint16_t *rom_day_month, uint16_t *rom_year, uint16_t *rom_time);
int bdk_cortina_print_ts(bdk_node_t node, int bus_id, int phy_id, int die_id);
int bdk_cortina_update_eeprom(bdk_node_t node, int bus_id, int phy_id, int chn_id,
                              const char *file_name);

void bdk_cortina_show_phy_modes(bdk_node_t node, int bus_id, int phy_id);
int bdk_cortina_switch_optical_mode_line(bdk_node_t node, int bus_id, int phy_id, int chn_id);
int bdk_cortina_switch_optical_mode_host(bdk_node_t node, int bus_id, int phy_id, int chn_id);
int bdk_cortina_switch_copper_mode_line(bdk_node_t node, int bus_id, int phy_id, int chn_id);
int bdk_cortina_switch_copper_mode_host(bdk_node_t node, int bus_id, int phy_id, int chn_id);

#endif
