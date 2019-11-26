#ifndef _CAVM_GSERN_INIT_H_
#define _CAVM_GSERN_INIT_H_
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern int cavm_gsern_init_wait_for_sm_complete(bdk_node_t node, int qlm);
extern int cavm_gsern_init_wait_for_sm_ready(bdk_node_t node, int qlm, int qlm_lane);
extern int cavm_gsern_init_wait_for_rx_ready(bdk_node_t node, int qlm, int qlm_lane);
extern int cavm_gsern_init_wait_for_tx_ready(bdk_node_t node, int qlm, int qlm_lane);

extern int cavm_gsern_init_pcie(bdk_node_t node, int qlm, bool is_first_qlm, enum cavm_gsern_flags flags, enum gsern_lane_modes mode);
extern int cavm_gsern_init_network(bdk_node_t node, int qlm, int qlm_lane, enum cavm_gsern_flags flags, enum gsern_lane_modes mode);

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/* Some fields in GSERN must be based on the VDD supplied to VDDA_GSER. This
   global contains the BDK's guess as what the voltage currently is in
   millivolts */
extern int cavm_gsern_voltage;

#endif /* _CAVM_GSERN_INIT_H_ */
