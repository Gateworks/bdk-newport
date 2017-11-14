/** @file
  The XHCI controller driver.

Copyright (c) 2011 - 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-usbdrd.h"
#include "Xhci.h"
#include "XhciReg.h"
#include "UsbBus.h"
#include "UsbDesc.h"
#include "UsbHub.h"

//
// Template for Xhci's Usb2 Host Controller Protocol Instance.
//

/*
** External interfaces of Xhci.c
*/
EFI_USB2_HC_PROTOCOL gXhciUsb2HcTemplate = {
  XhcGetCapability,
  XhcReset,
  XhcGetState,
  XhcSetState,
  XhcControlTransfer,
  XhcBulkTransfer,
  XhcAsyncInterruptTransfer,
  XhcSyncInterruptTransfer,
  XhcIsochronousTransfer,
  XhcAsyncIsochronousTransfer,
  XhcGetRootHubPortStatus,
  XhcSetRootHubPortFeature,
  XhcClearRootHubPortFeature,
  0x3,
  0x0
};
/*
** Helper functions
*/


/**
  Set the XHCI host controller to run.

  @param  Xhc          The XHCI Instance.
  @param  Timeout      Time to wait before abort (in millisecond, ms).

  @return EFI_SUCCESS  The XHCI host controller is running.
  @return EFI_TIMEOUT  Failed to set the XHCI to run before Timeout.

**/
static EFI_STATUS
XhcRunHC (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Timeout
  )
{
  EFI_STATUS              Status;

  XhcSetOpRegBit (Xhc, XHC_USBCMD_OFFSET, XHC_USBCMD_RUN);
  Status = XhcWaitOpRegBit (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HALT, FALSE, Timeout);
  return Status;
}
/**
  Halt the XHCI host controller.

  @param  Xhc          The XHCI Instance.
  @param  Timeout      Time to wait before abort (in millisecond, ms).

  @return EFI_SUCCESS  The XHCI host controller is halt.
  @return EFI_TIMEOUT  Failed to halt the XHCI before Timeout.

**/
static EFI_STATUS
XhcHaltHC (
  IN USB_XHCI_INSTANCE   *Xhc,
  IN UINT32              Timeout
  )
{
  EFI_STATUS              Status;

  XhcClearOpRegBit (Xhc, XHC_USBCMD_OFFSET, XHC_USBCMD_RUN);
  Status = XhcWaitOpRegBit (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HALT, TRUE, Timeout);
  return Status;
}


/**
  Reset the XHCI host controller.

  @param  Xhc          The XHCI Instance.
  @param  Timeout      Time to wait before abort (in millisecond, ms).

  @retval EFI_SUCCESS  The XHCI host controller is reset.
  @return Others       Failed to reset the XHCI before Timeout.

**/
static EFI_STATUS
XhcResetHC (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Timeout
  )
{
  EFI_STATUS              Status;

  Status = EFI_SUCCESS;

  /* DEBUG ((EFI_D_INFO, "XhcResetHC!\n")); */
  //
  // Host can only be reset when it is halt. If not so, halt it
  //
  if (!XHC_REG_BIT_IS_SET (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HALT)) {
	  Status = XhcHaltHC (Xhc, Timeout);

    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "XhcResetHC! <<-- 1 status=%d\n", (int)Status));
        return Status;
    }
  }

  if ((Xhc->DebugCapSupOffset == 0xFFFFFFFF) || ((XhcReadExtCapReg (Xhc, Xhc->DebugCapSupOffset) & 0xFF) != XHC_CAP_USB_DEBUG) ||
      ((XhcReadExtCapReg (Xhc, Xhc->DebugCapSupOffset + XHC_DC_DCCTRL) & BIT0) == 0)) {
    XhcSetOpRegBit (Xhc, XHC_USBCMD_OFFSET, XHC_USBCMD_RESET);
    Status = XhcWaitOpRegBit (Xhc, XHC_USBCMD_OFFSET, XHC_USBCMD_RESET, FALSE, Timeout);
  }

  DEBUG ((EFI_D_INFO, "XhcResetHC! <<-- 2 status=%d\n", (int)Status));
  return Status;
}

/*
 * Create instance of xhci controller in memory and initialize read-only parameters
 * @param node       Node to init
 * @param usb_port   Port to intialize
 *
 * @return address of instance on success, NULL on failure
 */
xhci_t* createUsbXHci(bdk_node_t node, int usb_port)
{
    xhci_t *thisXHC;

    if (usb_port >= CAVIUM_MAX_USB_INSTANCES) return NULL;
    if (NULL == (thisXHC = malloc(sizeof(*thisXHC)))) {
        DEBUG((EFI_D_ERROR,"Could not allocate XHCI instance for node %d port %d\n", (unsigned) node , (unsigned) usb_port));
        return NULL;
    }
    bzero(thisXHC, sizeof (*thisXHC));
    // Setup for Register IO
#define USBH_DEVID ((BDK_PCC_PROD_E_GEN << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_USBH << 16))
#define USBDRD_DEVID ((BDK_PCC_PROD_E_GEN << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_USBDRD << 16))
    const bdk_device_t *dev;
    if (NULL != (dev = bdk_device_lookup(node, USBH_DEVID, usb_port)) ) {
        BDK_CSR_INIT(uctl_ctl,node,BDK_USBHX_UCTL_CTL(usb_port));
        if (0 == (uctl_ctl.s.h_clk_en & uctl_ctl.s.csclk_en) )  {
            printf("\nUSB port have not been initialized\n");
            goto err_exit;
        }
    } else if (NULL != (dev = bdk_device_lookup(node, USBDRD_DEVID, usb_port)) )  {
         BDK_CSR_INIT(uctl_ctl,node,BDK_USBDRDX_UCTL_CTL(usb_port));
         if (0 == (uctl_ctl.s.h_clk_en) ) {
             printf("\nUSB port have not been initialized\n");
             goto err_exit;
         }
         if ( 0 != uctl_ctl.s.drd_mode) {
             printf("\nController setup is for mode other then host\n");
             goto err_exit;
         }
    } else {
        bdk_warn("No suitable XHCI device found\n");
        goto err_exit;
    }
    thisXHC->bdk_dev = dev;

    thisXHC->node = node;
    thisXHC->usb_port = usb_port;
    // Read section offsets from config space of xhci controller
    thisXHC->DBOff = XhcReadCapReg (thisXHC, XHC_DBOFF_OFFSET); // DoorBell ofset
    thisXHC->RTSOff = XhcReadCapReg (thisXHC, XHC_RTSOFF_OFFSET); // Runtime space offset
    BDK_CSR_DEFINE(caplength, BDK_USBHX_UAHC_CAPLENGTH(0));
    caplength.u =  XhcReadCapReg (thisXHC,  XHC_CAPLENGTH_OFFSET);
    thisXHC->CapLength = caplength.s.caplength; // OpReg space offset

    thisXHC->hcsparams1.u = XhcReadCapReg (thisXHC, XHC_HCSPARAMS1_OFFSET);
    thisXHC->hcsparams2.u = XhcReadCapReg (thisXHC, XHC_HCSPARAMS2_OFFSET);
    thisXHC->hccparams.u = XhcReadCapReg (thisXHC, XHC_HCCPARAMS_OFFSET);
    BDK_CSR_DEFINE(pgsz, BDK_USBHX_UAHC_PAGESIZE(0));
    pgsz.u = XhcReadOpReg(thisXHC, XHC_PAGESIZE_OFFSET);
    thisXHC->ExtCapRegBase = ((typeof(thisXHC->ExtCapRegBase))thisXHC->hccparams.s.xecp) << 2;
    thisXHC->DebugCapSupOffset = XhcGetCapabilityAddr (thisXHC, XHC_CAP_USB_DEBUG);
#if 0
    printf("thisHC @%p\n",thisXHC);
    printf("hcsparams1:%08lx\n",(unsigned long) thisXHC->hcsparams1.u);
    printf("hcsparams2:%08lx\n",(unsigned long) thisXHC->hcsparams2.u);
    printf("hccparams:%08lx\n",(unsigned long) thisXHC->hccparams.u);
    printf("page size %d\nnode %d port %d\n", pgsz.u,thisXHC->node,thisXHC->usb_port);
    printf("64 bit capability %d Debug: %08x\n",thisXHC->hccparams.s.ac64, thisXHC->DebugCapSupOffset);

#endif
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
    if (0 == thisXHC->hccparams.s.csz) {
        bdk_warn("Support for 32 byte context size is compiled out\n"
                 "Please complain to software provider\n");
        goto err_exit;
    }
#endif
    if ( thisXHC->hcsparams1.s.maxslots > CAVIUM_XHCI_MAXSLOTS) {
        bdk_warn("XHCI hcsparams1.maxslots(%d) exceeds configured maximum(%d)\n"
                 "Please complain to software provider\n"
                 ,
                 thisXHC->hcsparams1.s.maxslots,  CAVIUM_XHCI_MAXSLOTS);
    }

    thisXHC->PageSize = 1 << (12 + HighBitSet(pgsz.s.pagesize));
    CopyMem (&thisXHC->Usb2Hc, &gXhciUsb2HcTemplate, sizeof (EFI_USB2_HC_PROTOCOL));
    InitializeListHead(&thisXHC->AsyncIntTransfers);

    return thisXHC;
err_exit:
    free(thisXHC);
    return NULL;
}

const USB_PORT_STATE_MAP mUsbPortStateMap[] = {
  {XHC_PORTSC_CCS,   USB_PORT_STAT_CONNECTION},
  {XHC_PORTSC_PED,   USB_PORT_STAT_ENABLE},
  {XHC_PORTSC_OCA,   USB_PORT_STAT_OVERCURRENT},
  {XHC_PORTSC_RESET, USB_PORT_STAT_RESET}
};

const USB_PORT_STATE_MAP  mUsbPortChangeMap[] = {
  {XHC_PORTSC_CSC, USB_PORT_STAT_C_CONNECTION},
  {XHC_PORTSC_PEC, USB_PORT_STAT_C_ENABLE},
  {XHC_PORTSC_OCC, USB_PORT_STAT_C_OVERCURRENT},
  {XHC_PORTSC_PRC, USB_PORT_STAT_C_RESET}
};

const USB_CLEAR_PORT_MAP  mUsbClearPortChangeMap[] = {
  {XHC_PORTSC_CSC, EfiUsbPortConnectChange},
  {XHC_PORTSC_PEC, EfiUsbPortEnableChange},
  {XHC_PORTSC_OCC, EfiUsbPortOverCurrentChange},
  {XHC_PORTSC_PRC, EfiUsbPortResetChange}
};
const USB_PORT_STATE_MAP  mUsbHubPortStateMap[] = {
  {XHC_HUB_PORTSC_CCS,   USB_PORT_STAT_CONNECTION},
  {XHC_HUB_PORTSC_PED,   USB_PORT_STAT_ENABLE},
  {XHC_HUB_PORTSC_OCA,   USB_PORT_STAT_OVERCURRENT},
  {XHC_HUB_PORTSC_RESET, USB_PORT_STAT_RESET}
};

const USB_PORT_STATE_MAP  mUsbHubPortChangeMap[] = {
  {XHC_HUB_PORTSC_CSC, USB_PORT_STAT_C_CONNECTION},
  {XHC_HUB_PORTSC_PEC, USB_PORT_STAT_C_ENABLE},
  {XHC_HUB_PORTSC_OCC, USB_PORT_STAT_C_OVERCURRENT},
  {XHC_HUB_PORTSC_PRC, USB_PORT_STAT_C_RESET}
};

const USB_CLEAR_PORT_MAP mUsbHubClearPortChangeMap[] = {
  {XHC_HUB_PORTSC_CSC, EfiUsbPortConnectChange},
  {XHC_HUB_PORTSC_PEC, EfiUsbPortEnableChange},
  {XHC_HUB_PORTSC_OCC, EfiUsbPortOverCurrentChange},
  {XHC_HUB_PORTSC_PRC, EfiUsbPortResetChange},
  {XHC_HUB_PORTSC_BHRC, Usb3PortBHPortResetChange}
};


/**
  Clears a feature for the specified root hub port.

  @param  This                  A pointer to the EFI_USB2_HC_PROTOCOL instance.
  @param  PortNumber            Specifies the root hub port whose feature is
                                requested to be cleared.
  @param  PortFeature           Indicates the feature selector associated with the
                                feature clear request.

  @retval EFI_SUCCESS           The feature specified by PortFeature was cleared
                                for the USB root hub port specified by PortNumber.
  @retval EFI_INVALID_PARAMETER PortNumber is invalid or PortFeature is invalid.
  @retval EFI_DEVICE_ERROR      Can't read register.

**/
EFI_STATUS
EFIAPI
XhcClearRootHubPortFeature (
  IN EFI_USB2_HC_PROTOCOL  *This,
  IN UINT8                 PortNumber,
  IN EFI_USB_PORT_FEATURE  PortFeature
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  UINT32                  Offset;
  UINT32                  State;
  EFI_STATUS              Status;
  /* EFI_TPL                 OldTpl; */

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc       = XHC_FROM_THIS (This);
  Status    = EFI_SUCCESS;

  if (PortNumber >= Xhc->hcsparams1.s.maxports) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  Offset = XHC_PORTSC_OFFSET + (0x10 * PortNumber);

  //
  // Mask off the port status change bits, these bits are
  // write clean bit
  //
  State  = XhcReadOpReg (Xhc, Offset);
  State &= ~ (BIT1 | BIT17 | BIT18 | BIT19 | BIT20 | BIT21 | BIT22 | BIT23);

  switch (PortFeature) {
  case EfiUsbPortEnable:
    //
    // Ports may only be enabled by the xHC. Software cannot enable a port by writing a '1' to this flag.
    // A port may be disabled by software writing a '1' to this flag.
    //
    State |= XHC_PORTSC_PED;
    State &= ~XHC_PORTSC_RESET;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortSuspend:
    State |= XHC_PORTSC_LWS;
    XhcWriteOpReg (Xhc, Offset, State);
    State &= ~XHC_PORTSC_PLS;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortReset:
    //
    // PORTSC_RESET BIT(4) bit is RW1S attribute, which means Write-1-to-set status:
    // Register bits indicate status when read, a clear bit may be set by
    // writing a '1'. Writing a '0' to RW1S bits has no effect.
    //
    break;

  case EfiUsbPortOwner:
    //
    // XHCI root hub port don't has the owner bit, ignore the operation
    //
    break;

  case EfiUsbPortConnectChange:
    //
    // Clear connect status change
    //
    State |= XHC_PORTSC_CSC;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortEnableChange:
    //
    // Clear enable status change
    //
    State |= XHC_PORTSC_PEC;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortOverCurrentChange:
    //
    // Clear PortOverCurrent change
    //
    State |= XHC_PORTSC_OCC;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortResetChange:
    //
    // Clear Port Reset change
    //
    State |= XHC_PORTSC_PRC;
    XhcWriteOpReg (Xhc, Offset, State);
    break;

  case EfiUsbPortPower:
  case EfiUsbPortSuspendChange:
    //
    // Not supported or not related operation
    //
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
    break;
  }

ON_EXIT:
  DEBUG ((EFI_D_INFO, "status %d\n", (int) Status));
  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}

/**
  Sets a feature for the specified root hub port.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  PortNumber            Root hub port to set.
  @param  PortFeature           Feature to set.

  @retval EFI_SUCCESS           The feature specified by PortFeature was set.
  @retval EFI_INVALID_PARAMETER PortNumber is invalid or PortFeature is invalid.
  @retval EFI_DEVICE_ERROR      Can't read register.

**/
EFI_STATUS
EFIAPI
XhcSetRootHubPortFeature (
  IN EFI_USB2_HC_PROTOCOL  *This,
  IN UINT8                 PortNumber,
  IN EFI_USB_PORT_FEATURE  PortFeature
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  UINT32                  Offset;
  UINT32                  State;
  UINT32                  TotalPort;
  EFI_STATUS              Status;
#if defined(notdef_cavium)
  EFI_TPL                 OldTpl;

  OldTpl = gBS->RaiseTPL (XHC_TPL);
#endif
  Xhc    = XHC_FROM_THIS (This);
  Status = EFI_SUCCESS;

  TotalPort = (Xhc->hcsparams1.s.maxports);

  if (PortNumber >= TotalPort) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }
  Offset = (UINT32) (XHC_PORTSC_OFFSET + (0x10 * PortNumber));
  State  = XhcReadOpReg (Xhc, Offset);

  //
  // Mask off the port status change bits, these bits are
  // write clean bit
  //
  State &= ~ (BIT1 | BIT17 | BIT18 | BIT19 | BIT20 | BIT21 | BIT22 | BIT23);

  switch (PortFeature) {
  case EfiUsbPortEnable:
    //
    // Ports may only be enabled by the xHC. Software cannot enable a port by writing a '1' to this flag.
    // A port may be disabled by software writing a '1' to this flag.
    //
    Status = EFI_SUCCESS;
    break;

  case EfiUsbPortSuspend:

    State |= XHC_PORTSC_LWS;
    XhcWriteOpReg (Xhc, Offset, State);
    State &= ~XHC_PORTSC_PLS;
    State |= (3 << 5) ;
    XhcWriteOpReg (Xhc, Offset, State);

    break;

  case EfiUsbPortReset:
    DEBUG ((EFI_D_INFO, "XhcUsbPortReset!\n"));
    //
    // Make sure Host Controller not halt before reset it
    //
    if (XhcIsHalt (Xhc)) {
      Status = XhcRunHC (Xhc, XHC_GENERIC_TIMEOUT);

      if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_WARN, "XhcSetRootHubPortFeature :failed to start HC - %d\n", (int)Status));
        break;
      }
    }

    //
    // 4.3.1 Resetting a Root Hub Port
    // 1) Write the PORTSC register with the Port Reset (PR) bit set to '1'.
    //
    State |= XHC_PORTSC_RESET;
    XhcWriteOpReg (Xhc, Offset, State);
    XhcWaitOpRegBit(Xhc, Offset, XHC_PORTSC_PRC, TRUE, XHC_GENERIC_TIMEOUT);

    break;

  case EfiUsbPortPower:
    //
    // Not supported, ignore the operation
    //
    Status = EFI_SUCCESS;
    break;

  case EfiUsbPortOwner:
    //
    // XHCI root hub port don't has the owner bit, ignore the operation
    //
    Status = EFI_SUCCESS;
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
  }

ON_EXIT:
  DEBUG ((EFI_D_INFO, "status %d\n", (int) Status));
#if defined(notdef_cavium)
  gBS->RestoreTPL (OldTpl);
#endif
  return Status;
}

/**
  Retrieves the capability of root hub ports.

  @param  This                  The EFI_USB2_HC_PROTOCOL instance.
  @param  MaxSpeed              Max speed supported by the controller.
  @param  PortNumber            Number of the root hub ports.
  @param  Is64BitCapable        Whether the controller supports 64-bit memory
                                addressing.

  @retval EFI_SUCCESS           Host controller capability were retrieved successfully.
  @retval EFI_INVALID_PARAMETER Either of the three capability pointer is NULL.

**/
EFI_STATUS
EFIAPI
XhcGetCapability (
  IN  EFI_USB2_HC_PROTOCOL  *This,
  OUT UINT8                 *MaxSpeed,
  OUT UINT8                 *PortNumber,
  OUT UINT8                 *Is64BitCapable
  )
{
  USB_XHCI_INSTANCE  *Xhc;
  /* EFI_TPL            OldTpl; */

  if ((MaxSpeed == NULL) || (PortNumber == NULL) || (Is64BitCapable == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl          = gBS->RaiseTPL (XHC_TPL); */

  Xhc             = XHC_FROM_THIS (This);
  *MaxSpeed       = EFI_USB_SPEED_SUPER;
  *PortNumber     = (UINT8) (/* Xhc->HcSParams1.Data.MaxPorts */ Xhc->hcsparams1.s.maxports);
  *Is64BitCapable = (UINT8) (/* Xhc->HcCParams.Data.Ac64 */ Xhc->hccparams.s.ac64);
  DEBUG ((EFI_D_INFO, "%d ports, 64 bit %d\n", *PortNumber, *Is64BitCapable));

  /* gBS->RestoreTPL (OldTpl); */

  return EFI_SUCCESS;
}

/**
  Provides software reset for the USB host controller.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  Attributes            A bit mask of the reset operation to perform.

  @retval EFI_SUCCESS           The reset operation succeeded.
  @retval EFI_INVALID_PARAMETER Attributes is not valid.
  @retval EFI_UNSUPPOURTED      The type of reset specified by Attributes is
                                not currently supported by the host controller.
  @retval EFI_DEVICE_ERROR      Host controller isn't halted to reset.

**/
EFI_STATUS
EFIAPI
XhcReset (
  IN EFI_USB2_HC_PROTOCOL  *This,
  IN UINT16                Attributes
  )
{
  USB_XHCI_INSTANCE  *Xhc;
  EFI_STATUS         Status;
  /* EFI_TPL            OldTpl; */

  Xhc = XHC_FROM_THIS (This);
  if (Xhc->DevicePath != NULL) {
#if defined(notdef_cavium)
    //
    // Report Status Code to indicate reset happens
    //
    REPORT_STATUS_CODE_WITH_DEVICE_PATH (
      EFI_PROGRESS_CODE,
      (EFI_IO_BUS_USB | EFI_IOB_PC_RESET),
      Xhc->DevicePath
      );
#else
    // Nothing to do
#endif
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  switch (Attributes) {
  case EFI_USB_HC_RESET_GLOBAL:
  //
  // Flow through, same behavior as Host Controller Reset
  //
  case EFI_USB_HC_RESET_HOST_CONTROLLER:
    if ((Xhc->DebugCapSupOffset != 0xFFFFFFFF) && ((XhcReadExtCapReg (Xhc, Xhc->DebugCapSupOffset) & 0xFF) == XHC_CAP_USB_DEBUG) &&
        ((XhcReadExtCapReg (Xhc, Xhc->DebugCapSupOffset + XHC_DC_DCCTRL) & BIT0) != 0)) {
      Status = EFI_SUCCESS;
      goto ON_EXIT;
    }
    //
    // Host Controller must be Halt when Reset it
    //
    if (!XhcIsHalt (Xhc)) {
        /*
         * Per XHCI specification section 5.4.1.1 Run/Stop (R/S)
         * The xHC is forced to halt within 16 ms. of software clearing the R/S bit to ‘0’
         * Since lower level SW could initialize HC we have to wait at least 16ms to
         * force HC to halt
         */
        Status = XhcHaltHC (Xhc, XHC_1_MILLISECOND * 200);

      if (EFI_ERROR (Status)) {
        Status = EFI_DEVICE_ERROR;
        goto ON_EXIT;
      }
    }

    Status = XhcResetHC (Xhc, XHC_RESET_TIMEOUT);
    ASSERT (!(XHC_REG_BIT_IS_SET (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_CNR)));
    if (EFI_ERROR (Status)) {
      goto ON_EXIT;
    }

    //
    // Clean up the asynchronous transfers, currently only
    // interrupt supports asynchronous operation.
    //
    XhciDelAllAsyncIntTransfers (Xhc);
    XhcFreeSched (Xhc);

    XhcInitSched (Xhc);
    break;

  case EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG:
  case EFI_USB_HC_RESET_HOST_WITH_DEBUG:
    Status = EFI_UNSUPPORTED;
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
  }

ON_EXIT:
  DEBUG ((EFI_D_INFO, "status %d\n", (int) Status));
  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}

/**
  Retrieves the current status of a USB root hub port.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  PortNumber            The root hub port to retrieve the state from.
                                This value is zero-based.
  @param  PortStatus            Variable to receive the port state.

  @retval EFI_SUCCESS           The status of the USB root hub port specified.
                                by PortNumber was returned in PortStatus.
  @retval EFI_INVALID_PARAMETER PortNumber is invalid.
  @retval EFI_DEVICE_ERROR      Can't read register.

**/
EFI_STATUS
EFIAPI
XhcGetRootHubPortStatus (
  IN  EFI_USB2_HC_PROTOCOL  *This,
  IN  UINT8                 PortNumber,
  OUT EFI_USB_PORT_STATUS   *PortStatus
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  UINT32                  Offset;
  UINT32                  State;
  UINT32                  TotalPort;
  UINTN                   Index;
  UINTN                   MapSize;
  EFI_STATUS              Status;
  USB_DEV_ROUTE           ParentRouteChart;
  /* EFI_TPL                 OldTpl; */

  if (PortStatus == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc       = XHC_FROM_THIS (This);
  Status    = EFI_SUCCESS;

  TotalPort = Xhc->hcsparams1.s.maxports;

  if (PortNumber >= TotalPort) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  Offset                       = (UINT32) (XHC_PORTSC_OFFSET + (0x10 * PortNumber));
  PortStatus->PortStatus       = 0;
  PortStatus->PortChangeStatus = 0;

  State = XhcReadOpReg (Xhc, Offset);

  //
  // According to XHCI 1.0 spec, bit 10~13 of the root port status register identifies the speed of the attached device.
  //
  switch ((State & XHC_PORTSC_PS) >> 10) {
  case 2:
    PortStatus->PortStatus |= USB_PORT_STAT_LOW_SPEED;
    break;

  case 3:
    PortStatus->PortStatus |= USB_PORT_STAT_HIGH_SPEED;
    break;

  case 4:
    PortStatus->PortStatus |= USB_PORT_STAT_SUPER_SPEED;
    break;

  default:
    break;
  }

  //
  // Convert the XHCI port/port change state to UEFI status
  //
  MapSize = sizeof (mUsbPortStateMap) / sizeof (USB_PORT_STATE_MAP);

  for (Index = 0; Index < MapSize; Index++) {
    if (XHC_BIT_IS_SET (State, mUsbPortStateMap[Index].HwState)) {
      PortStatus->PortStatus = (UINT16) (PortStatus->PortStatus | mUsbPortStateMap[Index].UefiState);
    }
  }
  //
  // Bit5~8 reflects its current link state.
  //
  if ((State & XHC_PORTSC_PLS) >> 5 == 3) {
    PortStatus->PortStatus |= USB_PORT_STAT_SUSPEND;
  }

  MapSize = sizeof (mUsbPortChangeMap) / sizeof (USB_PORT_STATE_MAP);

  for (Index = 0; Index < MapSize; Index++) {
    if (XHC_BIT_IS_SET (State, mUsbPortChangeMap[Index].HwState)) {
      PortStatus->PortChangeStatus = (UINT16) (PortStatus->PortChangeStatus | mUsbPortChangeMap[Index].UefiState);
    }
  }

  MapSize = sizeof (mUsbClearPortChangeMap) / sizeof (USB_CLEAR_PORT_MAP);

  for (Index = 0; Index < MapSize; Index++) {
    if (XHC_BIT_IS_SET (State, mUsbClearPortChangeMap[Index].HwState)) {
      XhcClearRootHubPortFeature (This, PortNumber, (EFI_USB_PORT_FEATURE)mUsbClearPortChangeMap[Index].Selector);
    }
  }

  //
  // Poll the root port status register to enable/disable corresponding device slot if there is a device attached/detached.
  // For those devices behind hub, we get its attach/detach event by hooking Get_Port_Status request at control transfer for those hub.
  //
  ParentRouteChart.Dword = 0;
  XhcPollPortStatusChange (Xhc, ParentRouteChart, PortNumber, PortStatus);

ON_EXIT:
   /* gBS->RestoreTPL (OldTpl); */
  return Status;
}

/**
  Retrieve the current state of the USB host controller.

  @param  This                   This EFI_USB2_HC_PROTOCOL instance.
  @param  State                  Variable to return the current host controller
                                 state.

  @retval EFI_SUCCESS            Host controller state was returned in State.
  @retval EFI_INVALID_PARAMETER  State is NULL.
  @retval EFI_DEVICE_ERROR       An error was encountered while attempting to
                                 retrieve the host controller's current state.

**/
EFI_STATUS
EFIAPI
XhcGetState (
  IN  EFI_USB2_HC_PROTOCOL  *This,
  OUT EFI_USB_HC_STATE      *State
  )
{
  USB_XHCI_INSTANCE  *Xhc;
  /* EFI_TPL            OldTpl; */

  if (State == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc    = XHC_FROM_THIS (This);

  if (XHC_REG_BIT_IS_SET (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HALT)) {
    *State = EfiUsbHcStateHalt;
  } else {
    *State = EfiUsbHcStateOperational;
  }

  DEBUG ((EFI_D_INFO, "current state %d\n", *State));
  /* gBS->RestoreTPL (OldTpl); */

  return EFI_SUCCESS;
}

/**
  Sets the USB host controller to a specific state.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  State                 The state of the host controller that will be set.

  @retval EFI_SUCCESS           The USB host controller was successfully placed
                                in the state specified by State.
  @retval EFI_INVALID_PARAMETER State is invalid.
  @retval EFI_DEVICE_ERROR      Failed to set the state due to device error.

**/
EFI_STATUS
EFIAPI
XhcSetState (
  IN EFI_USB2_HC_PROTOCOL  *This,
  IN EFI_USB_HC_STATE      State
  )
{
  USB_XHCI_INSTANCE   *Xhc;
  EFI_STATUS          Status;
  EFI_USB_HC_STATE    CurState;
  /* EFI_TPL             OldTpl; */

  Status = XhcGetState (This, &CurState);

  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  if (CurState == State) {
    return EFI_SUCCESS;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc    = XHC_FROM_THIS (This);

  switch (State) {
  case EfiUsbHcStateHalt:
    Status = XhcHaltHC(Xhc, XHC_GENERIC_TIMEOUT);
    break;

  case EfiUsbHcStateOperational:
#if defined(notdef_cavium)
    if (XHC_REG_BIT_IS_SET (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HSE)) {
      Status = EFI_DEVICE_ERROR;
      break;
    }

    if (!XHC_REG_BIT_IS_SET (Xhc, XHC_USBSTS_OFFSET, XHC_USBSTS_HALT)) {
      Status = EFI_DEVICE_ERROR;
      break;
    }
#else
    {
        uint32_t hcsts = XhcReadOpReg(Xhc, XHC_USBSTS_OFFSET);
        if (( hcsts & XHC_USBSTS_HSE) || !(hcsts &  XHC_USBSTS_HALT)) {
            Status = EFI_DEVICE_ERROR;
            break;
        }
    }
#endif
    //
    // Software must not write a one to this field unless the host controller
    // is in the Halted state. Doing so will yield undefined results.
    // refers to Spec[XHCI1.0-2.3.1]
    //
    Status = XhcRunHC (Xhc, XHC_GENERIC_TIMEOUT);
    break;

  case EfiUsbHcStateSuspend:
    Status = EFI_UNSUPPORTED;
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
  }

  DEBUG ((EFI_D_INFO, "status %d\n", (int) Status));
#if defined(notdef_cavium)
  gBS->RestoreTPL (OldTpl);
#endif
  return Status;
}

/**
  Submits control transfer to a target USB device.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress         The target device address.
  @param  DeviceSpeed           Target device speed.
  @param  MaximumPacketLength   Maximum packet size the default control transfer
                                endpoint is capable of sending or receiving.
  @param  Request               USB device request to send.
  @param  TransferDirection     Specifies the data direction for the data stage
  @param  Data                  Data buffer to be transmitted or received from USB
                                device.
  @param  DataLength            The size (in bytes) of the data buffer.
  @param  Timeout               Indicates the maximum timeout, in millisecond.
  @param  Translator            Transaction translator to be used by this device.
  @param  TransferResult        Return the result of this control transfer.

  @retval EFI_SUCCESS           Transfer was completed successfully.
  @retval EFI_OUT_OF_RESOURCES  The transfer failed due to lack of resources.
  @retval EFI_INVALID_PARAMETER Some parameters are invalid.
  @retval EFI_TIMEOUT           Transfer failed due to timeout.
  @retval EFI_DEVICE_ERROR      Transfer failed due to host controller or device error.

**/
EFI_STATUS
EFIAPI
XhcControlTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN     EFI_USB_DEVICE_REQUEST              *Request,
  IN     EFI_USB_DATA_DIRECTION              TransferDirection,
  IN OUT VOID                                *Data,
  IN OUT UINTN                               *DataLength,
  IN     UINTN                               Timeout,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  OUT    UINT32                              *TransferResult
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  URB                     *Urb;
  UINT8                   Endpoint;
  UINT8                   Index;
  UINT8                   DescriptorType;
  UINT8                   SlotId;
  UINT8                   TTT;
  UINT8                   MTT;
  UINT32                  MaxPacket0;
  EFI_USB_HUB_DESCRIPTOR  *HubDesc;
  /* EFI_TPL                 OldTpl; */
  EFI_STATUS              Status;
  EFI_STATUS              RecoveryStatus;
  UINTN                   MapSize;
  EFI_USB_PORT_STATUS     PortStatus;
  UINT32                  State;
  EFI_USB_DEVICE_REQUEST  ClearPortRequest;
  UINTN                   Len;
  unsigned                ErrorLevel = EFI_D_ERROR;

  //
  // Validate parameters
  //
  if ((Request == NULL) || (TransferResult == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((TransferDirection != EfiUsbDataIn) &&
      (TransferDirection != EfiUsbDataOut) &&
      (TransferDirection != EfiUsbNoData)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((TransferDirection == EfiUsbNoData) &&
      ((Data != NULL) || (*DataLength != 0))) {
    return EFI_INVALID_PARAMETER;
  }

  if ((TransferDirection != EfiUsbNoData) &&
     ((Data == NULL) || (*DataLength == 0))) {
    return EFI_INVALID_PARAMETER;
  }

  if ((MaximumPacketLength != 8)  && (MaximumPacketLength != 16) &&
      (MaximumPacketLength != 32) && (MaximumPacketLength != 64) &&
      (MaximumPacketLength != 512)
      ) {
    return EFI_INVALID_PARAMETER;
  }

  if ((DeviceSpeed == EFI_USB_SPEED_LOW) && (MaximumPacketLength != 8)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((DeviceSpeed == EFI_USB_SPEED_SUPER) && (MaximumPacketLength != 512)) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc             = XHC_FROM_THIS (This);

  Status          = EFI_DEVICE_ERROR;
  *TransferResult = EFI_USB_ERR_SYSTEM;
  Len             = 0;

  if (/* XhcIsHalt (Xhc) || XhcIsSysError (Xhc) */bdk_unlikely(cvmXhcNotOK(Xhc))) {
    DEBUG ((EFI_D_ERROR, "HC halted at entrance\n"));
    goto ON_EXIT;
  }

  //
  // Check if the device is still enabled before every transaction.
  //
  SlotId = XhcBusDevAddrToSlotId (Xhc, DeviceAddress);
  if (SlotId == 0) {
    goto ON_EXIT;
  }

  //
  // Hook the Set_Address request from UsbBus.
  // According to XHCI 1.0 spec, the Set_Address request is replaced by XHCI's Address_Device cmd.
  //
  if ((Request->Request     == USB_REQ_SET_ADDRESS) &&
      (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD, USB_TARGET_DEVICE))) {
    //
    // Reset the BusDevAddr field of all disabled entries in UsbDevContext array firstly.
    // This way is used to clean the history to avoid using wrong device address by XhcAsyncInterruptTransfer().
    //
    for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
      if (!Xhc->UsbDevContext[Index + 1].Enabled &&
          (Xhc->UsbDevContext[Index + 1].SlotId == 0) &&
          (Xhc->UsbDevContext[Index + 1].BusDevAddr == (UINT8)Request->Value)) {
        Xhc->UsbDevContext[Index + 1].BusDevAddr = 0;
      }
    }

    if (Xhc->UsbDevContext[SlotId].XhciDevAddr == 0) {
      Status = EFI_DEVICE_ERROR;
      goto ON_EXIT;
    }
    //
    // The actual device address has been assigned by XHCI during initializing the device slot.
    // So we just need establish the mapping relationship between the device address requested from UsbBus
    // and the actual device address assigned by XHCI. The the following invocations through EFI_USB2_HC_PROTOCOL interface
    // can find out the actual device address by it.
    //
    Xhc->UsbDevContext[SlotId].BusDevAddr = (UINT8)Request->Value;
    Status = EFI_SUCCESS;
    goto ON_EXIT;
  }

  //
  // Create a new URB, insert it into the asynchronous
  // schedule list, then poll the execution status.
  // Note that we encode the direction in address although default control
  // endpoint is bidirectional. XhcCreateUrb expects this
  // combination of Ep addr and its direction.
  //
  Endpoint = (UINT8) (0 | ((TransferDirection == EfiUsbDataIn) ? 0x80 : 0));
  Urb = XhcCreateUrb (
          Xhc,
          DeviceAddress,
          Endpoint,
          DeviceSpeed,
          MaximumPacketLength,
          XHC_CTRL_TRANSFER,
          Request,
          Data,
          *DataLength,
          NULL,
          NULL
          );

  if (Urb == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to create URB"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Status = XhcExecTransfer (Xhc, FALSE, Urb, Timeout);

  //
  // Get the status from URB. The result is updated in XhcCheckUrbResult
  // which is called by XhcExecTransfer
  //
  *TransferResult = Urb->Result;
  *DataLength     = Urb->Completed;

  if (Status == EFI_TIMEOUT) {
    //
    // The transfer timed out. Abort the transfer by dequeueing of the TD.
    //
    RecoveryStatus = XhcDequeueTrbFromEndpoint(Xhc, Urb);
    if (EFI_ERROR(RecoveryStatus)) {
      DEBUG((EFI_D_ERROR, "XhcControlTransfer: XhcDequeueTrbFromEndpoint failed\n"));
    }
    goto FREE_URB;
  } else {
    if (*TransferResult == EFI_USB_NOERROR) {
      Status = EFI_SUCCESS;
    } else if (*TransferResult == EFI_USB_ERR_STALL) {
      RecoveryStatus = XhcRecoverHaltedEndpoint(Xhc, Urb);
      if (EFI_ERROR (RecoveryStatus)) {
        DEBUG ((EFI_D_ERROR, "XhcRecoverHaltedEndpoint failed\n"));
      } else {
          ErrorLevel = EFI_D_WARN;
      }
      Status = EFI_DEVICE_ERROR;
      goto FREE_URB;
    } else {
      goto FREE_URB;
    }
  }
#if defined(notdef_cavium)
  Xhc->PciIo->Flush (Xhc->PciIo);

  if (Urb->DataMap != NULL) {
    Status = Xhc->PciIo->Unmap (Xhc->PciIo, Urb->DataMap);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      Status = EFI_DEVICE_ERROR;
      goto FREE_URB;
    }
  }
#else
  BDK_WMB;
#endif
  //
  // Hook Get_Descriptor request from UsbBus as we need evaluate context and configure endpoint.
  // Hook Get_Status request form UsbBus as we need trace device attach/detach event happened at hub.
  // Hook Set_Config request from UsbBus as we need configure device endpoint.
  //
  if ((Request->Request     == USB_REQ_GET_DESCRIPTOR) &&
      ((Request->RequestType == USB_REQUEST_TYPE (EfiUsbDataIn, USB_REQ_TYPE_STANDARD, USB_TARGET_DEVICE)) ||
      ((Request->RequestType == USB_REQUEST_TYPE (EfiUsbDataIn, USB_REQ_TYPE_CLASS, USB_TARGET_DEVICE))))) {
    DescriptorType = (UINT8)(Request->Value >> 8);
    if ((DescriptorType == USB_DESC_TYPE_DEVICE) && ((*DataLength == sizeof (EFI_USB_DEVICE_DESCRIPTOR)) || ((DeviceSpeed == EFI_USB_SPEED_FULL) && (*DataLength >= 8)))) {
        ASSERT (Data != NULL);
        //
        // Store a copy of device scriptor as hub device need this info to configure endpoint.
        //
        CopyMem (&Xhc->UsbDevContext[SlotId].DevDesc, Data, *DataLength);
        if (Xhc->UsbDevContext[SlotId].DevDesc.BcdUSB >= 0x0300) {
          //
          // If it's a usb3.0 device, then its max packet size is a 2^n.
          //
          MaxPacket0 = 1 << Xhc->UsbDevContext[SlotId].DevDesc.MaxPacketSize0;
        } else {
          MaxPacket0 = Xhc->UsbDevContext[SlotId].DevDesc.MaxPacketSize0;
        }
        bool doEval;
        if (NULL == Xhc->UsbDevContext[SlotId].ConfDesc) {
            Xhc->UsbDevContext[SlotId].ConfDesc = AllocateZeroPool (Xhc->UsbDevContext[SlotId].DevDesc.NumConfigurations * sizeof (EFI_USB_CONFIG_DESCRIPTOR *));
            doEval = true;
        } else {
            doEval =
                (Xhc->UsbDevContext[SlotId].InputContext &&
                 ((INPUT_CONTEXT*)Xhc->UsbDevContext[SlotId].InputContext)->EP[0].MaxPacketSize != MaxPacket0);
        }

        if (doEval) {
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
            Status = XhcEvaluateContext64 (Xhc, SlotId, MaxPacket0);
#else
            if (Xhc->/* HcCParams.Data.Csz */hccparams.s.csz == 0) {
                Status = XhcEvaluateContext (Xhc, SlotId, MaxPacket0);
            } else {
                Status = XhcEvaluateContext64 (Xhc, SlotId, MaxPacket0);
            }
#endif
        }
    } else if (DescriptorType == USB_DESC_TYPE_CONFIG) {
      ASSERT (Data != NULL);
      if (*DataLength == ((UINT16 *)Data)[1]) {
        //
        // Get configuration value from request, Store the configuration descriptor for Configure_Endpoint cmd.
        //
        Index = (UINT8)Request->Value;
        ASSERT (Index < Xhc->UsbDevContext[SlotId].DevDesc.NumConfigurations);
        Xhc->UsbDevContext[SlotId].ConfDesc[Index] = AllocateZeroPool(*DataLength);
        CopyMem (Xhc->UsbDevContext[SlotId].ConfDesc[Index], Data, *DataLength);
        //
        // Default to use AlternateSetting 0 for all interfaces.
        //
        Xhc->UsbDevContext[SlotId].ActiveAlternateSetting = AllocateZeroPool (Xhc->UsbDevContext[SlotId].ConfDesc[Index]->NumInterfaces * sizeof (UINT8));
      }
    } else if (((DescriptorType == USB_DESC_TYPE_HUB) ||
               (DescriptorType == USB_DESC_TYPE_HUB_SUPER_SPEED)) && (*DataLength > 2)) {
      ASSERT (Data != NULL);
      HubDesc = (EFI_USB_HUB_DESCRIPTOR *)Data;
      ASSERT (HubDesc->NumPorts <= 15);
      //
      // The bit 5,6 of HubCharacter field of Hub Descriptor is TTT.
      //
      TTT = (UINT8)((HubDesc->HubCharacter & (BIT5 | BIT6)) >> 5);
      if (Xhc->UsbDevContext[SlotId].DevDesc.DeviceProtocol == 2) {
        //
        // Don't support multi-TT feature for super speed hub now.
        //
        MTT = 0;
        DEBUG ((EFI_D_INFO, "Don't support multi-TT feature for Hub at this time. (forcing MTT disable)\n"));
      } else {
        MTT = 0;
      }
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
      Status = XhcConfigHubContext64 (Xhc, SlotId, HubDesc->NumPorts, TTT, MTT);
#else
      if (Xhc->/* HcCParams.Data.Csz */hccparams.s.csz == 0) {
        Status = XhcConfigHubContext (Xhc, SlotId, HubDesc->NumPorts, TTT, MTT);
      } else {
        Status = XhcConfigHubContext64 (Xhc, SlotId, HubDesc->NumPorts, TTT, MTT);
      }
#endif
    }
  } else if ((Request->Request     == USB_REQ_SET_CONFIG) &&
             (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD, USB_TARGET_DEVICE))) {
    //
    // Hook Set_Config request from UsbBus as we need configure device endpoint.
    //
    for (Index = 0; Index < Xhc->UsbDevContext[SlotId].DevDesc.NumConfigurations; Index++) {
      if (Xhc->UsbDevContext[SlotId].ConfDesc[Index]->ConfigurationValue == (UINT8)Request->Value) {
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
          Status = XhcSetConfigCmd64 (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Index]);
#else
        if (Xhc->/* HcCParams.Data.Csz */hccparams.s.csz == 0) {
          Status = XhcSetConfigCmd (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Index]);
        } else {
          Status = XhcSetConfigCmd64 (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Index]);
        }
#endif
        break;
      }
    }
  } else if ((Request->Request     == USB_REQ_SET_INTERFACE) &&
             (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD, USB_TARGET_INTERFACE))) {
    //
    // Hook Set_Interface request from UsbBus as we need configure interface setting.
    // Request->Value indicates AlterlateSetting to set
    // Request->Index indicates Interface to set
    //
    if (Xhc->UsbDevContext[SlotId].ActiveAlternateSetting[(UINT8) Request->Index] != (UINT8) Request->Value) {
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
        Status = XhcSetInterface64 (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Xhc->UsbDevContext[SlotId].ActiveConfiguration - 1], Request);
#else
      if (Xhc->/* HcCParams.Data.Csz */hccparams.s.csz == 0) {
        Status = XhcSetInterface (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Xhc->UsbDevContext[SlotId].ActiveConfiguration - 1], Request);
      } else {
        Status = XhcSetInterface64 (Xhc, SlotId, DeviceSpeed, Xhc->UsbDevContext[SlotId].ConfDesc[Xhc->UsbDevContext[SlotId].ActiveConfiguration - 1], Request);
      }

#endif
    }
  } else if ((Request->Request     == USB_REQ_GET_STATUS) &&
             (Request->RequestType == USB_REQUEST_TYPE (EfiUsbDataIn, USB_REQ_TYPE_CLASS, USB_TARGET_OTHER))) {
    ASSERT (Data != NULL);
    //
    // Hook Get_Status request from UsbBus to keep track of the port status change.
    //
    State                       = *(UINT32 *)Data;
    PortStatus.PortStatus       = 0;
    PortStatus.PortChangeStatus = 0;

    if (DeviceSpeed == EFI_USB_SPEED_SUPER) {
      //
      // For super speed hub, its bit10~12 presents the attached device speed.
      //
      if ((State & XHC_PORTSC_PS) >> 10 == 0) {
        PortStatus.PortStatus |= USB_PORT_STAT_SUPER_SPEED;
      }
    } else {
      //
      // For high or full/low speed hub, its bit9~10 presents the attached device speed.
      //
      if (XHC_BIT_IS_SET (State, BIT9)) {
        PortStatus.PortStatus |= USB_PORT_STAT_LOW_SPEED;
      } else if (XHC_BIT_IS_SET (State, BIT10)) {
        PortStatus.PortStatus |= USB_PORT_STAT_HIGH_SPEED;
      }
    }

    //
    // Convert the XHCI port/port change state to UEFI status
    //
    MapSize = sizeof (mUsbHubPortStateMap) / sizeof (USB_PORT_STATE_MAP);
    for (Index = 0; Index < MapSize; Index++) {
      if (XHC_BIT_IS_SET (State, mUsbHubPortStateMap[Index].HwState)) {
        PortStatus.PortStatus = (UINT16) (PortStatus.PortStatus | mUsbHubPortStateMap[Index].UefiState);
      }
    }

    MapSize = sizeof (mUsbHubPortChangeMap) / sizeof (USB_PORT_STATE_MAP);
    for (Index = 0; Index < MapSize; Index++) {
      if (XHC_BIT_IS_SET (State, mUsbHubPortChangeMap[Index].HwState)) {
        PortStatus.PortChangeStatus = (UINT16) (PortStatus.PortChangeStatus | mUsbHubPortChangeMap[Index].UefiState);
      }
    }

    MapSize = sizeof (mUsbHubClearPortChangeMap) / sizeof (USB_CLEAR_PORT_MAP);

    for (Index = 0; Index < MapSize; Index++) {
      if (XHC_BIT_IS_SET (State, mUsbHubClearPortChangeMap[Index].HwState)) {
        ZeroMem (&ClearPortRequest, sizeof (EFI_USB_DEVICE_REQUEST));
        ClearPortRequest.RequestType  = USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_CLASS, USB_TARGET_OTHER);
        ClearPortRequest.Request      = (UINT8) USB_REQ_CLEAR_FEATURE;
        ClearPortRequest.Value        = mUsbHubClearPortChangeMap[Index].Selector;
        ClearPortRequest.Index        = Request->Index;
        ClearPortRequest.Length       = 0;

        XhcControlTransfer (
          This,
          DeviceAddress,
          DeviceSpeed,
          MaximumPacketLength,
          &ClearPortRequest,
          EfiUsbNoData,
          NULL,
          &Len,
          Timeout,
          Translator,
          TransferResult
          );
      }
    }

    XhcPollPortStatusChange (Xhc, Xhc->UsbDevContext[SlotId].RouteString, (UINT8)Request->Index, &PortStatus);
#if defined(notdef_cavium)
    *(UINT32 *)Data = *(UINT32*)&PortStatus;
#else
    memcpy(Data,&PortStatus, sizeof(UINT32)); // Compiler is unhappy about strict aliasing
#endif
  }

FREE_URB:
  FreePool (Urb);

ON_EXIT:

  if (EFI_ERROR (Status)) {
      DEBUG ((ErrorLevel, "error - %d, transfer - %x\n", (int)Status, *TransferResult));
  }

  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}

/**
  Submits bulk transfer to a bulk endpoint of a USB device.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress         Target device address.
  @param  EndPointAddress       Endpoint number and its direction in bit 7.
  @param  DeviceSpeed           Device speed, Low speed device doesn't support bulk
                                transfer.
  @param  MaximumPacketLength   Maximum packet size the endpoint is capable of
                                sending or receiving.
  @param  DataBuffersNumber     Number of data buffers prepared for the transfer.
  @param  Data                  Array of pointers to the buffers of data to transmit
                                from or receive into.
  @param  DataLength            The length of the data buffer.
  @param  DataToggle            On input, the initial data toggle for the transfer;
                                On output, it is updated to to next data toggle to
                                use of the subsequent bulk transfer.
  @param  Timeout               Indicates the maximum time, in millisecond, which
                                the transfer is allowed to complete.
  @param  Translator            A pointr to the transaction translator data.
  @param  TransferResult        A pointer to the detailed result information of the
                                bulk transfer.

  @retval EFI_SUCCESS           The transfer was completed successfully.
  @retval EFI_OUT_OF_RESOURCES  The transfer failed due to lack of resource.
  @retval EFI_INVALID_PARAMETER Some parameters are invalid.
  @retval EFI_TIMEOUT           The transfer failed due to timeout.
  @retval EFI_DEVICE_ERROR      The transfer failed due to host controller error.

**/
EFI_STATUS
EFIAPI
XhcBulkTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               EndPointAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN     UINT8                               DataBuffersNumber,
  IN OUT VOID                                *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
  IN OUT UINTN                               *DataLength,
  IN OUT UINT8                               *DataToggle,
  IN     UINTN                               Timeout,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  OUT    UINT32                              *TransferResult
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  URB                     *Urb;
  UINT8                   SlotId;
  EFI_STATUS              Status;
  EFI_STATUS              RecoveryStatus;
  /* EFI_TPL                 OldTpl; */
  unsigned                ErrorLevel = EFI_D_ERROR;

  //
  // Validate the parameters
  //
  if ((DataLength == NULL) || (*DataLength == 0) ||
      (Data == NULL) || (Data[0] == NULL) || (TransferResult == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((*DataToggle != 0) && (*DataToggle != 1)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((DeviceSpeed == EFI_USB_SPEED_LOW) ||
      ((DeviceSpeed == EFI_USB_SPEED_FULL) && (MaximumPacketLength > 64)) ||
      ((EFI_USB_SPEED_HIGH == DeviceSpeed) && (MaximumPacketLength > 512)) ||
      ((EFI_USB_SPEED_SUPER == DeviceSpeed) && (MaximumPacketLength > 1024))) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc             = XHC_FROM_THIS (This);

  *TransferResult = EFI_USB_ERR_SYSTEM;
  Status          = EFI_DEVICE_ERROR;

  if (/* XhcIsHalt (Xhc) || XhcIsSysError (Xhc) */ bdk_unlikely(cvmXhcNotOK(Xhc))) {
    DEBUG ((EFI_D_ERROR, "HC is halted\n"));
    goto ON_EXIT;
  }

  //
  // Check if the device is still enabled before every transaction.
  //
  SlotId = XhcBusDevAddrToSlotId (Xhc, DeviceAddress);
  if (SlotId == 0) {
    goto ON_EXIT;
  }

  //
  // Create a new URB, insert it into the asynchronous
  // schedule list, then poll the execution status.
  //
  Urb = XhcCreateUrb (
          Xhc,
          DeviceAddress,
          EndPointAddress,
          DeviceSpeed,
          MaximumPacketLength,
          XHC_BULK_TRANSFER,
          NULL,
          Data[0],
          *DataLength,
          NULL,
          NULL
          );

  if (Urb == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to create URB\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Status = XhcExecTransfer (Xhc, FALSE, Urb, Timeout);

  *TransferResult = Urb->Result;
  *DataLength     = Urb->Completed;

  if (Status == EFI_TIMEOUT) {
    //
    // The transfer timed out. Abort the transfer by dequeueing of the TD.
    //
    RecoveryStatus = XhcDequeueTrbFromEndpoint(Xhc, Urb);
    if (EFI_ERROR(RecoveryStatus)) {
      DEBUG((EFI_D_ERROR, "XhcBulkTransfer: XhcDequeueTrbFromEndpoint failed\n"));
    }
  } else {
    if (*TransferResult == EFI_USB_NOERROR) {
      Status = EFI_SUCCESS;
    } else if (*TransferResult == EFI_USB_ERR_STALL) {
      RecoveryStatus = XhcRecoverHaltedEndpoint(Xhc, Urb);
      if (EFI_ERROR (RecoveryStatus)) {
        DEBUG ((EFI_D_ERROR, "XhcRecoverHaltedEndpoint failed\n"));
      } else {
          ErrorLevel = EFI_D_WARN;
      }
      Status = EFI_DEVICE_ERROR;
    }
  }
#if defined(notdef_cavium)
  Xhc->PciIo->Flush (Xhc->PciIo);
#else
  BDK_WMB;
#endif
  XhcFreeUrb (Xhc, Urb);

ON_EXIT:

  if (EFI_ERROR (Status)) {
      DEBUG ((ErrorLevel, "error - %d, transfer - %x\n", (int)Status, *TransferResult));
  }
  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}

/**
  Submits an asynchronous interrupt transfer to an
  interrupt endpoint of a USB device.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress         Target device address.
  @param  EndPointAddress       Endpoint number and its direction encoded in bit 7
  @param  DeviceSpeed           Indicates device speed.
  @param  MaximumPacketLength   Maximum packet size the target endpoint is capable
  @param  IsNewTransfer         If TRUE, to submit an new asynchronous interrupt
                                transfer If FALSE, to remove the specified
                                asynchronous interrupt.
  @param  DataToggle            On input, the initial data toggle to use; on output,
                                it is updated to indicate the next data toggle.
  @param  PollingInterval       The he interval, in milliseconds, that the transfer
                                is polled.
  @param  DataLength            The length of data to receive at the rate specified
                                by  PollingInterval.
  @param  Translator            Transaction translator to use.
  @param  CallBackFunction      Function to call at the rate specified by
                                PollingInterval.
  @param  Context               Context to CallBackFunction.

  @retval EFI_SUCCESS           The request has been successfully submitted or canceled.
  @retval EFI_INVALID_PARAMETER Some parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES  The request failed due to a lack of resources.
  @retval EFI_DEVICE_ERROR      The transfer failed due to host controller error.

**/
EFI_STATUS
EFIAPI
XhcAsyncInterruptTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               EndPointAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN     BOOLEAN                             IsNewTransfer,
  IN OUT UINT8                               *DataToggle,
  IN     UINTN                               PollingInterval,
  IN     UINTN                               DataLength,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  IN     EFI_ASYNC_USB_TRANSFER_CALLBACK     CallBackFunction,
  IN     VOID                                *Context OPTIONAL
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  URB                     *Urb;
  EFI_STATUS              Status;
  UINT8                   SlotId;
  UINT8                   Index;
  UINT8                   *Data;
  /* EFI_TPL                 OldTpl; */

  //
  // Validate parameters
  //
  if (!XHCI_IS_DATAIN (EndPointAddress)) {
    return EFI_INVALID_PARAMETER;
  }

  if (IsNewTransfer) {
    if (DataLength == 0) {
      return EFI_INVALID_PARAMETER;
    }

    if ((*DataToggle != 1) && (*DataToggle != 0)) {
      return EFI_INVALID_PARAMETER;
    }

    if ((PollingInterval > 255) || (PollingInterval < 1)) {
      return EFI_INVALID_PARAMETER;
    }
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc    = XHC_FROM_THIS (This);

  //
  // Delete Async interrupt transfer request.
  //
  if (!IsNewTransfer) {
    //
    // The delete request may happen after device is detached.
    //
    for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
      if (Xhc->UsbDevContext[Index + 1].BusDevAddr == DeviceAddress) {
        break;
      }
    }

    if (Index == CAVIUM_XHCI_MAXSLOTS) {
      Status = EFI_INVALID_PARAMETER;
      goto ON_EXIT;
    }

    Status = XhciDelAsyncIntTransfer (Xhc, DeviceAddress, EndPointAddress);
    DEBUG ((EFI_D_INFO, "remove old transfer for addr %d, Status = %d\n", DeviceAddress, (int)Status));
    goto ON_EXIT;
  }

  Status = EFI_SUCCESS;

  if (/* XhcIsHalt (Xhc) || XhcIsSysError (Xhc) */bdk_unlikely(cvmXhcNotOK(Xhc))) {
      DEBUG ((EFI_D_ERROR, "HC is halted\n"));
    Status = EFI_DEVICE_ERROR;
    goto ON_EXIT;
  }

  //
  // Check if the device is still enabled before every transaction.
  //
  SlotId = XhcBusDevAddrToSlotId (Xhc, DeviceAddress);
  if (SlotId == 0) {
    goto ON_EXIT;
  }

  Data = AllocateZeroPool (DataLength);

  if (Data == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to allocate buffer\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Urb = XhcCreateUrb (
          Xhc,
          DeviceAddress,
          EndPointAddress,
          DeviceSpeed,
          MaximumPacketLength,
          XHC_INT_TRANSFER_ASYNC,
          NULL,
          Data,
          DataLength,
          CallBackFunction,
          Context
          );

  if (Urb == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to create URB\n"));
    FreePool (Data);
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  InsertHeadList (&Xhc->AsyncIntTransfers, &Urb->UrbList);
  //
  // Ring the doorbell
  //
  Status = RingIntTransferDoorBell (Xhc, Urb);

ON_EXIT:
#if defined(notdef_cavium)
  Xhc->PciIo->Flush (Xhc->PciIo);
#else
  BDK_WMB;
#endif
  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}


/**
  Submits synchronous interrupt transfer to an interrupt endpoint
  of a USB device.

  @param  This                  This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress         Target device address.
  @param  EndPointAddress       Endpoint number and its direction encoded in bit 7
  @param  DeviceSpeed           Indicates device speed.
  @param  MaximumPacketLength   Maximum packet size the target endpoint is capable
                                of sending or receiving.
  @param  Data                  Buffer of data that will be transmitted to  USB
                                device or received from USB device.
  @param  DataLength            On input, the size, in bytes, of the data buffer; On
                                output, the number of bytes transferred.
  @param  DataToggle            On input, the initial data toggle to use; on output,
                                it is updated to indicate the next data toggle.
  @param  Timeout               Maximum time, in second, to complete.
  @param  Translator            Transaction translator to use.
  @param  TransferResult        Variable to receive the transfer result.

  @return EFI_SUCCESS           The transfer was completed successfully.
  @return EFI_OUT_OF_RESOURCES  The transfer failed due to lack of resource.
  @return EFI_INVALID_PARAMETER Some parameters are invalid.
  @return EFI_TIMEOUT           The transfer failed due to timeout.
  @return EFI_DEVICE_ERROR      The failed due to host controller or device error

**/
EFI_STATUS
EFIAPI
XhcSyncInterruptTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               EndPointAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN OUT VOID                                *Data,
  IN OUT UINTN                               *DataLength,
  IN OUT UINT8                               *DataToggle,
  IN     UINTN                               Timeout,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  OUT    UINT32                              *TransferResult
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  URB                     *Urb;
  UINT8                   SlotId;
  EFI_STATUS              Status;
  EFI_STATUS              RecoveryStatus;
  /* EFI_TPL                 OldTpl; */
  unsigned                ErrorLevel = EFI_D_ERROR;

  //
  // Validates parameters
  //
  if ((DataLength == NULL) || (*DataLength == 0) ||
      (Data == NULL) || (TransferResult == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((*DataToggle != 1) && (*DataToggle != 0)) {
    return EFI_INVALID_PARAMETER;
  }

  if (((DeviceSpeed == EFI_USB_SPEED_LOW) && (MaximumPacketLength != 8))  ||
      ((DeviceSpeed == EFI_USB_SPEED_FULL) && (MaximumPacketLength > 64)) ||
      ((DeviceSpeed == EFI_USB_SPEED_HIGH) && (MaximumPacketLength > 3072))) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (XHC_TPL); */

  Xhc     = XHC_FROM_THIS (This);

  *TransferResult = EFI_USB_ERR_SYSTEM;
  Status          = EFI_DEVICE_ERROR;

  if (/* XhcIsHalt (Xhc) || XhcIsSysError (Xhc) */bdk_unlikely(cvmXhcNotOK(Xhc))) {
    DEBUG ((EFI_D_ERROR, "HC is halt\n"));
    goto ON_EXIT;
  }

  //
  // Check if the device is still enabled before every transaction.
  //
  SlotId = XhcBusDevAddrToSlotId (Xhc, DeviceAddress);
  if (SlotId == 0) {
    goto ON_EXIT;
  }

  Urb = XhcCreateUrb (
          Xhc,
          DeviceAddress,
          EndPointAddress,
          DeviceSpeed,
          MaximumPacketLength,
          XHC_INT_TRANSFER_SYNC,
          NULL,
          Data,
          *DataLength,
          NULL,
          NULL
          );

  if (Urb == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to create URB\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Status = XhcExecTransfer (Xhc, FALSE, Urb, Timeout);

  *TransferResult = Urb->Result;
  *DataLength     = Urb->Completed;

  if (Status == EFI_TIMEOUT) {
    //
    // The transfer timed out. Abort the transfer by dequeueing of the TD.
    //
    RecoveryStatus = XhcDequeueTrbFromEndpoint(Xhc, Urb);
    if (EFI_ERROR(RecoveryStatus)) {
      DEBUG((EFI_D_ERROR, "XhcSyncInterruptTransfer: XhcDequeueTrbFromEndpoint failed\n"));
    }
  } else {
    if (*TransferResult == EFI_USB_NOERROR) {
      Status = EFI_SUCCESS;
    } else if (*TransferResult == EFI_USB_ERR_STALL) {
      RecoveryStatus = XhcRecoverHaltedEndpoint(Xhc, Urb);
      if (EFI_ERROR (RecoveryStatus)) {
        DEBUG ((EFI_D_ERROR, "XhcRecoverHaltedEndpoint failed\n"));
      } else {
          ErrorLevel = EFI_D_WARN;
      }
      Status = EFI_DEVICE_ERROR;
    }
  }
#if defined(notdef_cavium)
  Xhc->PciIo->Flush (Xhc->PciIo);
#else
  BDK_WMB;
#endif
  XhcFreeUrb (Xhc, Urb);

ON_EXIT:
  if (EFI_ERROR (Status)) {
      DEBUG ((ErrorLevel, "error - %d, transfer - %x\n", (int)Status, *TransferResult));
  }
  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}


/**
  Submits isochronous transfer to a target USB device.

  @param  This                 This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress        Target device address.
  @param  EndPointAddress      End point address with its direction.
  @param  DeviceSpeed          Device speed, Low speed device doesn't support this
                               type.
  @param  MaximumPacketLength  Maximum packet size that the endpoint is capable of
                               sending or receiving.
  @param  DataBuffersNumber    Number of data buffers prepared for the transfer.
  @param  Data                 Array of pointers to the buffers of data that will
                               be transmitted to USB device or received from USB
                               device.
  @param  DataLength           The size, in bytes, of the data buffer.
  @param  Translator           Transaction translator to use.
  @param  TransferResult       Variable to receive the transfer result.

  @return EFI_UNSUPPORTED      Isochronous transfer is unsupported.

**/
EFI_STATUS
EFIAPI
XhcIsochronousTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               EndPointAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN     UINT8                               DataBuffersNumber,
  IN OUT VOID                                *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
  IN     UINTN                               DataLength,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  OUT    UINT32                              *TransferResult
  )
{
  return EFI_UNSUPPORTED;
}


/**
  Submits Async isochronous transfer to a target USB device.

  @param  This                 This EFI_USB2_HC_PROTOCOL instance.
  @param  DeviceAddress        Target device address.
  @param  EndPointAddress      End point address with its direction.
  @param  DeviceSpeed          Device speed, Low speed device doesn't support this
                               type.
  @param  MaximumPacketLength  Maximum packet size that the endpoint is capable of
                               sending or receiving.
  @param  DataBuffersNumber    Number of data buffers prepared for the transfer.
  @param  Data                 Array of pointers to the buffers of data that will
                               be transmitted to USB device or received from USB
                               device.
  @param  DataLength           The size, in bytes, of the data buffer.
  @param  Translator           Transaction translator to use.
  @param  IsochronousCallBack  Function to be called when the transfer complete.
  @param  Context              Context passed to the call back function as
                               parameter.

  @return EFI_UNSUPPORTED      Isochronous transfer isn't supported.

**/
EFI_STATUS
EFIAPI
XhcAsyncIsochronousTransfer (
  IN     EFI_USB2_HC_PROTOCOL                *This,
  IN     UINT8                               DeviceAddress,
  IN     UINT8                               EndPointAddress,
  IN     UINT8                               DeviceSpeed,
  IN     UINTN                               MaximumPacketLength,
  IN     UINT8                               DataBuffersNumber,
  IN OUT VOID                                *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
  IN     UINTN                               DataLength,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
  IN     EFI_ASYNC_USB_TRANSFER_CALLBACK     IsochronousCallBack,
  IN     VOID                                *Context
  )
{
  return EFI_UNSUPPORTED;
}

/**
 ** return cavium node id and physical interface number for a protocol instance
 ** @param usbIf          Address of USB interface instance
 ** @param node           Address of variable to receive node number or NULL
 ** @param usb_port       Address of variable to receive port number or NULL
 ** @param lock           Address of variable to receive pointer to bus level lock or NULL

 ** @return Zero on success, non-zero on failure
 */
int cvm_usbif2node(
    const USB_INTERFACE *usbIf,
    bdk_node_t    *node,
    int           *usb_port,
    void          **lock)
{
     if ((NULL == usbIf) ||
        ((NULL == node) && (NULL == usb_port) && (NULL == lock) ))
        return -1;
     USB_DEVICE *thisDevice = usbIf->Device;
     if (!thisDevice) return -1;
     USB_BUS *thisBus = thisDevice->Bus;
     if (!thisBus || ! thisBus->Usb2Hc) return -1;

     USB_XHCI_INSTANCE       *Xhc = XHC_FROM_THIS( thisBus->Usb2Hc);
     if (node) *node = Xhc->node; // Physical node
     if (usb_port) *usb_port = Xhc->usb_port; // Physical port
     if (lock) *lock = Xhc->xhci_lock; // Port lock
     return 0;
}
