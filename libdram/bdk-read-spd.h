/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern int
Setup_DRAM_Config(bdk_node_t node, int ddr_interface_num,
                  dram_init_data_t *init_data,
                  dram_overrides_t *overrides);

extern impedence_values_t ddr4_impedence_values;
