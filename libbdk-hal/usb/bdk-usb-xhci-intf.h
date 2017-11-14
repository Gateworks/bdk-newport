#ifndef __BDK_USB_EXTAPI_H__
#define __BDK_USB_EXTAPI_H__
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

/**
 * @file
*  External interface to usb-xhci support to bdk
**/

//
// This header must not rely on xhci-private data types
//

/**
 * Convert USB speed encoding to human-readable token
 *
 * @param speed Encoded speed
 *
 * @return Pointer to a speed token one of SS:HS:LS:FS:??
 **/
const char* __bdk_usb_speed2token(const int speed);

/**
 * Initialize root hub USB XHCI root hub instance on a thunder node
 * Root hub has to be initialized prior to that
 *
 * @param node cavium node number
 * @param usb_port xhci instance on a node
 *
 * @return Zero	success
 * @return Non-Zero error
 **/
extern int bdk_usb_HCInit(bdk_node_t node, int usb_port) BDK_WEAK;

/**
 * Manually trigger root Hub enumeration pass
 *
 * @param node       Node to init
 * @param usb_port   Port to intialize
 * @param checklocks Check/acquire for bus lock
 *
 * @return Zero on success, negative on error
 */
extern int bdk_usb_HCPoll(bdk_node_t node, int usb_port, int checklocks) BDK_WEAK;

/**
 * Print current USB topology discovered by enumeration
 *
 * @param node       Node
 * @param usb_port   Physical Port
 *
 * @return Zero on success, negative on error
 */
extern int bdk_usb_HCList(bdk_node_t node, int usb_port) BDK_WEAK;

/**
 * Query or toggle polling for Root Hub Enumeration and async interrupt
 * transfers for XHCI.
 *
 * @param node cavium node number
 * @param usb_port xhci instance on a node
 * @param action DO_QUERY: query DO_TOGGLE: toggle state
 *
 * @return Zero	polling is off
 * @return Positive polling is on
 * @return Negative error
 **/
typedef enum {
    DO_QUERY,
    DO_TOGGLE
} bdk_usb_toggleReq_t;

extern int bdk_usb_togglePoll(bdk_node_t node, int usb_port, const bdk_usb_toggleReq_t action) BDK_WEAK;
#endif
