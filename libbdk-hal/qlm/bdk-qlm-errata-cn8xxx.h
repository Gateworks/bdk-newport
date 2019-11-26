/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Errata GSER-25992 - RX EQ Default Settings Update<p>
 * For all GSER and all lanes when not PCIe EP:
 *     set GSER()_LANE()_RX_CFG_4[CFG_RX_ERRDET_CTRL<13:8>] = 13 (decimal)
 *     set GSER()_LANE()_RX_CTLE_CTRL[PCS_SDS_RX_CTLE_BIAS_CTRL] = 3
 * Applied when SERDES are configured for 8G and 10G.<p>
 * Applies to:
 *     CN88XX pass 1.x
 * Fixed in hardware:
 *     CN88XX pass 2.x
 *     CN81XX
 *     CN83XX
 *
 * @param node     Node to apply errata fix for
 * @param qlm      QLM to apply errata fix to
 * @param baud_mhz QLM speed in Mhz
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_errata_gser_25992(bdk_node_t node, int qlm, int baud_mhz);

/**
 * (GSER-26150) 10G PHY PLL Temperature Failure
 *
 * 10 Gb temperature excursions can cause lock failure. Change
 * the calibration point of the VCO at start up to shift some
 * available range of the VCO from -deltaT direction to the
 * +deltaT ramp direction allowing a greater range of VCO
 * temperatures before experiencing the failure.
 *
 * Applies to:
 *     CN88XX pass 1.x
 * Fix in hardware:
 *     CN88XX pass 2.x
 *     CN81XX
 *     CN83XX
 *
 * Only applies to QLMs running 8G and 10G
 *
 * @param node   Node to apply errata to
 * @param qlm    QLM to apply errata fix to
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_errata_gser_26150(bdk_node_t node, int qlm, int baud_mhz);

/**
 * Errata (GSER-26636) 10G-KR/40G-KR - Inverted Tx Coefficient Direction Change
 * Applied to all 10G standards (required for KR) but also applied to other
 * standards in case software training is used.
 * Applies to:
 *     CN88XX pass 1.x
 * Fixed in hardware:
 *     CN88XX pass 2.x
 *     CN81XX
 *     CN83XX
 *
 * @param node     Node to apply errata fix for
 * @param qlm      QLM to apply errata fix to
 * @param baud_mhz QLM speed in Mhz
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_errata_gser_26636(bdk_node_t node, int qlm, int baud_mhz);

/**
 * (GSER-27140) SERDES has temperature drift sensitivity in the RX EQ<p>
 * SERDES temperature drift sensitivity in receiver. Issues have
 * been found with the Bit Error Rate (BER) reliability of
 * 10GBASE-KR links over the commercial temperature range (0 to 100C),
 * especially when subjected to rapid thermal ramp stress testing.
 * (See HRM for corresponding case temperature requirements for each speed grade.)<p>
 * Applies to:
 *     CN88XX pass 1.x
 *     CN88XX pass 2.x
 *     CN83XX pass 1.x
 *     CN81XX pass 1.x
 * Fixed in hardware:
 *     TBD<p>
 * Only applies to QLMs running 10G
 *
 * @param node     Note to apply errata fix to
 * @param qlm      QLM to apply errata fix to
 * @param baud_mhz QLM baud rate in Mhz
 * @param channel_loss
 *                 Insertion loss at Nyquist rate (e.g. 5.125Ghz for XFI/XLAUI) in dB
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_errata_gser_27140(bdk_node_t node, int qlm, int baud_mhz, int channel_loss);

/**
 * Errata GSER-27882 -GSER 10GBASE-KR Transmit Equalizer
 * Training may not update PHY Tx Taps. This function is not static
 * so we can share it with BGX KR
 * Applies to:
 *     CN88XX pass 1.x, 2.0, 2.1
 * Fixed in hardware:
 *     CN88XX pass 2.2 and higher
 *     CN81XX
 *     CN83XX
 *
 * @param node   Node to apply errata fix for
 * @param qlm    QLM to apply errata fix to
 * @param lane
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_errata_gser_27882(bdk_node_t node, int qlm, int lane);

