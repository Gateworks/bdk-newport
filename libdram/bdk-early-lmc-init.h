/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern int
Perform_LMC_RESET_Init(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data);

extern void
Perform_Early_LMC_Init(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides);

extern void
Finish_Early_LMC_Init(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides);

extern void
Bring_Up_DRAM_for_Training(bdk_node_t node, int ddr_interface_num,
                           int rank_mask, dram_init_data_t *init_data);

