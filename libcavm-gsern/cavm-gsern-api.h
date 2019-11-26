#ifndef _CAVM_GSERN_API_H_
#define _CAVM_GSERN_API_H_
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

enum cavm_gsern_mode
{
    CAVM_GSERN_MODE_DISABLED,
    CAVM_GSERN_MODE_PCIE_RC,
    CAVM_GSERN_MODE_PCIE_EP,
    CAVM_GSERN_MODE_CGX,
};

enum cavm_gsern_flags
{
    CAVM_GSERN_FLAGS_NONE = 0x0,
    CAVM_GSERN_FLAGS_DUAL = 0x1,
    CAVM_GSERN_FLAGS_QUAD = 0x2
};

/**
 * Setup the initial mode of a GSERN serdes. This is called for the initial mode
 * set, not mode change due to auto negotiation.
 *
 * @param node     Node to setup
 * @param qlm      DLM/QLM to setup
 * @param qlm_lane Lane in QLM to setup. Only used in networking modes
 * @param mode     Mode to setup
 * @param is_first Set if this is the first DLM/QLM in a sequence used for wide
 *                 protocols. For example, PCIe x16 would set this on QLM0 but not
 *                 on QLM1-3.
 * @param baud_mhz Baud rate in MegaHertz
 * @param flags    Mode flags for optional features
 *
 * @return Zero on success, negative on failure
 */
extern int cavm_gsern_set_mode(int node, int qlm, int qlm_lane, enum cavm_gsern_mode mode, bool is_first, int baud_mhz, enum cavm_gsern_flags flags);

/**
 * Capture an eye diagram for the given QLM lane. The output data is written
 * to "eye".
 *
 * @param node      Node to use in numa setup
 * @param qlm       QLM to use
 * @param qlm_lane  Which lane
 * @param show_data Set to non-zero to have the eye capture dump the raw eye data as
 *                  it is captured
 * @param eye       Output eye data
 *
 * @return Zero on success, negative on failure
 */
extern int cavm_gsern_eye_capture(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data);

#endif /* _CAVM_GSERN_API_H_ */
