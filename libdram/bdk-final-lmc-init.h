/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern void
process_custom_dll_offsets(bdk_node_t node,  int ddr_interface_num,
                           const char *enable_str, const int8_t *offsets,
                           const char *byte_str, int mode);


extern void
Perform_DLL_Encoding_and_WR_Deskew(bdk_node_t node,  int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides,
                                   const ddr_custom_config_t *custom_lmc_config);

extern void Perform_Deskew_Unlock(bdk_node_t node, int ddr_interface_num,
                                  int unlock_envvar,
                                  dram_init_data_t *init_data,
                                  dram_overrides_t *overrides);

extern void Perform_Final_LMC_Init(bdk_node_t node, int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides);

extern void Clear_LMC_ECC_Errors(bdk_node_t node, int ddr_interface_num);

