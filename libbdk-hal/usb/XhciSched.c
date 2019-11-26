/** @file

  XHCI transfer scheduling routines.

Copyright (c) 2011 - 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <bdk.h>
#include "Xhci.h"
#include "XhciReg.h"
#include <malloc.h> // for memalign

static inline VOID
XhcWriteDoorBellReg (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
    BDK_WMB; //Settle memory writes
    XhcWrite32(Xhc, Xhc->DBOff+Offset,Data);
}

/**
  Check if the Trb is a transaction of the URBs in XHCI's asynchronous transfer list.

  @param Xhc    The XHCI Instance.
  @param Trb    The TRB to be checked.
  @param Urb    The pointer to the matched Urb.

  @retval TRUE  The Trb is matched with a transaction of the URBs in the async list.
  @retval FALSE The Trb is not matched with any URBs in the async list.

**/
static
BOOLEAN
IsAsyncIntTrb (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  TRB_TEMPLATE        *Trb,
  OUT URB                 **Urb
  )
{
  LIST_ENTRY              *Entry;
  LIST_ENTRY              *Next;
  TRB_TEMPLATE            *CheckedTrb;
  URB                     *CheckedUrb;
  UINTN                   Index;

  EFI_LIST_FOR_EACH_SAFE (Entry, Next, &Xhc->AsyncIntTransfers) {
    CheckedUrb = EFI_LIST_CONTAINER (Entry, URB, UrbList);
    CheckedTrb = CheckedUrb->TrbStart;
    for (Index = 0; Index < CheckedUrb->TrbNum; Index++) {
      if (Trb == CheckedTrb) {
        *Urb = CheckedUrb;
        return TRUE;
      }
      CheckedTrb++;
      if ((UINTN)CheckedTrb >= ((UINTN) CheckedUrb->Ring->RingSeg0 + sizeof (TRB_TEMPLATE) * CheckedUrb->Ring->TrbNumber)) {
        CheckedTrb = (TRB_TEMPLATE*) CheckedUrb->Ring->RingSeg0;
      }
    }
  }

  return FALSE;
}


/**
  Check if the Trb is a transaction of the URB.

  @param Trb    The TRB to be checked
  @param Urb    The transfer ring to be checked.

  @retval TRUE  It is a transaction of the URB.
  @retval FALSE It is not any transaction of the URB.

**/
static BOOLEAN
IsTransferRingTrb (
  IN  TRB_TEMPLATE        *Trb,
  IN  URB                 *Urb
  )
{
  TRB_TEMPLATE  *CheckedTrb;
  unsigned         Index;

  CheckedTrb = Urb->Ring->RingSeg0;

  ASSERT (Urb->Ring->TrbNumber == CMD_RING_TRB_NUMBER || Urb->Ring->TrbNumber == TR_RING_TRB_NUMBER);

  for (Index = 0; Index < Urb->Ring->TrbNumber; Index++) {
    if (Trb == CheckedTrb) {
      return TRUE;
    }
    CheckedTrb++;
  }

  return FALSE;
}


/**
  Create a command transfer TRB to support XHCI command interfaces.

  @param  Xhc       The XHCI Instance.
  @param  CmdTrb    The cmd TRB to be executed.

  @return Created URB or NULL.

**/
static  URB*
XhcCreateCmdTrb (
  USB_XHCI_INSTANCE  *Xhc,
  TRB_TEMPLATE       *CmdTrb
  )
{
  URB    *Urb;

  Urb = AllocateZeroPool (sizeof (URB));
  if (Urb == NULL) {
    return NULL;
  }

//  Urb->Signature  = XHC_URB_SIG;

  Urb->Ring       = &Xhc->CmdRing;
  XhcSyncTrsRing (Xhc, Urb->Ring);
  Urb->TrbNum     = 1;
  Urb->TrbStart   = Urb->Ring->RingEnqueue;
  CopyMem (Urb->TrbStart, CmdTrb, sizeof (TRB_TEMPLATE));
  Urb->TrbStart->CycleBit = Urb->Ring->RingPCS & BIT0;
  Urb->TrbEnd             = Urb->TrbStart;

  return Urb;
}

/**
  Execute a XHCI cmd TRB pointed by CmdTrb.

  @param  Xhc                   The XHCI Instance.
  @param  CmdTrb                The cmd TRB to be executed.
  @param  Timeout               Indicates the maximum time, in millisecond, which the
                                transfer is allowed to complete.
  @param  EvtTrb                The event TRB corresponding to the cmd TRB.

  @retval EFI_SUCCESS           The transfer was completed successfully.
  @retval EFI_INVALID_PARAMETER Some parameters are invalid.
  @retval EFI_TIMEOUT           The transfer failed due to timeout.
  @retval EFI_DEVICE_ERROR      The transfer failed due to host controller error.

**/
static int
XhcCmdTransfer (
    USB_XHCI_INSTANCE     *Xhc,
    TRB_TEMPLATE          *CmdTrb,
    UINTN                 Timeout,
    TRB_TEMPLATE          **EvtTrb
  )
{
  EFI_STATUS      Status;
  URB             *Urb;

  //
  // Validate the parameters
  //
  if ((Xhc == NULL) || (CmdTrb == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_DEVICE_ERROR;

  if (/*XhcIsHalt (Xhc) || XhcIsSysError (Xhc)*/ bdk_unlikely(cvmXhcNotOK(Xhc))) {
    DEBUG ((EFI_D_ERROR, "HC is halted\n"));
    goto ON_EXIT;
  }

  //
  // Create a new URB, then poll the execution status.
  //
  Urb = XhcCreateCmdTrb (Xhc, CmdTrb);

  if (Urb == NULL) {
    DEBUG ((EFI_D_ERROR, "failed to create URB\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

  Status  = XhcExecTransfer (Xhc, TRUE, Urb, Timeout);
  *EvtTrb = Urb->EvtTrb;

  if (Urb->Result == EFI_USB_NOERROR) {
    Status = EFI_SUCCESS;
  }

  XhcFreeUrb (Xhc, Urb);

ON_EXIT:
  return Status;
}

/**
  Create a new URB for a new transaction.

  @param  Xhc       The XHCI Instance
  @param  BusAddr   The logical device address assigned by UsbBus driver
  @param  EpAddr    Endpoint addrress
  @param  DevSpeed  The device speed
  @param  MaxPacket The max packet length of the endpoint
  @param  Type      The transaction type
  @param  Request   The standard USB request for control transfer
  @param  Data      The user data to transfer
  @param  DataLen   The length of data buffer
  @param  Callback  The function to call when data is transferred
  @param  Context   The context to the callback

  @return Created URB or NULL

**/
URB*
XhcCreateUrb (
    USB_XHCI_INSTANCE                  *Xhc,
    UINT8                              BusAddr,
    UINT8                              EpAddr,
    UINT8                              DevSpeed,
    UINTN                              MaxPacket,
    UINTN                              Type,
    EFI_USB_DEVICE_REQUEST             *Request,
    VOID                               *Data,
    UINTN                              DataLen,
    EFI_ASYNC_USB_TRANSFER_CALLBACK    Callback,
    VOID                               *Context
  )
{
  USB_ENDPOINT                  *Ep;
  EFI_STATUS                    Status;
  URB                           *Urb;

  Urb = AllocateZeroPool (sizeof (URB));
    if (Urb == NULL) {
    return NULL;
  }

//  Urb->Signature = XHC_URB_SIG;
  InitializeListHead (&Urb->UrbList);

  Ep            = &Urb->Ep;
  Ep->BusAddr   = BusAddr;
  Ep->EpAddr    = (UINT8)(EpAddr & 0x0F);
  Ep->Direction = ((EpAddr & 0x80) != 0) ? EfiUsbDataIn : EfiUsbDataOut;
  Ep->DevSpeed  = DevSpeed;
  Ep->MaxPacket = MaxPacket;
  Ep->Type      = Type;

  Urb->Request  = Request;
  Urb->Data     = Data;
  Urb->DataLen  = DataLen;
  Urb->Callback = Callback;
  Urb->Context  = Context;

  Status = XhcCreateTransferTrb (Xhc, Urb);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "XhcCreateTransferTrb Failed, Status = %d\n", (int) Status));
    FreePool (Urb);
    Urb = NULL;
  }

  return Urb;
}

/**
  Free an allocated URB.

  @param  Xhc                   The XHCI device.
  @param  Urb                   The URB to free.

**/
VOID
XhcFreeUrb (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN URB                  *Urb
  )
{
  if ((Xhc == NULL) || (Urb == NULL)) {
    return;
  }
#if defined(OCTEONTX_NOT_USED)
  if (Urb->DataMap != NULL) {
    Xhc->PciIo->Unmap (Xhc->PciIo, Urb->DataMap);
  }
#endif
  FreePool (Urb);

}

/**
  Create a transfer TRB.

  @param  Xhc     The XHCI Instance
  @param  Urb     The urb used to construct the transfer TRB.

  @return Created TRB or NULL

**/
EFI_STATUS
XhcCreateTransferTrb (
  USB_XHCI_INSTANCE          *Xhc,
  URB                        *Urb
  )
{
  VOID                          *OutputContext;
  TRANSFER_RING                 *EPRing;
  UINT8                         EPType;
  UINT8                         SlotId;
  UINT8                         Dci;
  TRB                           *TrbStart;
  UINTN                         TotalLen;
  UINTN                         Len;
  UINTN                         TrbNum;
#if defined(OCTEONTX_NOT_USED)
  EFI_PCI_IO_PROTOCOL_OPERATION MapOp;
  EFI_PHYSICAL_ADDRESS          PhyAddr;
  VOID                          *Map;
  EFI_STATUS                    Status;
#endif
  SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
  if (SlotId == 0) {
    return EFI_DEVICE_ERROR;
  }

  Urb->Finished  = FALSE;
  Urb->StartDone = FALSE;
  Urb->EndDone   = FALSE;
  Urb->Completed = 0;
  Urb->Result    = EFI_USB_NOERROR;

  Dci       = XhcEndpointToDci (Urb->Ep.EpAddr, (UINT8)(Urb->Ep.Direction));
  ASSERT (Dci < 32);
  EPRing    = (TRANSFER_RING *)(UINTN) Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1];
  Urb->Ring = EPRing;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
  EPType  = (UINT8) ((DEVICE_CONTEXT_64 *)OutputContext)->EP[Dci-1].EPType;
#else
  if (Xhc->hccparams.s.csz == 0) {
    EPType  = (UINT8) ((DEVICE_CONTEXT *)OutputContext)->EP[Dci-1].EPType;
  } else {
    EPType  = (UINT8) ((DEVICE_CONTEXT_64 *)OutputContext)->EP[Dci-1].EPType;
  }
#endif

  if (Urb->Data != NULL) {
#if defined(OCTEONTX_NOT_USED)
    if (((UINT8) (Urb->Ep.Direction)) == EfiUsbDataIn) {
      MapOp = EfiPciIoOperationBusMasterWrite;
    } else {
      MapOp = EfiPciIoOperationBusMasterRead;
    }

    Len = Urb->DataLen;
    Status  = Xhc->PciIo->Map (Xhc->PciIo, MapOp, Urb->Data, &Len, &PhyAddr, &Map);

    if (EFI_ERROR (Status) || (Len != Urb->DataLen)) {
      DEBUG ((EFI_D_ERROR, "Fail to map Urb->Data.\n"));
      return EFI_OUT_OF_RESOURCES;
    }

    Urb->DataPhy  = (VOID *) ((UINTN) PhyAddr);
    Urb->DataMap  = Map;
#else
    Urb->DataPhy  = (typeof( Urb->DataPhy))  bdk_ptr_to_phys(Urb->Data);
    Len = Urb->DataLen;
#endif
  }

  //
  // Construct the TRB
  //
  XhcSyncTrsRing (Xhc, EPRing);
  Urb->TrbStart = EPRing->RingEnqueue;
  switch (EPType) {
    case ED_CONTROL_BIDIR:
      //
      // For control transfer, create SETUP_STAGE_TRB first.
      //
      TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
      TrbStart->TrbCtrSetup.bmRequestType = Urb->Request->RequestType;
      TrbStart->TrbCtrSetup.bRequest      = Urb->Request->Request;
      TrbStart->TrbCtrSetup.wValue        = Urb->Request->Value;
      TrbStart->TrbCtrSetup.wIndex        = Urb->Request->Index;
      TrbStart->TrbCtrSetup.wLength       = Urb->Request->Length;
      TrbStart->TrbCtrSetup.Length        = 8;
      TrbStart->TrbCtrSetup.IntTarget     = 0;
      TrbStart->TrbCtrSetup.IOC           = 1;
      TrbStart->TrbCtrSetup.IDT           = 1;
      TrbStart->TrbCtrSetup.Type          = TRB_TYPE_SETUP_STAGE;
      if (Urb->Ep.Direction == EfiUsbDataIn) {
        TrbStart->TrbCtrSetup.TRT = 3;
      } else if (Urb->Ep.Direction == EfiUsbDataOut) {
        TrbStart->TrbCtrSetup.TRT = 2;
      } else {
        TrbStart->TrbCtrSetup.TRT = 0;
      }
      //
      // Update the cycle bit
      //
      TrbStart->TrbCtrSetup.CycleBit = EPRing->RingPCS & BIT0;
      Urb->TrbNum++;

      //
      // For control transfer, create DATA_STAGE_TRB.
      //
      if (Urb->DataLen > 0) {
        XhcSyncTrsRing (Xhc, EPRing);
        TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
        TrbStart->TrbCtrData.TRBPtrLo  = XHC_LOW_32BIT(Urb->DataPhy);
        TrbStart->TrbCtrData.TRBPtrHi  = XHC_HIGH_32BIT(Urb->DataPhy);
        TrbStart->TrbCtrData.Length    = (UINT32) Urb->DataLen;
        TrbStart->TrbCtrData.TDSize    = 0;
        TrbStart->TrbCtrData.IntTarget = 0;
        TrbStart->TrbCtrData.ISP       = 1;
        TrbStart->TrbCtrData.IOC       = 1;
        TrbStart->TrbCtrData.IDT       = 0;
        TrbStart->TrbCtrData.CH        = 0;
        TrbStart->TrbCtrData.Type      = TRB_TYPE_DATA_STAGE;
        if (Urb->Ep.Direction == EfiUsbDataIn) {
          TrbStart->TrbCtrData.DIR = 1;
        } else if (Urb->Ep.Direction == EfiUsbDataOut) {
          TrbStart->TrbCtrData.DIR = 0;
        } else {
          TrbStart->TrbCtrData.DIR = 0;
        }
        //
        // Update the cycle bit
        //
        TrbStart->TrbCtrData.CycleBit = EPRing->RingPCS & BIT0;
        Urb->TrbNum++;
      }
      //
      // For control transfer, create STATUS_STAGE_TRB.
      // Get the pointer to next TRB for status stage use
      //
      XhcSyncTrsRing (Xhc, EPRing);
      TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
      TrbStart->TrbCtrStatus.IntTarget = 0;
      TrbStart->TrbCtrStatus.IOC       = 1;
      TrbStart->TrbCtrStatus.CH        = 0;
      TrbStart->TrbCtrStatus.Type      = TRB_TYPE_STATUS_STAGE;
      if (Urb->Ep.Direction == EfiUsbDataIn) {
        TrbStart->TrbCtrStatus.DIR = 0;
      } else if (Urb->Ep.Direction == EfiUsbDataOut) {
        TrbStart->TrbCtrStatus.DIR = 1;
      } else {
        TrbStart->TrbCtrStatus.DIR = 0;
      }
      //
      // Update the cycle bit
      //
      TrbStart->TrbCtrStatus.CycleBit = EPRing->RingPCS & BIT0;
      //
      // Update the enqueue pointer
      //
      XhcSyncTrsRing (Xhc, EPRing);
      Urb->TrbNum++;
      Urb->TrbEnd = (TRB_TEMPLATE *)(UINTN)TrbStart;

      break;

    case ED_BULK_OUT:
    case ED_BULK_IN:
      TotalLen = 0;
      Len      = 0;
      TrbNum   = 0;
      TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
      while (TotalLen < Urb->DataLen) {
        if ((TotalLen + 0x10000) >= Urb->DataLen) {
          Len = Urb->DataLen - TotalLen;
        } else {
          Len = 0x10000;
        }
        TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
        TrbStart->TrbNormal.TRBPtrLo  = XHC_LOW_32BIT((UINT8 *) Urb->DataPhy + TotalLen);
        TrbStart->TrbNormal.TRBPtrHi  = XHC_HIGH_32BIT((UINT8 *) Urb->DataPhy + TotalLen);
        TrbStart->TrbNormal.Length    = (UINT32) Len;
        TrbStart->TrbNormal.TDSize    = 0;
        TrbStart->TrbNormal.IntTarget = 0;
        TrbStart->TrbNormal.ISP       = 1;
        TrbStart->TrbNormal.IOC       = 1;
        TrbStart->TrbNormal.Type      = TRB_TYPE_NORMAL;
        //
        // Update the cycle bit
        //
        TrbStart->TrbNormal.CycleBit = EPRing->RingPCS & BIT0;

        XhcSyncTrsRing (Xhc, EPRing);
        TrbNum++;
        TotalLen += Len;
      }

      Urb->TrbNum = TrbNum;
      Urb->TrbEnd = (TRB_TEMPLATE *)(UINTN)TrbStart;
      break;

    case ED_INTERRUPT_OUT:
    case ED_INTERRUPT_IN:
      TotalLen = 0;
      Len      = 0;
      TrbNum   = 0;
      TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
      while (TotalLen < Urb->DataLen) {
        if ((TotalLen + 0x10000) >= Urb->DataLen) {
          Len = Urb->DataLen - TotalLen;
        } else {
          Len = 0x10000;
        }
        TrbStart = (TRB *)(UINTN)EPRing->RingEnqueue;
        TrbStart->TrbNormal.TRBPtrLo  = XHC_LOW_32BIT((UINT8 *) Urb->DataPhy + TotalLen);
        TrbStart->TrbNormal.TRBPtrHi  = XHC_HIGH_32BIT((UINT8 *) Urb->DataPhy + TotalLen);
        TrbStart->TrbNormal.Length    = (UINT32) Len;
        TrbStart->TrbNormal.TDSize    = 0;
        TrbStart->TrbNormal.IntTarget = 0;
        TrbStart->TrbNormal.ISP       = 1;
        TrbStart->TrbNormal.IOC       = 1;
        TrbStart->TrbNormal.Type      = TRB_TYPE_NORMAL;
        //
        // Update the cycle bit
        //
        TrbStart->TrbNormal.CycleBit = EPRing->RingPCS & BIT0;

        XhcSyncTrsRing (Xhc, EPRing);
        TrbNum++;
        TotalLen += Len;
      }

      Urb->TrbNum = TrbNum;
      Urb->TrbEnd = (TRB_TEMPLATE *)(UINTN)TrbStart;
      break;

    default:
      DEBUG ((EFI_D_INFO, "Not supported EPType 0x%x!\n",EPType));
      ASSERT (FALSE);
      break;
  }

  return EFI_SUCCESS;
}

//------ end of command execution
/**
  Synchronize the specified event ring to update the enqueue and dequeue pointer.

  @param  Xhc         The XHCI Instance.
  @param  EvtRing     The event ring to sync.

  @retval EFI_SUCCESS The event ring is synchronized successfully.

**/
EFI_STATUS
EFIAPI
XhcSyncEventRing (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN EVENT_RING           *EvtRing
  )
{
  UINTN               Index;
  TRB_TEMPLATE        *EvtTrb1;

  ASSERT (EvtRing != NULL);

  //
  // Calculate the EventRingEnqueue and EventRingCCS.
  // Note: only support single Segment
  //
  EvtTrb1 = EvtRing->EventRingDequeue;

  for (Index = 0; Index < EvtRing->TrbNumber; Index++) {
    if (EvtTrb1->CycleBit != EvtRing->EventRingCCS) {
      break;
    }

    EvtTrb1++;

    if ((UINTN)EvtTrb1 >= ((UINTN) EvtRing->EventRingSeg0 + sizeof (TRB_TEMPLATE) * EvtRing->TrbNumber)) {
      EvtTrb1 = EvtRing->EventRingSeg0;
      EvtRing->EventRingCCS = (EvtRing->EventRingCCS) ? 0 : 1;
    }
  }

  if (Index < EvtRing->TrbNumber) {
    EvtRing->EventRingEnqueue = EvtTrb1;
  } else {
    ASSERT (FALSE);
  }

  return EFI_SUCCESS;
}

/**
  Synchronize the specified transfer ring to update the enqueue and dequeue pointer.

  @param  Xhc         The XHCI Instance.
  @param  TrsRing     The transfer ring to sync.

  @retval EFI_SUCCESS The transfer ring is synchronized successfully.

**/
EFI_STATUS
EFIAPI
XhcSyncTrsRing (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN TRANSFER_RING        *TrsRing
  )
{
  UINTN               Index;
  TRB_TEMPLATE        *TrsTrb;

  ASSERT (TrsRing != NULL);
  //
  // Calculate the latest RingEnqueue and RingPCS
  //
  TrsTrb = TrsRing->RingEnqueue;
  ASSERT (TrsTrb != NULL);

  for (Index = 0; Index < TrsRing->TrbNumber; Index++) {
    if (TrsTrb->CycleBit != (TrsRing->RingPCS & BIT0)) {
      break;
    }
    TrsTrb++;
    if ((UINT8) TrsTrb->Type == TRB_TYPE_LINK) {
      ASSERT (((LINK_TRB*)TrsTrb)->TC != 0);
      //
      // set cycle bit in Link TRB as normal
      //
      ((LINK_TRB*)TrsTrb)->CycleBit = TrsRing->RingPCS & BIT0;
      //
      // Toggle PCS maintained by software
      //
      TrsRing->RingPCS = (TrsRing->RingPCS & BIT0) ? 0 : 1;
      TrsTrb = (TRB_TEMPLATE *) TrsRing->RingSeg0;  // Use host address
    }
  }

  ASSERT (Index != TrsRing->TrbNumber);

  if (TrsTrb != TrsRing->RingEnqueue) {
    TrsRing->RingEnqueue = TrsTrb;
  }

  //
  // Clear the Trb context for enqueue, but reserve the PCS bit
  //
  TrsTrb->Parameter1 = 0;
  TrsTrb->Parameter2 = 0;
  TrsTrb->Status     = 0;
  TrsTrb->RsvdZ1     = 0;
  TrsTrb->Type       = 0;
  TrsTrb->Control    = 0;

  return EFI_SUCCESS;
}

/**
  Check if there is a new generated event.

  @param  Xhc           The XHCI Instance.
  @param  EvtRing       The event ring to check.
  @param  NewEvtTrb     The new event TRB found.

  @retval EFI_SUCCESS   Found a new event TRB at the event ring.
  @retval EFI_NOT_READY The event ring has no new event.

**/
EFI_STATUS
EFIAPI
XhcCheckNewEvent (
  IN  USB_XHCI_INSTANCE       *Xhc,
  IN  EVENT_RING              *EvtRing,
  OUT TRB_TEMPLATE            **NewEvtTrb
  )
{
  ASSERT (EvtRing != NULL);

  *NewEvtTrb = EvtRing->EventRingDequeue;

  if (EvtRing->EventRingDequeue == EvtRing->EventRingEnqueue) {
    return EFI_NOT_READY;
  }

  EvtRing->EventRingDequeue++;
  //
  // If the dequeue pointer is beyond the ring, then roll-back it to the beginning of the ring.
  //
  if ((UINTN)EvtRing->EventRingDequeue >= ((UINTN) EvtRing->EventRingSeg0 + sizeof (TRB_TEMPLATE) * EvtRing->TrbNumber)) {
    EvtRing->EventRingDequeue = EvtRing->EventRingSeg0;
  }

  return EFI_SUCCESS;
}

/**
  Ring the door bell to notify XHCI there is a transaction to be executed.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id of the target device.
  @param  Dci           The device context index of the target slot or endpoint.

  @retval EFI_SUCCESS   Successfully ring the door bell.

**/
EFI_STATUS
XhcRingDoorBell (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT8                SlotId,
  IN UINT8                Dci
  )
{
  if (0 == SlotId) Dci = 0;
  XhcWriteDoorBellReg (Xhc, SlotId * sizeof (UINT32), Dci);
  return EFI_SUCCESS;
}

//------ end of helpers
/**
  Check the URB's execution result and update the URB's
  result accordingly.

  @param  Xhc             The XHCI Instance.
  @param  Urb             The URB to check result.

  @return Whether the result of URB transfer is finialized.

**/
BOOLEAN
XhcCheckUrbResult (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  URB                 *Urb
  )
{
  EVT_TRB_TRANSFER        *EvtTrb;
  TRB_TEMPLATE            *TRBPtr;
  unsigned                Index;
  UINT8                   TRBType;
  EFI_STATUS              Status;
  URB                     *AsyncUrb;
  URB                     *CheckedUrb;
#if defined(OCTEONTX_NOT_USED)
  UINT64                  XhcDequeue;
  UINT32                  High;
  UINT32                  Low;
  EFI_PHYSICAL_ADDRESS    PhyAddr;
#else
  uint64_t    		PhyAddr;
#endif
  ASSERT ((Xhc != NULL) && (Urb != NULL));

  Status   = EFI_SUCCESS;
  AsyncUrb = NULL;

  if (Urb->Finished) {
    goto EXIT;
  }

  EvtTrb = NULL;

  if (/*XhcIsHalt (Xhc) || cvmXhcIsSysError (Xhc)*/bdk_unlikely(cvmXhcNotOK(Xhc))) {
    Urb->Result |= EFI_USB_ERR_SYSTEM;
    goto EXIT;
  }

  //
  // Traverse the event ring to find out all new events from the previous check.
  //
  XhcSyncEventRing (Xhc, &Xhc->EventRing);
  for (Index = 0; Index < Xhc->EventRing.TrbNumber; Index++) {
    Status = XhcCheckNewEvent (Xhc, &Xhc->EventRing, ((TRB_TEMPLATE **)&EvtTrb));
    if (Status == EFI_NOT_READY) {
      //
      // All new events are handled, return directly.
      //
      goto EXIT;
    }

    //
    // Only handle COMMAND_COMPLETETION_EVENT and TRANSFER_EVENT.
    //
    if ((EvtTrb->Type != TRB_TYPE_COMMAND_COMPLT_EVENT) && (EvtTrb->Type != TRB_TYPE_TRANS_EVENT)) {
      continue;
    }

    //
    // Need convert pci device address to host address
    //
#if defined(OCTEONTX_NOT_USED)
    PhyAddr = (EFI_PHYSICAL_ADDRESS)(EvtTrb->TRBPtrLo | LShiftU64 ((UINT64) EvtTrb->TRBPtrHi, 32));
    TRBPtr = (TRB_TEMPLATE *)(UINTN) UsbHcGetHostAddrForPciAddr (Xhc->MemPool, (VOID *)(UINTN) PhyAddr, sizeof (TRB_TEMPLATE));
#else
    PhyAddr = ((typeof(PhyAddr))EvtTrb->TRBPtrLo) | (( ((typeof(PhyAddr))EvtTrb->TRBPtrHi)) <<32);
    TRBPtr = bdk_phys_to_ptr(PhyAddr);
#endif

    //
    // Update the status of Urb according to the finished event regardless of whether
    // the urb is current checked one or in the XHCI's async transfer list.
    // This way is used to avoid that those completed async transfer events don't get
    // handled in time and are flushed by newer coming events.
    //
    if (IsTransferRingTrb (TRBPtr, Urb)) {
      CheckedUrb = Urb;
    } else if (IsAsyncIntTrb (Xhc, TRBPtr, &AsyncUrb)) {
      CheckedUrb = AsyncUrb;
    } else {
      continue;
    }

    switch (EvtTrb->Completecode) {
      case TRB_COMPLETION_STALL_ERROR:
        CheckedUrb->Result  |= EFI_USB_ERR_STALL;
        CheckedUrb->Finished = TRUE;
        DEBUG ((EFI_D_WARN, "STALL_ERROR! Completecode = %x\n",EvtTrb->Completecode));
        goto EXIT;

      case TRB_COMPLETION_BABBLE_ERROR:
        CheckedUrb->Result  |= EFI_USB_ERR_BABBLE;
        CheckedUrb->Finished = TRUE;
        DEBUG ((EFI_D_ERROR, "BABBLE_ERROR! Completecode = %x\n",EvtTrb->Completecode));
        goto EXIT;

      case TRB_COMPLETION_DATA_BUFFER_ERROR:
        CheckedUrb->Result  |= EFI_USB_ERR_BUFFER;
        CheckedUrb->Finished = TRUE;
        DEBUG ((EFI_D_ERROR, "ERR_BUFFER! Completecode = %x\n",EvtTrb->Completecode));
        goto EXIT;

      case TRB_COMPLETION_USB_TRANSACTION_ERROR:
        CheckedUrb->Result  |= EFI_USB_ERR_TIMEOUT;
        CheckedUrb->Finished = TRUE;
        DEBUG ((EFI_D_ERROR, "TRANSACTION_ERROR! Completecode = %x\n",EvtTrb->Completecode));
        goto EXIT;

      case TRB_COMPLETION_SHORT_PACKET:
      case TRB_COMPLETION_SUCCESS:
        TRBType = (UINT8) (TRBPtr->Type);
        if ((TRBType == TRB_TYPE_DATA_STAGE) ||
            (TRBType == TRB_TYPE_NORMAL) ||
            (TRBType == TRB_TYPE_ISOCH)) {
          CheckedUrb->Completed += (((TRANSFER_TRB_NORMAL*)TRBPtr)->Length - EvtTrb->Length);
        } else if(EvtTrb->Completecode == TRB_COMPLETION_SHORT_PACKET &&  Urb->Ep.Type != XHC_BULK_TRANSFER) {
            DEBUG ((EFI_D_WARN, "short packet happens! EpType %u TrbType %d\n",
                    (unsigned) Urb->Ep.Type, (unsigned) TRBPtr->Type  ));
        }
        break;

      default:
        DEBUG ((EFI_D_ERROR, "Transfer Default Error Occur! Completecode = 0x%x!\n",EvtTrb->Completecode));
        CheckedUrb->Result  |= EFI_USB_ERR_TIMEOUT;
        CheckedUrb->Finished = TRUE;
        goto EXIT;
    }

    //
    // Only check first and end Trb event address
    //
    if (TRBPtr == CheckedUrb->TrbStart) {
      CheckedUrb->StartDone = TRUE;
    }

    if (TRBPtr == CheckedUrb->TrbEnd) {
      CheckedUrb->EndDone = TRUE;
    }

    if (CheckedUrb->StartDone && CheckedUrb->EndDone) {
      CheckedUrb->Finished = TRUE;
      CheckedUrb->EvtTrb   = (TRB_TEMPLATE *)EvtTrb;
    }
  }

EXIT:

  //
  // Advance event ring to last available entry
  //
  // Some 3rd party XHCI external cards don't support single 64-bytes width register access,
  // So divide it to two 32-bytes width register access.
  //
#if defined(OCTEONTX_NOT_USED)
  Low  = XhcReadRuntimeReg (Xhc, XHC_ERDP_OFFSET);
  High = XhcReadRuntimeReg (Xhc, XHC_ERDP_OFFSET + 4);
  XhcDequeue = (UINT64)(LShiftU64((UINT64)High, 32) | Low);
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, Xhc->EventRing.EventRingDequeue, sizeof (TRB_TEMPLATE));
  if ((XhcDequeue & (~0x0F)) != (PhyAddr & (~0x0F))) {
    //
    // Some 3rd party XHCI external cards don't support single 64-bytes width register access,
    // So divide it to two 32-bytes width register access.
    //
    XhcWriteRuntimeReg (Xhc, XHC_ERDP_OFFSET, XHC_LOW_32BIT (PhyAddr) | BIT3);
    XhcWriteRuntimeReg (Xhc, XHC_ERDP_OFFSET + 4, XHC_HIGH_32BIT (PhyAddr));
  }
#else
  PhyAddr = (typeof(PhyAddr))bdk_ptr_to_phys(Xhc->EventRing.EventRingDequeue);
  uint64_t XhcDequeue = XhcReadRuntimeReg64(Xhc,XHC_ERDP_OFFSET);
  if ((XhcDequeue & (~0x0F)) != (PhyAddr & (~0x0F))) {
    XhcWriteRuntimeReg64 (Xhc, XHC_ERDP_OFFSET, (UINT64)PhyAddr | BIT3); /* uahc_erdp.s.ehb  */
  }
#endif

  return Urb->Finished;
}


/**
  Execute the transfer by polling the URB. This is a synchronous operation.

  @param  Xhc               The XHCI Instance.
  @param  CmdTransfer       The executed URB is for cmd transfer or not.
  @param  Urb               The URB to execute.
  @param  Timeout           The time to wait before abort, in millisecond.

  @return EFI_DEVICE_ERROR  The transfer failed due to transfer error.
  @return EFI_TIMEOUT       The transfer failed due to time out.
  @return EFI_SUCCESS       The transfer finished OK.

**/
EFI_STATUS
XhcExecTransfer (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  BOOLEAN             CmdTransfer,
  IN  URB                 *Urb,
  IN  UINTN               Timeout
  )
{
  EFI_STATUS              Status;
  UINT8                   SlotId;
  UINT8                   Dci;
  BOOLEAN                 Finished;

  if (CmdTransfer) {
    SlotId = 0;
    Dci    = 0;
  } else {
    SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
    if (SlotId == 0) {
      return EFI_DEVICE_ERROR;
    }
    Dci  = XhcEndpointToDci (Urb->Ep.EpAddr, (UINT8)(Urb->Ep.Direction));
    ASSERT (Dci < 32);
  }
#if defined(OCTEONTX_NOT_USED)
  UINTN                   Index;
  UINT64                  Loop;
  Status = EFI_SUCCESS;

  Loop   = (Timeout) ? Timeout * XHC_1_MILLISECOND : 0xFFFFFFFFU;

  XhcRingDoorBell (Xhc, SlotId, Dci);

  for (Index = 0; Index < Loop; Index++) {
    Finished = XhcCheckUrbResult (Xhc, Urb);
    if (Finished) {
      break;
    }
    gBS->Stall (XHC_1_MICROSECOND);
  }

  if (Index == Loop) {
    Urb->Result = EFI_USB_ERR_TIMEOUT;
    Status      = EFI_TIMEOUT;
  } else if (Urb->Result != EFI_USB_NOERROR) {
      Status      = EFI_DEVICE_ERROR;
  }
#else
  Status      = EFI_TIMEOUT;
  XhcRingDoorBell (Xhc, SlotId, Dci);

  uint64_t done = (Timeout) ? Timeout * XHC_1_MILLISECOND : 0xFFFFFFFFU;
  done += bdk_clock_get_count(BDK_CLOCK_TIME) + done * bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;

  do {
      Finished = XhcCheckUrbResult (Xhc, Urb);
      if (Finished) {
          Status = EFI_SUCCESS;
          break;
      }
      bdk_thread_yield();
  } while(bdk_clock_get_count(BDK_CLOCK_TIME) < done);

  if (EFI_TIMEOUT == Status) {
    Urb->Result = EFI_USB_ERR_TIMEOUT;
  } else if (Urb->Result != EFI_USB_NOERROR) {
      Status      = EFI_DEVICE_ERROR;
  }
#endif
  return Status;
}

//--------------------------------->
/*
 * Initialize host controller for schedule
 *
 * @param xhc The XHC instance
 *
 * @return Zero on success non-zero on failure
 */
int XhcInitSched(xhci_t* xhc)
{
    int rc = 0;

    xhc->MaxSlotsEn = xhc->hcsparams1.s.maxslots;
    // Program max device slots
    XhcWriteOpReg (xhc, XHC_CONFIG_OFFSET, xhc->MaxSlotsEn);

    // Program device context base array and set scratchpad
    unsigned entries = xhc->MaxSlotsEn + 1;
    void *dcbaa = memalign( CAVIUM_XHCI_ALIGN, entries * sizeof(uint64_t));
    if (NULL == dcbaa) {
        rc = -4;
        goto out;
    }
    bzero( dcbaa,  (entries) * sizeof(uint64_t));
#define _clean(x) if (x) {free(x); x = NULL;}
    unsigned MaxScratchPadBufs = xhc->hcsparams2.s.maxscratchpadbufs_l | ( xhc->hcsparams2.s.maxscratchpadbufs_h << 5);
    if (MaxScratchPadBufs) {

        uint64_t *ScratchBuf; // Temp variable for physical addresses
        unsigned sz = ((MaxScratchPadBufs * sizeof(uint64_t)) + CAVIUM_XHCI_ALIGN -1) / CAVIUM_XHCI_ALIGN ;
        ScratchBuf = (typeof(ScratchBuf)) memalign(CAVIUM_XHCI_ALIGN, sz * CAVIUM_XHCI_ALIGN);
        if (!ScratchBuf) {
            rc = -7;
            free(dcbaa);
            goto out;
        }
        bzero(ScratchBuf, sz * CAVIUM_XHCI_ALIGN);
        uint64_t ScratchPhy = bdk_ptr_to_phys(ScratchBuf);
        xhc->ScratchBuf = ScratchBuf;
        for (unsigned Index = 0; Index < MaxScratchPadBufs; Index++) {
            void *thisScratchPad = memalign(xhc->PageSize, xhc->PageSize);
            if (!thisScratchPad) {
                rc = -8;
                free(dcbaa);
                _clean(xhc->ScratchBuf);
                goto out;
            }
            bzero(thisScratchPad, xhc->PageSize);
            *ScratchBuf++ = bdk_ptr_to_phys(thisScratchPad);
        }
        *(uint64_t*)dcbaa = ScratchPhy;
        xhc->MaxScratchPadBufs = MaxScratchPadBufs;
    }
    xhc->DCBAA = dcbaa;
    XhcWriteOpReg64 (xhc, XHC_DCBAAP_OFFSET,bdk_ptr_to_phys(dcbaa) );

    //
    // Define the Command Ring Dequeue Pointer by programming the Command Ring Control Register
    // (5.4.5) with a 64-bit address pointing to the starting address of the first TRB of the Command Ring.
    // Note: The Command Ring is 64 byte aligned, so the low order 6 bits of the Command Ring Pointer shall
    // always be '0'.
    //
    if (( rc =CreateTransferRing (xhc, CMD_RING_TRB_NUMBER, &xhc->CmdRing)))
        goto out;
    uint64_t CmdRingPhy = bdk_ptr_to_phys(xhc->CmdRing.RingSeg0);
    CmdRingPhy |= XHC_CRCR_RCS;
    XhcWriteOpReg64 (xhc, XHC_CRCR_OFFSET, CmdRingPhy);
    //
    // Disable the 'interrupter enable' bit in USB_CMD
    // and clear IE & IP bit in all Interrupter X Management Registers.
    //
   XhcClearOpRegBit (xhc, XHC_USBCMD_OFFSET, XHC_USBCMD_INTE);
   for (unsigned Index = 0; Index <xhc->hcsparams1.s.maxintrs ; Index++) {
    XhcClearRuntimeRegBit (xhc, XHC_IMAN_OFFSET + (Index * 32), XHC_IMAN_IE);
    XhcSetRuntimeRegBit (xhc, XHC_IMAN_OFFSET + (Index * 32), XHC_IMAN_IP);
  }

    //
    // Allocate EventRing for Cmd, Ctrl, Bulk, Interrupt, AsynInterrupt transfer
    //
    rc = CreateEventRing (xhc, &xhc->EventRing);
    if (rc) {
        if (xhc->CmdRing.RingSeg0 != NULL) {
            free(xhc->CmdRing.RingSeg0);
            xhc->CmdRing.RingSeg0 = NULL;
        }
    }

out:
    if (rc)
        printf("%s exiting with rc %d\n", __FUNCTION__, rc);

    return rc;
}

/**
  Calculate the device context index by endpoint address and direction.

  @param  EpAddr              The target endpoint number.
  @param  Direction           The direction of the target endpoint.

  @return The device context index of endpoint.

**/
UINT8
XhcEndpointToDci (
  IN  UINT8                   EpAddr,
  IN  UINT8                   Direction
  )
{
  UINT8 Index;

  if (EpAddr == 0) {
    return 1;
  } else {
    Index = (UINT8) (2 * EpAddr);
    if (Direction == EfiUsbDataIn) {
      Index += 1;
    }
    return Index;
  }
}

#undef _clean

EFI_STATUS CreateTransferRing (
     USB_XHCI_INSTANCE     *xhc,
     unsigned              TrbNum,
     TRANSFER_RING         *TransferRing
    )
{
    void * buf;
    LINK_TRB              *EndTrb;
#if defined(OCTEONTX_NOT_USED)
  Buf = UsbHcAllocateMem (Xhc->MemPool, sizeof (TRB_TEMPLATE) * TrbNum);
  ASSERT (Buf != NULL);
  ASSERT (((UINTN) Buf & 0x3F) == 0);
  ZeroMem (Buf, sizeof (TRB_TEMPLATE) * TrbNum);
#else
    buf = memalign(BDK_CACHE_LINE_SIZE, sizeof (TRB_TEMPLATE) * TrbNum);
    if (NULL == buf) {
        return EFI_OUT_OF_RESOURCES;
    }
    bzero(buf,sizeof (TRB_TEMPLATE) * TrbNum);
#endif
    TransferRing->RingSeg0     = buf;
    TransferRing->TrbNumber    = TrbNum;
    TransferRing->RingEnqueue  = (TRB_TEMPLATE *) TransferRing->RingSeg0;
    TransferRing->RingDequeue  = (TRB_TEMPLATE *) TransferRing->RingSeg0;
    TransferRing->RingPCS      = 1;
    // 4.9.2 Transfer Ring Management
    // To form a ring (or circular queue) a Link TRB may be inserted at the end of a ring to
    // point to the first TRB in the ring.
    //
    EndTrb        = (LINK_TRB *) ((UINTN)buf + sizeof (TRB_TEMPLATE) * (TrbNum - 1));
    EndTrb->Type  = TRB_TYPE_LINK;
    uint64_t PhyAddr = bdk_ptr_to_phys(buf);
    EndTrb->PtrLo = XHC_LOW_32BIT (PhyAddr);
    EndTrb->PtrHi = XHC_HIGH_32BIT (PhyAddr);
    //
    // Toggle Cycle (TC). When set to '1', the xHC shall toggle its interpretation of the Cycle bit.
    //
    EndTrb->TC    = 1;
    //
    // Set Cycle bit as other TRB PCS init value
    //
    EndTrb->CycleBit = 0;
    return EFI_SUCCESS;
}

/**
  Create XHCI event ring.

  @param  xhc                 The XHCI Instance.
  @param  EventRing           The created event ring.

**/
EFI_STATUS
CreateEventRing (
  IN  USB_XHCI_INSTANCE     *xhc,
  OUT EVENT_RING            *EventRing
  )
{
    void *buf;
    EVENT_RING_SEG_TABLE_ENTRY  *ERSTBase;
#if defined(OCTEONTX_NOT_USED)
  Size = sizeof (TRB_TEMPLATE) * EVENT_RING_TRB_NUMBER;
  Buf = UsbHcAllocateMem (Xhc->MemPool, Size);
  ASSERT (Buf != NULL);
  ASSERT (((UINTN) Buf & 0x3F) == 0);
  ZeroMem (Buf, Size);
#else
    uint64_t size =  sizeof (TRB_TEMPLATE) * EVENT_RING_TRB_NUMBER;
    buf = memalign(BDK_CACHE_LINE_SIZE,size);
    if (NULL == buf) {
        return EFI_OUT_OF_RESOURCES;
    }
    bzero(buf,size);
#endif
    EventRing->EventRingSeg0    = buf;
    EventRing->TrbNumber        = EVENT_RING_TRB_NUMBER;
    EventRing->EventRingDequeue = (TRB_TEMPLATE *) EventRing->EventRingSeg0;
    EventRing->EventRingEnqueue = (TRB_TEMPLATE *) EventRing->EventRingSeg0;

    uint64_t  DequeuePhy = bdk_ptr_to_phys(buf);
    //
    // Software maintains an Event Ring Consumer Cycle State (CCS) bit, initializing it to '1'
    // and toggling it every time the Event Ring Dequeue Pointer wraps back to the beginning of the Event Ring.
    //
    EventRing->EventRingCCS = 1;

    size = sizeof (EVENT_RING_SEG_TABLE_ENTRY) * ERST_NUMBER;
    buf = memalign(BDK_CACHE_LINE_SIZE,size);
    if (NULL == buf) {
        free(EventRing->EventRingSeg0);
        return EFI_OUT_OF_RESOURCES;
    }
    bzero(buf,size);

    ERSTBase              = (EVENT_RING_SEG_TABLE_ENTRY *) buf;
    EventRing->ERSTBase   = ERSTBase;
    ERSTBase->PtrLo       = XHC_LOW_32BIT (DequeuePhy);
    ERSTBase->PtrHi       = XHC_HIGH_32BIT (DequeuePhy);
    ERSTBase->RingTrbSize = EVENT_RING_TRB_NUMBER;

    uint64_t  ERSTPhy = bdk_ptr_to_phys(ERSTBase);

    //
    // Program the Interrupter Event Ring Segment Table Size (ERSTSZ) register (5.5.2.3.1)
    //
    BDK_WMB;            // Settle memory writes before writing to IO space
    XhcWriteRuntimeReg (
        xhc,
        XHC_ERSTSZ_OFFSET,
        ERST_NUMBER
        );
    //
    // Program the Interrupter Event Ring Dequeue Pointer (ERDP) register (5.5.2.3.3)
    //
    XhcWriteRuntimeReg64 (
        xhc,
        XHC_ERDP_OFFSET,
        DequeuePhy
        );
    //
    // Program the Interrupter Event Ring Segment Table Base Address (ERSTBA) register(5.5.2.3.2)
    //
    XhcWriteRuntimeReg64 (
        xhc,
        XHC_ERSTBA_OFFSET,
        ERSTPhy
        );
    //
    // Need set IMAN IE bit to enble the ring interrupt
    //
    XhcSetRuntimeRegBit (xhc, XHC_IMAN_OFFSET, XHC_IMAN_IE);

    return EFI_SUCCESS;
}

/**
  Find out the slot id according to the device's route string.

  @param  xhc             The XHCI Instance.
  @param  RouteString     The route string described the device location.

  @return The slot id used by the device.

**/
UINT8
XhcRouteStringToSlotId (
  USB_XHCI_INSTANCE  *xhc,
  USB_DEV_ROUTE      RouteString
  )
{
  unsigned Index;

  for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
    if (xhc->UsbDevContext[Index + 1].Enabled &&
        (xhc->UsbDevContext[Index + 1].SlotId != 0) &&
        (xhc->UsbDevContext[Index + 1].RouteString.Dword == RouteString.Dword)) {
        return xhc->UsbDevContext[Index + 1].SlotId;
    }
  }
  return 0;
}

/**
  Find out the actual device address according to the requested device address from UsbBus.

  @param  Xhc             The XHCI Instance.
  @param  BusDevAddr      The requested device address by UsbBus upper driver.

  @return The actual device address assigned to the device.

**/
UINT8
XhcBusDevAddrToSlotId (
  IN  USB_XHCI_INSTANCE  *Xhc,
  IN  UINT8              BusDevAddr
  )
{
  unsigned  Index;

  for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
    if (Xhc->UsbDevContext[Index + 1].Enabled &&
        (Xhc->UsbDevContext[Index + 1].SlotId != 0) &&
        (Xhc->UsbDevContext[Index + 1].BusDevAddr == BusDevAddr)) {
        return Xhc->UsbDevContext[Index + 1].SlotId;
    }
  }
  return 0;
}

/**
  Disable the specified device slot.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be disabled.

  @retval EFI_SUCCESS   Successfully disable the device slot.

**/
static
EFI_STATUS
XhcDisableSlotCmd (
  IN USB_XHCI_INSTANCE         *Xhc,
  IN UINT8                     SlotId
  )
{
  EFI_STATUS            Status;
  TRB_TEMPLATE          *EvtTrb;
  CMD_TRB_DISABLE_SLOT  CmdTrbDisSlot;
  UINT8                 Index;
  VOID                  *RingSeg;

  //
  // Disable the device slots occupied by these devices on its downstream ports.
  // Entry 0 is reserved.
  //
  for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
    if (!Xhc->UsbDevContext[Index + 1].Enabled ||
        (Xhc->UsbDevContext[Index + 1].SlotId == 0) ||
        (Xhc->UsbDevContext[Index + 1].ParentRouteString.Dword != Xhc->UsbDevContext[SlotId].RouteString.Dword)) {
      continue;
    }

    Status = XhcDisableSlotCmd (Xhc, Xhc->UsbDevContext[Index + 1].SlotId);

    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "failed to disable child, ignore error\n"));
      Xhc->UsbDevContext[Index + 1].SlotId = 0;
    }
  }

  //
  // Construct the disable slot command
  //
  DEBUG ((EFI_D_INFO, "Disable device slot %d!\n", SlotId));

  ZeroMem (&CmdTrbDisSlot, sizeof (CmdTrbDisSlot));
  CmdTrbDisSlot.CycleBit = 1;
  CmdTrbDisSlot.Type     = TRB_TYPE_DIS_SLOT;
  CmdTrbDisSlot.SlotId   = SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbDisSlot,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Disable Slot Command Failed, Status = %d\n", (int) Status));
    return Status;
  }
  //
  // Free the slot's device context entry
  //
  Xhc->DCBAA[SlotId] = 0;

  //
  // Free the slot related data structure
  //
  for (Index = 0; Index < 31; Index++) {
    if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index] != NULL) {
      RingSeg = ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index])->RingSeg0;
      if (RingSeg != NULL) {
#if defined(OCTEONTX_NOT_USED)
        UsbHcFreeMem (Xhc->MemPool, RingSeg, sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER);
#else
          free(RingSeg);
#endif
      }
      FreePool (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index]);
      Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index] = NULL;
    }
  }
  if (Xhc->UsbDevContext[SlotId].ConfDesc) {
      for (Index = 0; Index < Xhc->UsbDevContext[SlotId].DevDesc.NumConfigurations; Index++) {
          if (Xhc->UsbDevContext[SlotId].ConfDesc[Index] != NULL) {
              FreePool (Xhc->UsbDevContext[SlotId].ConfDesc[Index]);
          }
      }
      free(Xhc->UsbDevContext[SlotId].ConfDesc);
      Xhc->UsbDevContext[SlotId].ConfDesc = NULL;
  }
  if (Xhc->UsbDevContext[SlotId].ActiveAlternateSetting != NULL) {
    FreePool (Xhc->UsbDevContext[SlotId].ActiveAlternateSetting);
  }
  if (Xhc->UsbDevContext[SlotId].InputContext != NULL) {
#if defined(OCTEONTX_NOT_USED)
    UsbHcFreeMem (Xhc->MemPool, Xhc->UsbDevContext[SlotId].InputContext, sizeof (INPUT_CONTEXT));
#else
      free( Xhc->UsbDevContext[SlotId].InputContext);
      Xhc->UsbDevContext[SlotId].InputContext = NULL;
#endif
  }

  if (Xhc->UsbDevContext[SlotId].OutputContext != NULL) {
#if defined(OCTEONTX_NOT_USED)
    UsbHcFreeMem (Xhc->MemPool, Xhc->UsbDevContext[SlotId].OutputContext, sizeof (DEVICE_CONTEXT));
#else
      free(Xhc->UsbDevContext[SlotId].OutputContext);
      Xhc->UsbDevContext[SlotId].OutputContext = NULL;
#endif
  }
  //
  // Doesn't zero the entry because XhcAsyncInterruptTransfer() may be invoked to remove the established
  // asynchronous interrupt pipe after the device is disabled. It needs the device address mapping info to
  // remove urb from XHCI's asynchronous transfer list.
  //
  Xhc->UsbDevContext[SlotId].Enabled = FALSE;
  Xhc->UsbDevContext[SlotId].SlotId  = 0;

  return Status;
}

#if !defined(OCTEONTX_NOT_USED)
/*
 * DisableSlotCmd and DisableSlotCMd64 are identical for us.
 * The only part different between those has to do with pci memory management, we are not concerned with.
 */
#else
/**
  Disable the specified device slot.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be disabled.

  @retval EFI_SUCCESS   Successfully disable the device slot.

**/
EFI_STATUS
XhcDisableSlotCmd64 (
  IN USB_XHCI_INSTANCE         *Xhc,
  IN UINT8                     SlotId
  )
{
  EFI_STATUS            Status;
  TRB_TEMPLATE          *EvtTrb;
  CMD_TRB_DISABLE_SLOT  CmdTrbDisSlot;
  UINT8                 Index;
  VOID                  *RingSeg;

  //
  // Disable the device slots occupied by these devices on its downstream ports.
  // Entry 0 is reserved.
  //
  for (Index = 0; Index < CAVIUM_XHCI_MAXSLOTS; Index++) {
    if (!Xhc->UsbDevContext[Index + 1].Enabled ||
        (Xhc->UsbDevContext[Index + 1].SlotId == 0) ||
        (Xhc->UsbDevContext[Index + 1].ParentRouteString.Dword != Xhc->UsbDevContext[SlotId].RouteString.Dword)) {
      continue;
    }

    Status = XhcDisableSlotCmd64 (Xhc, Xhc->UsbDevContext[Index + 1].SlotId);

    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "failed to disable child, ignore error\n"));
      Xhc->UsbDevContext[Index + 1].SlotId = 0;
    }
  }

  //
  // Construct the disable slot command
  //
  DEBUG ((EFI_D_INFO, "Disable device slot %d!\n", SlotId));

  ZeroMem (&CmdTrbDisSlot, sizeof (CmdTrbDisSlot));
  CmdTrbDisSlot.CycleBit = 1;
  CmdTrbDisSlot.Type     = TRB_TYPE_DIS_SLOT;
  CmdTrbDisSlot.SlotId   = SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbDisSlot,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Disable Slot Command Failed, Status = %d\n", (int) Status));
    return Status;
  }
  //
  // Free the slot's device context entry
  //
  Xhc->DCBAA[SlotId] = 0;

  //
  // Free the slot related data structure
  //
  for (Index = 0; Index < 31; Index++) {
    if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index] != NULL) {
      RingSeg = ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index])->RingSeg0;
      if (RingSeg != NULL) {
#if defined(OCTEONTX_NOT_USED)
        UsbHcFreeMem (Xhc->MemPool, RingSeg, sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER);
#else
        free(RingSeg);
#endif
      }
      FreePool (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index]);
      Xhc->UsbDevContext[SlotId].EndpointTransferRing[Index] = NULL;
    }
  }
  if (Xhc->UsbDevContext[SlotId].ConfDesc) {
      for (Index = 0; Index < Xhc->UsbDevContext[SlotId].DevDesc.NumConfigurations; Index++) {
          if (Xhc->UsbDevContext[SlotId].ConfDesc[Index] != NULL) {
              FreePool (Xhc->UsbDevContext[SlotId].ConfDesc[Index]);
          }
      }
      free(Xhc->UsbDevContext[SlotId].ConfDesc);
      Xhc->UsbDevContext[SlotId].ConfDesc = NULL;
  }
  if (Xhc->UsbDevContext[SlotId].ActiveAlternateSetting != NULL) {
    FreePool (Xhc->UsbDevContext[SlotId].ActiveAlternateSetting);
  }
  if (Xhc->UsbDevContext[SlotId].InputContext != NULL) {
#if defined(OCTEONTX_NOT_USED)
    UsbHcFreeMem (Xhc->MemPool, Xhc->UsbDevContext[SlotId].InputContext, sizeof (INPUT_CONTEXT_64));
#else
      free( Xhc->UsbDevContext[SlotId].InputContext);
      Xhc->UsbDevContext[SlotId].InputContext = NULL;
#endif
  }

  if (Xhc->UsbDevContext[SlotId].OutputContext != NULL) {
#if defined(OCTEONTX_NOT_USED)
      UsbHcFreeMem (Xhc->MemPool, Xhc->UsbDevContext[SlotId].OutputContext, sizeof (DEVICE_CONTEXT_64));
#else
      free( Xhc->UsbDevContext[SlotId].OutputContext);
      Xhc->UsbDevContext[SlotId].OutputContext = NULL;
#endif
  }
  //
  // Doesn't zero the entry because XhcAsyncInterruptTransfer() may be invoked to remove the established
  // asynchronous interrupt pipe after the device is disabled. It needs the device address mapping info to
  // remove urb from XHCI's asynchronous transfer list.
  //
  Xhc->UsbDevContext[SlotId].Enabled = FALSE;
  Xhc->UsbDevContext[SlotId].SlotId  = 0;

  return Status;
}
#endif
#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Assign and initialize the device slot for a new device.

  @param  Xhc                 The XHCI Instance.
  @param  ParentRouteChart    The route string pointed to the parent device.
  @param  ParentPort          The port at which the device is located.
  @param  RouteChart          The route string pointed to the device.
  @param  DeviceSpeed         The device speed.

  @retval EFI_SUCCESS   Successfully assign a slot to the device and assign an address to it.

**/
static
EFI_STATUS
EFIAPI
XhcInitializeDeviceSlot (
  IN  USB_XHCI_INSTANCE         *Xhc,
  IN  USB_DEV_ROUTE             ParentRouteChart,
  IN  UINT16                    ParentPort,
  IN  USB_DEV_ROUTE             RouteChart,
  IN  UINT8                     DeviceSpeed
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT               *InputContext;
  DEVICE_CONTEXT              *OutputContext;
  TRANSFER_RING               *EndpointTransferRing;
  CMD_TRB_ADDRESS_DEVICE      CmdTrbAddr;
  UINT8                       DeviceAddress;
  CMD_TRB_ENABLE_SLOT         CmdTrb;
  UINT8                       SlotId;
  UINT8                       ParentSlotId;
  DEVICE_CONTEXT              *ParentDeviceContext;
#if defined(OCTEONTX_NOT_USED)
  EFI_PHYSICAL_ADDRESS        PhyAddr;
#else
  uint64_t                    PhyAddr;
#endif

  ZeroMem (&CmdTrb, sizeof (CMD_TRB_ENABLE_SLOT));
  CmdTrb.CycleBit = 1;
  CmdTrb.Type     = TRB_TYPE_EN_SLOT;

  Status = XhcCmdTransfer (
              Xhc,
              (TRB_TEMPLATE *) (UINTN) &CmdTrb,
              XHC_GENERIC_TIMEOUT,
              (TRB_TEMPLATE **) (UINTN) &EvtTrb
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Enable Slot Failed, Status = %d\n", (int) Status));
    return Status;
  }
  ASSERT (EvtTrb->SlotId <= Xhc->MaxSlotsEn);
  DEBUG ((EFI_D_INFO, "Enable Slot Successfully, The Slot ID = 0x%x\n", EvtTrb->SlotId));
  SlotId = (UINT8)EvtTrb->SlotId;
  ASSERT (SlotId != 0);

  ZeroMem (&Xhc->UsbDevContext[SlotId], sizeof (USB_DEV_CONTEXT));
  Xhc->UsbDevContext[SlotId].Enabled                 = TRUE;
  Xhc->UsbDevContext[SlotId].SlotId                  = SlotId;
  Xhc->UsbDevContext[SlotId].RouteString.Dword       = RouteChart.Dword;
  Xhc->UsbDevContext[SlotId].ParentRouteString.Dword = ParentRouteChart.Dword;

  //
  // 4.3.3 Device Slot Initialization
  // 1) Allocate an Input Context data structure (6.2.5) and initialize all fields to '0'.
  //
#if defined(OCTEONTX_NOT_USED)
  InputContext = UsbHcAllocateMem (Xhc->MemPool, sizeof (INPUT_CONTEXT));
  ASSERT (InputContext != NULL);
  ASSERT (((UINTN) InputContext & 0x3F) == 0);
#else
  InputContext = memalign(0x40,sizeof (INPUT_CONTEXT));
  if ((NULL == InputContext) ||(((UINTN) InputContext & 0x3F) != 0))  {
      DEBUG ((EFI_D_ERROR, "Failed to allocate InputContext @%p %lu bytes\n", InputContext, sizeof(*InputContext)));
      return EFI_OUT_OF_RESOURCES;
  }
#endif

  ZeroMem (InputContext, sizeof (INPUT_CONTEXT));

  Xhc->UsbDevContext[SlotId].InputContext = (VOID *) InputContext;

  //
  // 2) Initialize the Input Control Context (6.2.5.1) of the Input Context by setting the A0 and A1
  //    flags to '1'. These flags indicate that the Slot Context and the Endpoint 0 Context of the Input
  //    Context are affected by the command.
  //
  InputContext->InputControlContext.Dword2 |= (BIT0 | BIT1);

  //
  // 3) Initialize the Input Slot Context data structure
  //
  InputContext->Slot.RouteString    = RouteChart.Route.RouteString;
  InputContext->Slot.Speed          = DeviceSpeed + 1;
  InputContext->Slot.ContextEntries = 1;
  InputContext->Slot.RootHubPortNum = RouteChart.Route.RootPortNum;

  if (RouteChart.Route.RouteString) {
    //
    // The device is behind of hub device.
    //
    ParentSlotId = XhcRouteStringToSlotId(Xhc, ParentRouteChart);
    ASSERT (ParentSlotId != 0);
    //
    //if the Full/Low device attached to a High Speed Hub, Init the TTPortNum and TTHubSlotId field of slot context
    //
    ParentDeviceContext = (DEVICE_CONTEXT *)Xhc->UsbDevContext[ParentSlotId].OutputContext;
    if ((ParentDeviceContext->Slot.TTPortNum == 0) &&
        (ParentDeviceContext->Slot.TTHubSlotId == 0)) {
      if ((ParentDeviceContext->Slot.Speed == (EFI_USB_SPEED_HIGH + 1)) && (DeviceSpeed < EFI_USB_SPEED_HIGH)) {
        //
        // Full/Low device attached to High speed hub port that isolates the high speed signaling
        // environment from Full/Low speed signaling environment for a device
        //
        InputContext->Slot.TTPortNum   = ParentPort;
        InputContext->Slot.TTHubSlotId = ParentSlotId;
      }
    } else {
      //
      // Inherit the TT parameters from parent device.
      //
      InputContext->Slot.TTPortNum   = ParentDeviceContext->Slot.TTPortNum;
      InputContext->Slot.TTHubSlotId = ParentDeviceContext->Slot.TTHubSlotId;
      //
      // If the device is a High speed device then down the speed to be the same as its parent Hub
      //
      if (DeviceSpeed == EFI_USB_SPEED_HIGH) {
        InputContext->Slot.Speed = ParentDeviceContext->Slot.Speed;
      }
    }
  }

  //
  // 4) Allocate and initialize the Transfer Ring for the Default Control Endpoint.
  //
  EndpointTransferRing = AllocateZeroPool (sizeof (TRANSFER_RING));
  Xhc->UsbDevContext[SlotId].EndpointTransferRing[0] = EndpointTransferRing;
  if (EFI_SUCCESS != CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])) {
      DEBUG ((EFI_D_ERROR, "Failed to create TransferRing for context"));
      return EFI_OUT_OF_RESOURCES;
  }
  //
  // 5) Initialize the Input default control Endpoint 0 Context (6.2.3).
  //
  InputContext->EP[0].EPType = ED_CONTROL_BIDIR;

  if (DeviceSpeed == EFI_USB_SPEED_SUPER) {
    InputContext->EP[0].MaxPacketSize = 512;
  } else if (DeviceSpeed == EFI_USB_SPEED_HIGH) {
    InputContext->EP[0].MaxPacketSize = 64;
  } else {
    InputContext->EP[0].MaxPacketSize = 8;
  }
  //
  // Initial value of Average TRB Length for Control endpoints would be 8B, Interrupt endpoints
  // 1KB, and Bulk and Isoch endpoints 3KB.
  //
  InputContext->EP[0].AverageTRBLength = 8;
  InputContext->EP[0].MaxBurstSize     = 0;
  InputContext->EP[0].Interval         = 0;
  InputContext->EP[0].MaxPStreams      = 0;
  InputContext->EP[0].Mult             = 0;
  InputContext->EP[0].CErr             = 3;

  //
  // Init the DCS(dequeue cycle state) as the transfer ring's CCS
  //
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (
              Xhc->MemPool,
              ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])->RingSeg0,
              sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER
              );
#else
  PhyAddr = bdk_ptr_to_phys( ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])->RingSeg0);
#endif
  InputContext->EP[0].PtrLo = XHC_LOW_32BIT (PhyAddr) | BIT0;
  InputContext->EP[0].PtrHi = XHC_HIGH_32BIT (PhyAddr);

  //
  // 6) Allocate the Output Device Context data structure (6.2.1) and initialize it to '0'.
  //
#if defined(OCTEONTX_NOT_USED)
  OutputContext = UsbHcAllocateMem (Xhc->MemPool, sizeof (DEVICE_CONTEXT));
  ASSERT (OutputContext != NULL);
  ASSERT (((UINTN) OutputContext & 0x3F) == 0);
#else
  OutputContext = memalign(0x40,  sizeof (DEVICE_CONTEXT));
  if ((NULL == OutputContext) ||(((UINTN) OutputContext & 0x3F) != 0))  {
      DEBUG ((EFI_D_ERROR, "Failed to allocate OutputContext @%p %lu bytes\n", OutputContext, sizeof(*OutputContext)));
      free(InputContext);
      return EFI_OUT_OF_RESOURCES;
  }
#endif
  ZeroMem (OutputContext, sizeof (DEVICE_CONTEXT));

  Xhc->UsbDevContext[SlotId].OutputContext = OutputContext;
  //
  // 7) Load the appropriate (Device Slot ID) entry in the Device Context Base Address Array (5.4.6) with
  //    a pointer to the Output Device Context data structure (6.2.1).
  //
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, OutputContext, sizeof (DEVICE_CONTEXT));
#else
  PhyAddr = bdk_ptr_to_phys(OutputContext);
#endif
  //
  // Fill DCBAA with PCI device address
  //
  Xhc->DCBAA[SlotId] = (UINT64) (UINTN) PhyAddr;

  //
  // 8) Issue an Address Device Command for the Device Slot, where the command points to the Input
  //    Context data structure described above.
  //
  // Delay 10ms to meet TRSTRCY delay requirement in usb 2.0 spec chapter 7.1.7.5 before sending SetAddress() request
  // to device.
  //
#if defined(OCTEONTX_NOT_USED)
  gBS->Stall (XHC_RESET_RECOVERY_DELAY);
#else
  bdk_wait_usec(XHC_RESET_RECOVERY_DELAY);
#endif
  ZeroMem (&CmdTrbAddr, sizeof (CmdTrbAddr));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, Xhc->UsbDevContext[SlotId].InputContext, sizeof (INPUT_CONTEXT));
#else
  PhyAddr = bdk_ptr_to_phys(Xhc->UsbDevContext[SlotId].InputContext);
#endif
  CmdTrbAddr.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbAddr.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbAddr.CycleBit = 1;
  CmdTrbAddr.Type     = TRB_TYPE_ADDRESS_DEV;
  CmdTrbAddr.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbAddr,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (!EFI_ERROR (Status)) {
    DeviceAddress = (UINT8) ((DEVICE_CONTEXT *) OutputContext)->Slot.DeviceAddress;
    DEBUG ((EFI_D_INFO, " Address %d assigned successfully\n", DeviceAddress));
    Xhc->UsbDevContext[SlotId].XhciDevAddr = DeviceAddress;
  }

  return Status;
}
#endif
/**
  Assign and initialize the device slot for a new device.

  @param  Xhc                 The XHCI Instance.
  @param  ParentRouteChart    The route string pointed to the parent device.
  @param  ParentPort          The port at which the device is located.
  @param  RouteChart          The route string pointed to the device.
  @param  DeviceSpeed         The device speed.

  @retval EFI_SUCCESS   Successfully assign a slot to the device and assign an address to it.

**/
static EFI_STATUS
EFIAPI
XhcInitializeDeviceSlot64 (
  IN  USB_XHCI_INSTANCE         *Xhc,
  IN  USB_DEV_ROUTE             ParentRouteChart,
  IN  UINT16                    ParentPort,
  IN  USB_DEV_ROUTE             RouteChart,
  IN  UINT8                     DeviceSpeed
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT_64            *InputContext;
  DEVICE_CONTEXT_64           *OutputContext;
  TRANSFER_RING               *EndpointTransferRing;
  CMD_TRB_ADDRESS_DEVICE      CmdTrbAddr;
  UINT8                       DeviceAddress;
  CMD_TRB_ENABLE_SLOT         CmdTrb;
  UINT8                       SlotId;
  UINT8                       ParentSlotId;
  DEVICE_CONTEXT_64           *ParentDeviceContext;
#if defined(OCTEONTX_NOT_USED)
  EFI_PHYSICAL_ADDRESS        PhyAddr;
#else
  uint64_t                    PhyAddr;
#endif
  ZeroMem (&CmdTrb, sizeof (CMD_TRB_ENABLE_SLOT));
  CmdTrb.CycleBit = 1;
  CmdTrb.Type     = TRB_TYPE_EN_SLOT;

  Status = XhcCmdTransfer (
              Xhc,
              (TRB_TEMPLATE *) (UINTN) &CmdTrb,
              XHC_GENERIC_TIMEOUT,
              (TRB_TEMPLATE **) (UINTN) &EvtTrb
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Enable Slot Failed, Status = %d\n", (int) Status));
    return Status;
  }
  ASSERT (EvtTrb->SlotId <= Xhc->MaxSlotsEn);
  DEBUG ((EFI_D_INFO, "Enable Slot Successfully, The Slot ID = 0x%x\n", EvtTrb->SlotId));
  SlotId = (UINT8)EvtTrb->SlotId;
  ASSERT (SlotId != 0);

  ZeroMem (&Xhc->UsbDevContext[SlotId], sizeof (USB_DEV_CONTEXT));
  Xhc->UsbDevContext[SlotId].Enabled                 = TRUE;
  Xhc->UsbDevContext[SlotId].SlotId                  = SlotId;
  Xhc->UsbDevContext[SlotId].RouteString.Dword       = RouteChart.Dword;
  Xhc->UsbDevContext[SlotId].ParentRouteString.Dword = ParentRouteChart.Dword;

  //
  // 4.3.3 Device Slot Initialization
  // 1) Allocate an Input Context data structure (6.2.5) and initialize all fields to '0'.
  //
#if defined(OCTEONTX_NOT_USED)
  InputContext = UsbHcAllocateMem (Xhc->MemPool, sizeof (INPUT_CONTEXT_64));
  ASSERT (InputContext != NULL);
  ASSERT (((UINTN) InputContext & 0x3F) == 0);
#else
  InputContext = memalign(0x40,sizeof (INPUT_CONTEXT_64));
  if ((NULL == InputContext) ||(((UINTN) InputContext & 0x3F) != 0))  {
      DEBUG ((EFI_D_ERROR, "failed to allocate InputContext @%p %lu bytes\n", InputContext, sizeof(*InputContext)));
      return EFI_OUT_OF_RESOURCES;
  }
#endif
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT_64));

  Xhc->UsbDevContext[SlotId].InputContext = (VOID *) InputContext;

  //
  // 2) Initialize the Input Control Context (6.2.5.1) of the Input Context by setting the A0 and A1
  //    flags to '1'. These flags indicate that the Slot Context and the Endpoint 0 Context of the Input
  //    Context are affected by the command.
  //
  InputContext->InputControlContext.Dword2 |= (BIT0 | BIT1);

  //
  // 3) Initialize the Input Slot Context data structure
  //
  InputContext->Slot.RouteString    = RouteChart.Route.RouteString;
  InputContext->Slot.Speed          = DeviceSpeed + 1;
  InputContext->Slot.ContextEntries = 1;
  InputContext->Slot.RootHubPortNum = RouteChart.Route.RootPortNum;

  if (RouteChart.Route.RouteString) {
    //
    // The device is behind of hub device.
    //
    ParentSlotId = XhcRouteStringToSlotId(Xhc, ParentRouteChart);
    ASSERT (ParentSlotId != 0);
    //
    //if the Full/Low device attached to a High Speed Hub, Init the TTPortNum and TTHubSlotId field of slot context
    //
    ParentDeviceContext = (DEVICE_CONTEXT_64 *)Xhc->UsbDevContext[ParentSlotId].OutputContext;
    if ((ParentDeviceContext->Slot.TTPortNum == 0) &&
        (ParentDeviceContext->Slot.TTHubSlotId == 0)) {
      if ((ParentDeviceContext->Slot.Speed == (EFI_USB_SPEED_HIGH + 1)) && (DeviceSpeed < EFI_USB_SPEED_HIGH)) {
        //
        // Full/Low device attached to High speed hub port that isolates the high speed signaling
        // environment from Full/Low speed signaling environment for a device
        //
        InputContext->Slot.TTPortNum   = ParentPort;
        InputContext->Slot.TTHubSlotId = ParentSlotId;
      }
    } else {
      //
      // Inherit the TT parameters from parent device.
      //
      InputContext->Slot.TTPortNum   = ParentDeviceContext->Slot.TTPortNum;
      InputContext->Slot.TTHubSlotId = ParentDeviceContext->Slot.TTHubSlotId;
      //
      // If the device is a High speed device then down the speed to be the same as its parent Hub
      //
      if (DeviceSpeed == EFI_USB_SPEED_HIGH) {
        InputContext->Slot.Speed = ParentDeviceContext->Slot.Speed;
      }
    }
  }

  //
  // 4) Allocate and initialize the Transfer Ring for the Default Control Endpoint.
  //
  EndpointTransferRing = AllocateZeroPool (sizeof (TRANSFER_RING));
  Xhc->UsbDevContext[SlotId].EndpointTransferRing[0] = EndpointTransferRing;
  if (EFI_SUCCESS != CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])) {
      DEBUG ((EFI_D_ERROR, "Failed to create TransferRing for context"));
      return EFI_OUT_OF_RESOURCES;
  }

  //
  // 5) Initialize the Input default control Endpoint 0 Context (6.2.3).
  //
  InputContext->EP[0].EPType = ED_CONTROL_BIDIR;

  if (DeviceSpeed == EFI_USB_SPEED_SUPER) {
    InputContext->EP[0].MaxPacketSize = 512;
  } else if (DeviceSpeed == EFI_USB_SPEED_HIGH) {
    InputContext->EP[0].MaxPacketSize = 64;
  } else {
    InputContext->EP[0].MaxPacketSize = 8;
  }
  //
  // Initial value of Average TRB Length for Control endpoints would be 8B, Interrupt endpoints
  // 1KB, and Bulk and Isoch endpoints 3KB.
  //
  InputContext->EP[0].AverageTRBLength = 8;
  InputContext->EP[0].MaxBurstSize     = 0;
  InputContext->EP[0].Interval         = 0;
  InputContext->EP[0].MaxPStreams      = 0;
  InputContext->EP[0].Mult             = 0;
  InputContext->EP[0].CErr             = 3;

  //
  // Init the DCS(dequeue cycle state) as the transfer ring's CCS
  //
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (
              Xhc->MemPool,
              ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])->RingSeg0,
              sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER
              );
#else
  PhyAddr = bdk_ptr_to_phys(
       ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[0])->RingSeg0
      );
#endif
  InputContext->EP[0].PtrLo = XHC_LOW_32BIT (PhyAddr) | BIT0;
  InputContext->EP[0].PtrHi = XHC_HIGH_32BIT (PhyAddr);

  //
  // 6) Allocate the Output Device Context data structure (6.2.1) and initialize it to '0'.
  //
#if defined(OCTEONTX_NOT_USED)
  OutputContext = UsbHcAllocateMem (Xhc->MemPool, sizeof (DEVICE_CONTEXT_64));
  ASSERT (OutputContext != NULL);
  ASSERT (((UINTN) OutputContext & 0x3F) == 0);
#else
  OutputContext = memalign(0x40, sizeof (DEVICE_CONTEXT_64));
  if ((NULL == OutputContext) ||(((UINTN) OutputContext & 0x3F) != 0))  {
      DEBUG ((EFI_D_ERROR, "Failed to allocate OutputContext @%p %lu bytes\n", OutputContext, sizeof(*OutputContext)));
      free(InputContext);
      return EFI_OUT_OF_RESOURCES;
  }
#endif
  ZeroMem (OutputContext, sizeof (DEVICE_CONTEXT_64));

  Xhc->UsbDevContext[SlotId].OutputContext = OutputContext;
  //
  // 7) Load the appropriate (Device Slot ID) entry in the Device Context Base Address Array (5.4.6) with
  //    a pointer to the Output Device Context data structure (6.2.1).
  //
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, OutputContext, sizeof (DEVICE_CONTEXT_64));
#else
  PhyAddr = bdk_ptr_to_phys(OutputContext);
#endif
  //
  // Fill DCBAA with PCI device address
  //
  Xhc->DCBAA[SlotId] = (UINT64) (UINTN) PhyAddr;

  //
  // 8) Issue an Address Device Command for the Device Slot, where the command points to the Input
  //    Context data structure described above.
  //
  // Delay 10ms to meet TRSTRCY delay requirement in usb 2.0 spec chapter 7.1.7.5 before sending SetAddress() request
  // to device.
  //
#if defined(OCTEONTX_NOT_USED)
  gBS->Stall (XHC_RESET_RECOVERY_DELAY);
#else
  bdk_wait_usec(XHC_RESET_RECOVERY_DELAY);
#endif
  ZeroMem (&CmdTrbAddr, sizeof (CmdTrbAddr));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, Xhc->UsbDevContext[SlotId].InputContext, sizeof (INPUT_CONTEXT_64));
#else
  PhyAddr = bdk_ptr_to_phys(Xhc->UsbDevContext[SlotId].InputContext);
#endif
  CmdTrbAddr.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbAddr.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbAddr.CycleBit = 1;
  CmdTrbAddr.Type     = TRB_TYPE_ADDRESS_DEV;
  CmdTrbAddr.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbAddr,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (!EFI_ERROR (Status)) {
    DeviceAddress = (UINT8) ((DEVICE_CONTEXT_64 *) OutputContext)->Slot.DeviceAddress;
    DEBUG ((EFI_D_INFO, "    Address %d assigned successfully\n", DeviceAddress));
    Xhc->UsbDevContext[SlotId].XhciDevAddr = DeviceAddress;
  } else {
    DEBUG ((EFI_D_ERROR, " AddressDevice command failed with status %lld\n", Status));
  }
  return Status;
}

//------------------------------------------------>


/**
  System software shall use a Reset Endpoint Command (section 4.11.4.7) to remove the Halted
  condition in the xHC. After the successful completion of the Reset Endpoint Command, the Endpoint
  Context is transitioned from the Halted to the Stopped state and the Transfer Ring of the endpoint is
  re-enabled. The next write to the Doorbell of the Endpoint will transition the Endpoint Context from the
  Stopped to the Running state.

  @param  Xhc                   The XHCI Instance.
  @param  Urb                   The urb which makes the endpoint halted.

  @retval EFI_SUCCESS           The recovery is successful.
  @retval Others                Failed to recovery halted endpoint.

**/
EFI_STATUS
EFIAPI
XhcRecoverHaltedEndpoint (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  URB                 *Urb
  )
{
  EFI_STATUS                  Status;
  UINT8                       Dci;
  UINT8                       SlotId;

  Status = EFI_SUCCESS;
  SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
  if (SlotId == 0) {
    return EFI_DEVICE_ERROR;
  }
  Dci = XhcEndpointToDci (Urb->Ep.EpAddr, (UINT8)(Urb->Ep.Direction));
  ASSERT (Dci < 32);

  DEBUG ((EFI_D_INFO, "Recovery Halted Slot = %x,Dci = %x\n", SlotId, Dci));

  //
  // 1) Send Reset endpoint command to transit from halt to stop state
  //
  Status = XhcResetEndpoint(Xhc, SlotId, Dci);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Reset Endpoint Failed, Status = %d\n", (int) Status));
    goto Done;
  }

  //
  // 2)Set dequeue pointer
  //
  Status = XhcSetTrDequeuePointer(Xhc, SlotId, Dci, Urb);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Set Dequeue Pointer Failed, Status = %d\n", (int) Status));
    goto Done;
  }

  //
  // 3)Ring the doorbell to transit from stop to active
  //
  XhcRingDoorBell (Xhc, SlotId, Dci);

Done:
  return Status;
}

/**
  System software shall use a Stop Endpoint Command (section 4.6.9) and the Set TR Dequeue Pointer
  Command (section 4.6.10) to remove the timed-out TDs from the xHC transfer ring. The next write to
  the Doorbell of the Endpoint will transition the Endpoint Context from the Stopped to the Running
  state.

  @param  Xhc                   The XHCI Instance.
  @param  Urb                   The urb which doesn't get completed in a specified timeout range.

  @retval EFI_SUCCESS           The dequeuing of the TDs is successful.
  @retval Others                Failed to stop the endpoint and dequeue the TDs.

**/
EFI_STATUS
EFIAPI
XhcDequeueTrbFromEndpoint (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  URB                 *Urb
  )
{
  EFI_STATUS                  Status;
  UINT8                       Dci;
  UINT8                       SlotId;

  Status = EFI_SUCCESS;
  SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
  if (SlotId == 0) {
    return EFI_DEVICE_ERROR;
  }
  Dci = XhcEndpointToDci (Urb->Ep.EpAddr, (UINT8)(Urb->Ep.Direction));
  ASSERT (Dci < 32);

  DEBUG ((EFI_D_INFO, "Stop Slot = %x,Dci = %x\n", SlotId, Dci));

  //
  // 1) Send Stop endpoint command to stop xHC from executing of the TDs on the endpoint
  //
  Status = XhcStopEndpoint(Xhc, SlotId, Dci);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Stop Endpoint Failed, Status = %d\n", (int) Status));
    goto Done;
  }

  //
  // 2)Set dequeue pointer
  //
  Status = XhcSetTrDequeuePointer(Xhc, SlotId, Dci, Urb);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Set Transfer Ring Dequeue Pointer Failed, Status = %d\n", (int) Status));
    goto Done;
  }

  //
  // 3)Ring the doorbell to transit from stop to active
  //
  XhcRingDoorBell (Xhc, SlotId, Dci);

Done:
  return Status;
}

/**
  Free XHCI event ring.

  @param  Xhc                 The XHCI Instance.
  @param  EventRing           The event ring to be freed.

**/
static
EFI_STATUS
EFIAPI
XhcFreeEventRing (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  EVENT_RING          *EventRing
)
{
  if(EventRing->EventRingSeg0 == NULL) {
    return EFI_SUCCESS;
  }
#if defined(OCTEONTX_NOT_USED)
  //
  // Free EventRing Segment 0
  //
  UsbHcFreeMem (Xhc->MemPool, EventRing->EventRingSeg0, sizeof (TRB_TEMPLATE) * EVENT_RING_TRB_NUMBER);

  //
  // Free ESRT table
  //
  UsbHcFreeMem (Xhc->MemPool, EventRing->ERSTBase, sizeof (EVENT_RING_SEG_TABLE_ENTRY) * ERST_NUMBER);
#else
  free(EventRing->EventRingSeg0);
  free( EventRing->ERSTBase);
#endif
  return EFI_SUCCESS;
}

/**
  Free the resource allocated at initializing schedule.

  @param  Xhc        The XHCI Instance.

**/
VOID
XhcFreeSched (
  IN USB_XHCI_INSTANCE    *Xhc
  )
{
     unsigned MaxScratchPadBufs = Xhc->MaxScratchPadBufs;
    if (MaxScratchPadBufs && Xhc->ScratchBuf) {
        for( unsigned Index = 0; Index < MaxScratchPadBufs; Index++) {
            free(
                bdk_phys_to_ptr(Xhc->ScratchBuf[Index])
                );
        }
        free(Xhc->ScratchBuf);
        Xhc->ScratchBuf = NULL;
    }
    // Clean cmd ring
    if (Xhc->CmdRing.RingSeg0 != NULL) {
        free(Xhc->CmdRing.RingSeg0);
        Xhc->CmdRing.RingSeg0 = NULL;
    }
    // Clean Event ring
    XhcFreeEventRing (Xhc,&Xhc->EventRing);

    if(Xhc->DCBAA) {
        free(Xhc->DCBAA);
        Xhc->DCBAA = NULL;
    }
}



/**
  Delete a single asynchronous interrupt transfer for
  the device and endpoint.

  @param  Xhc                   The XHCI Instance.
  @param  BusAddr               The logical device address assigned by UsbBus driver.
  @param  EpNum                 The endpoint of the target.

  @retval EFI_SUCCESS           An asynchronous transfer is removed.
  @retval EFI_NOT_FOUND         No transfer for the device is found.

**/
EFI_STATUS
XhciDelAsyncIntTransfer (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  UINT8               BusAddr,
  IN  UINT8               EpNum
  )
{
  LIST_ENTRY              *Entry;
  LIST_ENTRY              *Next;
  URB                     *Urb;
  EFI_USB_DATA_DIRECTION  Direction;

  Direction = ((EpNum & 0x80) != 0) ? EfiUsbDataIn : EfiUsbDataOut;
  EpNum    &= 0x0F;

  Urb = NULL;

  EFI_LIST_FOR_EACH_SAFE (Entry, Next, &Xhc->AsyncIntTransfers) {
    Urb = EFI_LIST_CONTAINER (Entry, URB, UrbList);
    if ((Urb->Ep.BusAddr == BusAddr) &&
        (Urb->Ep.EpAddr == EpNum) &&
        (Urb->Ep.Direction == Direction)) {
      RemoveEntryList (&Urb->UrbList);
      FreePool (Urb->Data);
      XhcFreeUrb (Xhc, Urb);
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Remove all the asynchronous interrutp transfers.

  @param  Xhc    The XHCI Instance.

**/
VOID
XhciDelAllAsyncIntTransfers (
  IN USB_XHCI_INSTANCE    *Xhc
  )
{
  LIST_ENTRY              *Entry;
  LIST_ENTRY              *Next;
  URB                     *Urb;

  EFI_LIST_FOR_EACH_SAFE (Entry, Next, &Xhc->AsyncIntTransfers) {
    Urb = EFI_LIST_CONTAINER (Entry, URB, UrbList);
    RemoveEntryList (&Urb->UrbList);
    FreePool (Urb->Data);
    XhcFreeUrb (Xhc, Urb);
  }
}

/**
  Update the queue head for next round of asynchronous transfer

  @param  Xhc     The XHCI Instance.
  @param  Urb     The URB to update

**/
VOID
XhcUpdateAsyncRequest (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN URB                      *Urb
  )
{
  EFI_STATUS    Status;

  if (Urb->Result == EFI_USB_NOERROR) {
    Status = XhcCreateTransferTrb (Xhc, Urb);
    if (EFI_ERROR (Status)) {
      return;
    }
    Status = RingIntTransferDoorBell (Xhc, Urb);
    if (EFI_ERROR (Status)) {
      return;
    }
  }
}

/**
  Flush data from PCI controller specific address to mapped system
  memory address.

  @param  Xhc                The XHCI device.
  @param  Urb                The URB to unmap.

  @retval EFI_SUCCESS        Success to flush data to mapped system memory.
  @retval EFI_DEVICE_ERROR   Fail to flush data to mapped system memory.

**/
EFI_STATUS
XhcFlushAsyncIntMap (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  URB                 *Urb
  )
{
#if defined(OCTEONTX_NOT_USED)
  EFI_STATUS                    Status;
  EFI_PHYSICAL_ADDRESS          PhyAddr;
  EFI_PCI_IO_PROTOCOL_OPERATION MapOp;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINTN                         Len;
  VOID                          *Map;

  PciIo = Xhc->PciIo;
  Len   = Urb->DataLen;

  if (Urb->Ep.Direction == EfiUsbDataIn) {
    MapOp = EfiPciIoOperationBusMasterWrite;
  } else {
    MapOp = EfiPciIoOperationBusMasterRead;
  }

  if (Urb->DataMap != NULL) {
    Status = PciIo->Unmap (PciIo, Urb->DataMap);
    if (EFI_ERROR (Status)) {
      goto ON_ERROR;
    }
  }

  Urb->DataMap = NULL;

  Status = PciIo->Map (PciIo, MapOp, Urb->Data, &Len, &PhyAddr, &Map);
  if (EFI_ERROR (Status) || (Len != Urb->DataLen)) {
    goto ON_ERROR;
  }

  Urb->DataPhy  = (VOID *) ((UINTN) PhyAddr);
  Urb->DataMap  = Map;
  return EFI_SUCCESS;

ON_ERROR:
  return EFI_DEVICE_ERROR;
#else
  Urb->DataPhy  = (VOID *) bdk_ptr_to_phys(Urb->Data);
  BDK_WMB;
  return EFI_SUCCESS;
#endif
}

/**
  Interrupt transfer periodic check handler.

  @param  Event                 Interrupt event.
  @param  Context               Pointer to USB_XHCI_INSTANCE.

**/
VOID
EFIAPI
XhcMonitorAsyncRequests (
  IN EFI_EVENT            Event,
  IN VOID                 *Context
  )
{
  USB_XHCI_INSTANCE       *Xhc;
  LIST_ENTRY              *Entry;
  LIST_ENTRY              *Next;
  UINT8                   *ProcBuf;
  URB                     *Urb;
  UINT8                   SlotId;
  EFI_STATUS              Status;
#if defined(OCTEONTX_NOT_USED)
  EFI_TPL                 OldTpl;

  OldTpl = gBS->RaiseTPL (XHC_TPL);
#endif
  Xhc    = (USB_XHCI_INSTANCE*) Context;

  EFI_LIST_FOR_EACH_SAFE (Entry, Next, &Xhc->AsyncIntTransfers) {
    Urb = EFI_LIST_CONTAINER (Entry, URB, UrbList);

    //
    // Make sure that the device is available before every check.
    //
    SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
    if (SlotId == 0) {
      continue;
    }

    //
    // Check the result of URB execution. If it is still
    // active, check the next one.
    //
    XhcCheckUrbResult (Xhc, Urb);

    if (!Urb->Finished) {
      continue;
    }

    //
    // Flush any PCI posted write transactions from a PCI host
    // bridge to system memory.
    //
    Status = XhcFlushAsyncIntMap (Xhc, Urb);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Fail to Flush AsyncInt Mapped Memeory\n"));
    }

    //
    // Allocate a buffer then copy the transferred data for user.
    // If failed to allocate the buffer, update the URB for next
    // round of transfer. Ignore the data of this round.
    //
    ProcBuf = NULL;
    if (Urb->Result == EFI_USB_NOERROR) {
      ASSERT (Urb->Completed <= Urb->DataLen);

      ProcBuf = AllocateZeroPool (Urb->Completed);

      if (ProcBuf == NULL) {
        XhcUpdateAsyncRequest (Xhc, Urb);
        continue;
      }

      CopyMem (ProcBuf, Urb->Data, Urb->Completed);
    }

    //
    // Leave error recovery to its related device driver. A
    // common case of the error recovery is to re-submit the
    // interrupt transfer which is linked to the head of the
    // list. This function scans from head to tail. So the
    // re-submitted interrupt transfer's callback function
    // will not be called again in this round. Don't touch this
    // URB after the callback, it may have been removed by the
    // callback.
    //
    if (Urb->Callback != NULL) {
      //
      // Restore the old TPL, USB bus maybe connect device in
      // his callback. Some drivers may has a lower TPL restriction.
      //
#if defined(OCTEONTX_NOT_USED)
      gBS->RestoreTPL (OldTpl);
#endif
      (Urb->Callback) (ProcBuf, Urb->Completed, Urb->Context, Urb->Result);
#if defined(OCTEONTX_NOT_USED)
      OldTpl = gBS->RaiseTPL (XHC_TPL);
#endif
    }

    if (ProcBuf != NULL) {
#if defined(OCTEONTX_NOT_USED)
      gBS->FreePool (ProcBuf);
#else
      free(ProcBuf);
#endif
    }

    XhcUpdateAsyncRequest (Xhc, Urb);
  }
#if defined(OCTEONTX_NOT_USED)
  gBS->RestoreTPL (OldTpl);
#endif
}

/**
  Monitor the port status change. Enable/Disable device slot if there is a device attached/detached.

  @param  Xhc                   The XHCI Instance.
  @param  ParentRouteChart      The route string pointed to the parent device if it exists.
  @param  Port                  The port to be polled.
  @param  PortState             The port state.

  @retval EFI_SUCCESS           Successfully enable/disable device slot according to port state.
  @retval Others                Should not appear.

**/
EFI_STATUS
EFIAPI
XhcPollPortStatusChange (
  IN  USB_XHCI_INSTANCE     *Xhc,
  IN  USB_DEV_ROUTE         ParentRouteChart,
  IN  UINT8                 Port,
  IN  EFI_USB_PORT_STATUS   *PortState
  )
{
    if ((PortState->PortChangeStatus & (USB_PORT_STAT_C_CONNECTION | USB_PORT_STAT_C_ENABLE | USB_PORT_STAT_C_OVERCURRENT | USB_PORT_STAT_C_RESET)) == 0) {
        return 0;
    }

    EFI_STATUS        Status = EFI_SUCCESS;
    UINT8             Speed;
    UINT8             SlotId;
    USB_DEV_ROUTE     RouteChart;

    if (ParentRouteChart.Dword == 0) {
        RouteChart.Route.RouteString = 0;
        RouteChart.Route.RootPortNum = Port + 1;
        RouteChart.Route.TierNum     = 1;
    } else {
        if(Port < 14) {
            RouteChart.Route.RouteString = ParentRouteChart.Route.RouteString | (Port << (4 * (ParentRouteChart.Route.TierNum - 1)));
        } else {
            RouteChart.Route.RouteString = ParentRouteChart.Route.RouteString | (15 << (4 * (ParentRouteChart.Route.TierNum - 1)));
        }
        RouteChart.Route.RootPortNum   = ParentRouteChart.Route.RootPortNum;
        RouteChart.Route.TierNum       = ParentRouteChart.Route.TierNum + 1;
    }
    SlotId = XhcRouteStringToSlotId (Xhc, RouteChart);
    if (SlotId != 0) {
        DEBUG((EFI_D_INFO,"Disabling device slot n:%d u:%d s:%d\n",
               Xhc->node, Xhc->usb_port, SlotId));
#if defined(OCTEONTX_NOT_USED)
        if (Xhc->hccparams.s.csz == 0) {
            Status = XhcDisableSlotCmd (Xhc, SlotId);
        } else {
            Status = XhcDisableSlotCmd64 (Xhc, SlotId);
        }
#else
        Status = XhcDisableSlotCmd (Xhc, SlotId);
#endif
    }
   if (((PortState->PortStatus & USB_PORT_STAT_ENABLE) != 0) &&
      ((PortState->PortStatus & USB_PORT_STAT_CONNECTION) != 0)) {
    //
    // Has a device attached, Identify device speed after port is enabled.
    //
    Speed = EFI_USB_SPEED_FULL;
    if ((PortState->PortStatus & USB_PORT_STAT_LOW_SPEED) != 0) {
      Speed = EFI_USB_SPEED_LOW;
    } else if ((PortState->PortStatus & USB_PORT_STAT_HIGH_SPEED) != 0) {
      Speed = EFI_USB_SPEED_HIGH;
    } else if ((PortState->PortStatus & USB_PORT_STAT_SUPER_SPEED) != 0) {
      Speed = EFI_USB_SPEED_SUPER;
    }
    //
    // Execute Enable_Slot cmd for attached device, initialize device context and assign device address.
    //
    SlotId = XhcRouteStringToSlotId (Xhc, RouteChart);
    if ((SlotId == 0) && ((PortState->PortChangeStatus & USB_PORT_STAT_C_RESET) != 0)) {
        DEBUG((EFI_D_INFO,"Initializing device slot n:%d u:%d s:%d speed %d\n",
                Xhc->node, Xhc->usb_port, Port, Speed));
#if defined(BDK_XHCI_CSZ1_ONLY) && (BDK_XHCI_CSZ1_ONLY)
      Status = XhcInitializeDeviceSlot64 (Xhc, ParentRouteChart, Port, RouteChart, Speed);
#else
      if (Xhc->hccparams.s.csz == 0) {
        Status = XhcInitializeDeviceSlot (Xhc, ParentRouteChart, Port, RouteChart, Speed);
      } else {
        Status = XhcInitializeDeviceSlot64 (Xhc, ParentRouteChart, Port, RouteChart, Speed);
      }
#endif
    }

  }

  return Status;
}

/**
  Ring the door bell to notify XHCI there is a transaction to be executed through URB.

  @param  Xhc           The XHCI Instance.
  @param  Urb           The URB to be rung.

  @retval EFI_SUCCESS   Successfully ring the door bell.

**/
EFI_STATUS
RingIntTransferDoorBell (
  IN  USB_XHCI_INSTANCE   *Xhc,
  IN  URB                 *Urb
  )
{
  UINT8                SlotId;
  UINT8                Dci;

  SlotId = XhcBusDevAddrToSlotId (Xhc, Urb->Ep.BusAddr);
  Dci    = XhcEndpointToDci (Urb->Ep.EpAddr, (UINT8)(Urb->Ep.Direction));
  XhcRingDoorBell (Xhc, SlotId, Dci);
  return EFI_SUCCESS;
}

#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Initialize endpoint context in input context.

  @param Xhc            The XHCI Instance.
  @param SlotId         The slot id to be configured.
  @param DeviceSpeed    The device's speed.
  @param InputContext   The pointer to the input context.
  @param IfDesc         The pointer to the usb device interface descriptor.

  @return The maximum device context index of endpoint.

**/
UINT8
EFIAPI
XhcInitializeEndpointContext (
  IN USB_XHCI_INSTANCE          *Xhc,
  IN UINT8                      SlotId,
  IN UINT8                      DeviceSpeed,
  IN INPUT_CONTEXT              *InputContext,
  IN USB_INTERFACE_DESCRIPTOR   *IfDesc
  )
{
  USB_ENDPOINT_DESCRIPTOR       *EpDesc;
  UINTN                         NumEp;
  UINTN                         EpIndex;
  UINT8                         EpAddr;
  UINT8                         Direction;
  UINT8                         Dci;
  UINT8                         MaxDci;
  EFI_PHYSICAL_ADDRESS          PhyAddr;
  UINT8                         Interval;
  TRANSFER_RING                 *EndpointTransferRing;

  MaxDci = 0;

  NumEp = IfDesc->NumEndpoints;

  EpDesc = (USB_ENDPOINT_DESCRIPTOR *)(IfDesc + 1);
  for (EpIndex = 0; EpIndex < NumEp; EpIndex++) {
    while (EpDesc->DescriptorType != USB_DESC_TYPE_ENDPOINT) {
      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
    }

    if (EpDesc->Length < sizeof (USB_ENDPOINT_DESCRIPTOR)) {
      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
      continue;
    }

    EpAddr    = (UINT8)(EpDesc->EndpointAddress & 0x0F);
    Direction = (UINT8)((EpDesc->EndpointAddress & 0x80) ? EfiUsbDataIn : EfiUsbDataOut);

    Dci = XhcEndpointToDci (EpAddr, Direction);
    ASSERT (Dci < 32);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    InputContext->InputControlContext.Dword2 |= (BIT0 << Dci);
    InputContext->EP[Dci-1].MaxPacketSize     = EpDesc->MaxPacketSize;

    if (DeviceSpeed == EFI_USB_SPEED_SUPER) {
      //
      // 6.2.3.4, shall be set to the value defined in the bMaxBurst field of the SuperSpeed Endpoint Companion Descriptor.
      //
      InputContext->EP[Dci-1].MaxBurstSize = 0x0;
    } else {
      InputContext->EP[Dci-1].MaxBurstSize = 0x0;
    }

    switch (EpDesc->Attributes & USB_ENDPOINT_TYPE_MASK) {
      case USB_ENDPOINT_BULK:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_BULK_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_BULK_OUT;
        }

        InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
        if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] == NULL) {
          EndpointTransferRing = AllocateZeroPool(sizeof (TRANSFER_RING));
          Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] = (VOID *) EndpointTransferRing;
          EFI_STATUS rc=CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1]);
          ASSERT_HANG(!EFI_ERROR(rc));
        }

        break;
      case USB_ENDPOINT_ISO:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 0;
          InputContext->EP[Dci-1].EPType = ED_ISOCH_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 0;
          InputContext->EP[Dci-1].EPType = ED_ISOCH_OUT;
        }
        //
        // Do not support isochronous transfer now.
        //
        DEBUG ((EFI_D_INFO, "Unsupport ISO EP found, Transfer ring is not allocated.\n"));
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
      case USB_ENDPOINT_INTERRUPT:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_INTERRUPT_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_INTERRUPT_OUT;
        }
        InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
        InputContext->EP[Dci-1].MaxESITPayload   = EpDesc->MaxPacketSize;
        //
        // Get the bInterval from descriptor and init the the interval field of endpoint context
        //
        if ((DeviceSpeed == EFI_USB_SPEED_FULL) || (DeviceSpeed == EFI_USB_SPEED_LOW)) {
          Interval = EpDesc->Interval;
          //
          // Calculate through the bInterval field of Endpoint descriptor.
          //
          ASSERT (Interval != 0);
          InputContext->EP[Dci-1].Interval = (UINT32)HighBitSet((UINT32)Interval) + 3;
        } else if ((DeviceSpeed == EFI_USB_SPEED_HIGH) || (DeviceSpeed == EFI_USB_SPEED_SUPER)) {
          Interval = EpDesc->Interval;
          ASSERT (Interval >= 1 && Interval <= 16);
          //
          // Refer to XHCI 1.0 spec section 6.2.3.6, table 61
          //
          InputContext->EP[Dci-1].Interval         = Interval - 1;
          InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
          InputContext->EP[Dci-1].MaxESITPayload   = 0x0002;
          InputContext->EP[Dci-1].MaxBurstSize     = 0x0;
          InputContext->EP[Dci-1].CErr             = 3;
        }

        if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] == NULL) {
          EndpointTransferRing = AllocateZeroPool(sizeof (TRANSFER_RING));
          Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] = (VOID *) EndpointTransferRing;
          EFI_STATUS rc = CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1]);
          ASSERT_HANG(!EFI_ERROR(rc));
        }
        break;

      case USB_ENDPOINT_CONTROL:
        //
        // Do not support control transfer now.
        //
        DEBUG ((EFI_D_INFO, "Unsupport Control EP found, Transfer ring is not allocated.\n"));
      default:
        DEBUG ((EFI_D_INFO, "Unknown EP found, Transfer ring is not allocated.\n"));
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
    }
#if defined(OCTEONTX_NOT_USED)
    PhyAddr = UsbHcGetPciAddrForHostAddr (
                Xhc->MemPool,
                ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingSeg0,
                sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER
                );
#else
    PhyAddr = bdk_ptr_to_phys( ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingSeg0);
#endif
    PhyAddr &= ~((EFI_PHYSICAL_ADDRESS)0x0F);
    PhyAddr |= (EFI_PHYSICAL_ADDRESS)((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingPCS;
    InputContext->EP[Dci-1].PtrLo = XHC_LOW_32BIT (PhyAddr);
    InputContext->EP[Dci-1].PtrHi = XHC_HIGH_32BIT (PhyAddr);

    EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
  }

  return MaxDci;
}
#endif
/**
  Initialize endpoint context in input context.

  @param Xhc            The XHCI Instance.
  @param SlotId         The slot id to be configured.
  @param DeviceSpeed    The device's speed.
  @param InputContext   The pointer to the input context.
  @param IfDesc         The pointer to the usb device interface descriptor.

  @return The maximum device context index of endpoint.

**/
UINT8
EFIAPI
XhcInitializeEndpointContext64 (
  IN USB_XHCI_INSTANCE          *Xhc,
  IN UINT8                      SlotId,
  IN UINT8                      DeviceSpeed,
  IN INPUT_CONTEXT_64           *InputContext,
  IN USB_INTERFACE_DESCRIPTOR   *IfDesc
  )
{
  USB_ENDPOINT_DESCRIPTOR       *EpDesc;
  UINTN                         NumEp;
  UINTN                         EpIndex;
  UINT8                         EpAddr;
  UINT8                         Direction;
  UINT8                         Dci;
  UINT8                         MaxDci;
  EFI_PHYSICAL_ADDRESS          PhyAddr;
  UINT8                         Interval;
  TRANSFER_RING                 *EndpointTransferRing;

  MaxDci = 0;

  NumEp = IfDesc->NumEndpoints;

  EpDesc = (USB_ENDPOINT_DESCRIPTOR *)(IfDesc + 1);
  for (EpIndex = 0; EpIndex < NumEp; EpIndex++) {
    while (EpDesc->DescriptorType != USB_DESC_TYPE_ENDPOINT) {
      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
    }

    if (EpDesc->Length < sizeof (USB_ENDPOINT_DESCRIPTOR)) {
      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
      continue;
    }

    EpAddr    = (UINT8)(EpDesc->EndpointAddress & 0x0F);
    Direction = (UINT8)((EpDesc->EndpointAddress & 0x80) ? EfiUsbDataIn : EfiUsbDataOut);

    Dci = XhcEndpointToDci (EpAddr, Direction);
    ASSERT (Dci < 32);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    InputContext->InputControlContext.Dword2 |= (BIT0 << Dci);
    InputContext->EP[Dci-1].MaxPacketSize     = EpDesc->MaxPacketSize;

    if (DeviceSpeed == EFI_USB_SPEED_SUPER) {
      //
      // 6.2.3.4, shall be set to the value defined in the bMaxBurst field of the SuperSpeed Endpoint Companion Descriptor.
      //
      InputContext->EP[Dci-1].MaxBurstSize = 0x0;
    } else {
      InputContext->EP[Dci-1].MaxBurstSize = 0x0;
    }

    switch (EpDesc->Attributes & USB_ENDPOINT_TYPE_MASK) {
      case USB_ENDPOINT_BULK:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_BULK_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_BULK_OUT;
        }

        InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
        if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] == NULL) {
          EndpointTransferRing = AllocateZeroPool(sizeof (TRANSFER_RING));
          Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] = (VOID *) EndpointTransferRing;
          EFI_STATUS rc = CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1]);
           ASSERT_HANG(!EFI_ERROR(rc));
        }

        break;
      case USB_ENDPOINT_ISO:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 0;
          InputContext->EP[Dci-1].EPType = ED_ISOCH_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 0;
          InputContext->EP[Dci-1].EPType = ED_ISOCH_OUT;
        }
        //
        // Do not support isochronous transfer now.
        //
        DEBUG ((EFI_D_INFO, "Unsupport ISO EP found, Transfer ring is not allocated.\n"));
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
      case USB_ENDPOINT_INTERRUPT:
        if (Direction == EfiUsbDataIn) {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_INTERRUPT_IN;
        } else {
          InputContext->EP[Dci-1].CErr   = 3;
          InputContext->EP[Dci-1].EPType = ED_INTERRUPT_OUT;
        }
        InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
        InputContext->EP[Dci-1].MaxESITPayload   = EpDesc->MaxPacketSize;
        //
        // Get the bInterval from descriptor and init the the interval field of endpoint context
        //
        if ((DeviceSpeed == EFI_USB_SPEED_FULL) || (DeviceSpeed == EFI_USB_SPEED_LOW)) {
          Interval = EpDesc->Interval;
          //
          // Calculate through the bInterval field of Endpoint descriptor.
          //
          ASSERT (Interval != 0);
          InputContext->EP[Dci-1].Interval = (UINT32)HighBitSet((UINT32)Interval) + 3;
        } else if ((DeviceSpeed == EFI_USB_SPEED_HIGH) || (DeviceSpeed == EFI_USB_SPEED_SUPER)) {
          Interval = EpDesc->Interval;
          ASSERT (Interval >= 1 && Interval <= 16);
          //
          // Refer to XHCI 1.0 spec section 6.2.3.6, table 61
          //
          InputContext->EP[Dci-1].Interval         = Interval - 1;
          InputContext->EP[Dci-1].AverageTRBLength = 0x1000;
          InputContext->EP[Dci-1].MaxESITPayload   = 0x0002;
          InputContext->EP[Dci-1].MaxBurstSize     = 0x0;
          InputContext->EP[Dci-1].CErr             = 3;
        }

        if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] == NULL) {
          EndpointTransferRing = AllocateZeroPool(sizeof (TRANSFER_RING));
          Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1] = (VOID *) EndpointTransferRing;
          EFI_STATUS rc = CreateTransferRing(Xhc, TR_RING_TRB_NUMBER, (TRANSFER_RING *)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1]);
          ASSERT_HANG(!EFI_ERROR(rc));
        }
        break;

      case USB_ENDPOINT_CONTROL:
        //
        // Do not support control transfer now.
        //
        DEBUG ((EFI_D_INFO, "Unsupport Control EP found, Transfer ring is not allocated.\n"));
        /* FALL THRU */
      default:
        DEBUG ((EFI_D_INFO, "Unknown EP found, Transfer ring is not allocated.\n"));
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
    }
#if defined(OCTEONTX_NOT_USED)
    PhyAddr = UsbHcGetPciAddrForHostAddr (
                Xhc->MemPool,
                ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingSeg0,
                sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER
                );
#else
    PhyAddr = bdk_ptr_to_phys( ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingSeg0);
#endif
    PhyAddr &= ~((EFI_PHYSICAL_ADDRESS)0x0F);
    PhyAddr |= (EFI_PHYSICAL_ADDRESS)((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci-1])->RingPCS;
    InputContext->EP[Dci-1].PtrLo = XHC_LOW_32BIT (PhyAddr);
    InputContext->EP[Dci-1].PtrHi = XHC_HIGH_32BIT (PhyAddr);

    EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
  }

  return MaxDci;
}

#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Configure all the device endpoints through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  DeviceSpeed   The device's speed.
  @param  ConfigDesc    The pointer to the usb device configuration descriptor.

  @retval EFI_SUCCESS   Successfully configure all the device endpoints.

**/
EFI_STATUS
EFIAPI
XhcSetConfigCmd (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    DeviceSpeed,
  IN USB_CONFIG_DESCRIPTOR    *ConfigDesc
  )
{
  EFI_STATUS                  Status;
  USB_INTERFACE_DESCRIPTOR    *IfDesc;
  UINT8                       Index;
  UINT8                       Dci;
  UINT8                       MaxDci;
  /* EFI_PHYSICAL_ADDRESS */   uint64_t /* cavium*/     PhyAddr;

  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  INPUT_CONTEXT               *InputContext;
  DEVICE_CONTEXT              *OutputContext;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  //
  // 4.6.6 Configure Endpoint
  //
  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT));
  CopyMem (&InputContext->Slot, &OutputContext->Slot, sizeof (SLOT_CONTEXT));

  ASSERT (ConfigDesc != NULL);

  MaxDci = 0;

  IfDesc = (USB_INTERFACE_DESCRIPTOR *)(ConfigDesc + 1);
  for (Index = 0; Index < ConfigDesc->NumInterfaces; Index++) {
    while ((IfDesc->DescriptorType != USB_DESC_TYPE_INTERFACE) || (IfDesc->AlternateSetting != 0)) {
      IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
    }

    if (IfDesc->Length < sizeof (USB_INTERFACE_DESCRIPTOR)) {
      IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
      continue;
    }

    Dci = XhcInitializeEndpointContext (Xhc, SlotId, DeviceSpeed, InputContext, IfDesc);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
  }

  InputContext->InputControlContext.Dword2 |= BIT0;
  InputContext->Slot.ContextEntries         = MaxDci;
  //
  // configure endpoint
  //
  ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT));
#else
  PhyAddr = bdk_ptr_to_phys( InputContext);
#endif
  CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbCfgEP.CycleBit = 1;
  CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
  CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Configure Endpoint\n"));
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int) Status));
  } else {
    Xhc->UsbDevContext[SlotId].ActiveConfiguration = ConfigDesc->ConfigurationValue;
  }

  return Status;
}
#endif
/**
  Configure all the device endpoints through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  DeviceSpeed   The device's speed.
  @param  ConfigDesc    The pointer to the usb device configuration descriptor.

  @retval EFI_SUCCESS   Successfully configure all the device endpoints.

**/
EFI_STATUS
EFIAPI
XhcSetConfigCmd64 (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    DeviceSpeed,
  IN USB_CONFIG_DESCRIPTOR    *ConfigDesc
  )
{
  EFI_STATUS                  Status;
  USB_INTERFACE_DESCRIPTOR    *IfDesc;
  UINT8                       Index;
  UINT8                       Dci;
  UINT8                       MaxDci;
  /* EFI_PHYSICAL_ADDRESS */   uint64_t /* cavium*/     PhyAddr;


  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  INPUT_CONTEXT_64            *InputContext;
  DEVICE_CONTEXT_64           *OutputContext;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  //
  // 4.6.6 Configure Endpoint
  //
  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT_64));
  CopyMem (&InputContext->Slot, &OutputContext->Slot, sizeof (SLOT_CONTEXT_64));

  ASSERT (ConfigDesc != NULL);

  MaxDci = 0;

  IfDesc = (USB_INTERFACE_DESCRIPTOR *)(ConfigDesc + 1);
  for (Index = 0; Index < ConfigDesc->NumInterfaces; Index++) {
    while ((IfDesc->DescriptorType != USB_DESC_TYPE_INTERFACE) || (IfDesc->AlternateSetting != 0)) {
      IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
    }

    if (IfDesc->Length < sizeof (USB_INTERFACE_DESCRIPTOR)) {
      IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
      continue;
    }

    Dci = XhcInitializeEndpointContext64 (Xhc, SlotId, DeviceSpeed, InputContext, IfDesc);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
  }

  InputContext->InputControlContext.Dword2 |= BIT0;
  InputContext->Slot.ContextEntries         = MaxDci;
  //
  // configure endpoint
  //
  ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr  = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT_64));
#else
   PhyAddr = bdk_ptr_to_phys( InputContext);
#endif
  CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbCfgEP.CycleBit = 1;
  CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
  CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Configure Endpoint\n"));
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int) Status));
  } else {
    Xhc->UsbDevContext[SlotId].ActiveConfiguration = ConfigDesc->ConfigurationValue;
  }

  return Status;
}

/**
  Stop endpoint through XHCI's Stop_Endpoint cmd.

  @param  Xhc                   The XHCI Instance.
  @param  SlotId                The slot id to be configured.
  @param  Dci                   The device context index of endpoint.

  @retval EFI_SUCCESS           Stop endpoint successfully.
  @retval Others                Failed to stop endpoint.

**/
EFI_STATUS
EFIAPI
XhcStopEndpoint (
  IN USB_XHCI_INSTANCE      *Xhc,
  IN UINT8                  SlotId,
  IN UINT8                  Dci
  )
{
  EFI_STATUS                    Status;
  EVT_TRB_COMMAND_COMPLETION    *EvtTrb;
  CMD_TRB_STOP_ENDPOINT         CmdTrbStopED;

  DEBUG ((EFI_D_INFO, "Slot = 0x%x, Dci = 0x%x\n", SlotId, Dci));

  //
  // Send stop endpoint command to transit Endpoint from running to stop state
  //
  ZeroMem (&CmdTrbStopED, sizeof (CmdTrbStopED));
  CmdTrbStopED.CycleBit = 1;
  CmdTrbStopED.Type     = TRB_TYPE_STOP_ENDPOINT;
  CmdTrbStopED.EDID     = Dci;
  CmdTrbStopED.SlotId   = SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbStopED,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Stop Endpoint Failed, Status = %d\n", (int) Status));
  }

  return Status;
}

#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Set interface through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  DeviceSpeed   The device's speed.
  @param  ConfigDesc    The pointer to the usb device configuration descriptor.
  @param  Request       USB device request to send.

  @retval EFI_SUCCESS   Successfully set interface.

**/
EFI_STATUS
EFIAPI
XhcSetInterface (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    DeviceSpeed,
  IN USB_CONFIG_DESCRIPTOR    *ConfigDesc,
  IN EFI_USB_DEVICE_REQUEST   *Request
  )
{
  EFI_STATUS                  Status;
  USB_INTERFACE_DESCRIPTOR    *IfDescActive;
  USB_INTERFACE_DESCRIPTOR    *IfDescSet;
  USB_INTERFACE_DESCRIPTOR    *IfDesc;
  USB_ENDPOINT_DESCRIPTOR     *EpDesc;
  UINTN                       NumEp;
  UINTN                       EpIndex;
  UINT8                       EpAddr;
  UINT8                       Direction;
  UINT8                       Dci;
  UINT8                       MaxDci;
  EFI_PHYSICAL_ADDRESS        PhyAddr;
  VOID                        *RingSeg;

  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  INPUT_CONTEXT               *InputContext;
  DEVICE_CONTEXT              *OutputContext;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;

  Status = EFI_SUCCESS;

  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;
  //
  // XHCI 4.6.6 Configure Endpoint
  // When this command is used to "Set an Alternate Interface on a device", software shall set the Drop
  // Context and Add Context flags as follows:
  // 1) If an endpoint is not modified by the Alternate Interface setting, then software shall set the Drop
  // Context and Add Context flags to '0'.
  //
  // Except the interface indicated by Reqeust->Index, no impact to other interfaces.
  // So the default Drop Context and Add Context flags can be '0' to cover 1).
  //
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT));
  CopyMem (&InputContext->Slot, &OutputContext->Slot, sizeof (SLOT_CONTEXT));

  ASSERT (ConfigDesc != NULL);

  MaxDci = 0;

  IfDescActive = NULL;
  IfDescSet = NULL;

  IfDesc = (USB_INTERFACE_DESCRIPTOR *)(ConfigDesc + 1);
  while ((UINTN) IfDesc < ((UINTN) ConfigDesc + ConfigDesc->TotalLength)) {
    if ((IfDesc->DescriptorType == USB_DESC_TYPE_INTERFACE) && (IfDesc->Length >= sizeof (USB_INTERFACE_DESCRIPTOR))) {
      if (IfDesc->InterfaceNumber == (UINT8) Request->Index) {
        if (IfDesc->AlternateSetting == Xhc->UsbDevContext[SlotId].ActiveAlternateSetting[IfDesc->InterfaceNumber]) {
          //
          // Find out the active interface descriptor.
          //
          IfDescActive = IfDesc;
        } else if (IfDesc->AlternateSetting == (UINT8) Request->Value) {
          //
          // Find out the interface descriptor to set.
          //
          IfDescSet = IfDesc;
        }
      }
    }
    IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
  }

  //
  // XHCI 4.6.6 Configure Endpoint
  // When this command is used to "Set an Alternate Interface on a device", software shall set the Drop
  // Context and Add Context flags as follows:
  // 2) If an endpoint previously disabled, is enabled by the Alternate Interface setting, then software shall set
  // the Drop Context flag to '0' and Add Context flag to '1', and initialize the Input Endpoint Context.
  // 3) If an endpoint previously enabled, is disabled by the Alternate Interface setting, then software shall set
  // the Drop Context flag to '1' and Add Context flag to '0'.
  // 4) If a parameter of an enabled endpoint is modified by an Alternate Interface setting, the Drop Context
  // and Add Context flags shall be set to '1'.
  //
  // Below codes are to cover 2), 3) and 4).
  //

  if ((IfDescActive != NULL) && (IfDescSet != NULL)) {
    NumEp = IfDescActive->NumEndpoints;
    EpDesc = (USB_ENDPOINT_DESCRIPTOR *) (IfDescActive + 1);
    for (EpIndex = 0; EpIndex < NumEp; EpIndex++) {
      while (EpDesc->DescriptorType != USB_DESC_TYPE_ENDPOINT) {
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
      }

      if (EpDesc->Length < sizeof (USB_ENDPOINT_DESCRIPTOR)) {
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
      }

      EpAddr    = (UINT8) (EpDesc->EndpointAddress & 0x0F);
      Direction = (UINT8) ((EpDesc->EndpointAddress & 0x80) ? EfiUsbDataIn : EfiUsbDataOut);

      Dci = XhcEndpointToDci (EpAddr, Direction);
      ASSERT (Dci < 32);
      if (Dci > MaxDci) {
        MaxDci = Dci;
      }
      //
      // XHCI 4.3.6 - Setting Alternate Interfaces
      // 1) Stop any Running Transfer Rings affected by the Alternate Interface setting.
      //
      Status = XhcStopEndpoint (Xhc, SlotId, Dci);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      //
      // XHCI 4.3.6 - Setting Alternate Interfaces
      // 2) Free Transfer Rings of all endpoints that will be affected by the Alternate Interface setting.
      //
      if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1] != NULL) {
        RingSeg = ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1])->RingSeg0;
        if (RingSeg != NULL) {
#if defined(OCTEONTX_NOT_USED)
          UsbHcFreeMem (Xhc->MemPool, RingSeg, sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER);
#else
          free(RingSeg);
#endif
        }
        FreePool (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1]);
        Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1] = NULL;
      }

      //
      // Set the Drop Context flag to '1'.
      //
      InputContext->InputControlContext.Dword1 |= (BIT0 << Dci);

      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
    }

    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 3) Clear all the Endpoint Context fields of each endpoint that will be disabled by the Alternate
    // Interface setting, to '0'.
    //
    // The step 3) has been covered by the ZeroMem () to InputContext at the start of the function.
    //

    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 4) For each endpoint enabled by the Configure Endpoint Command:
    //   a. Allocate a Transfer Ring.
    //   b. Initialize the Transfer Ring Segment(s) by clearing all fields of all TRBs to '0'.
    //   c. Initialize the Endpoint Context data structure.
    //
    Dci = XhcInitializeEndpointContext (Xhc, SlotId, DeviceSpeed, InputContext, IfDescSet);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    InputContext->InputControlContext.Dword2 |= BIT0;
    InputContext->Slot.ContextEntries         = MaxDci;
    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 5) Issue and successfully complete a Configure Endpoint Command.
    //
    ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
    PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT));
#else
    PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
    CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
    CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
    CmdTrbCfgEP.CycleBit = 1;
    CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
    CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
    DEBUG ((EFI_D_INFO, "Configure Endpoint\n"));
    Status = XhcCmdTransfer (
               Xhc,
               (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
               XHC_GENERIC_TIMEOUT,
               (TRB_TEMPLATE **) (UINTN) &EvtTrb
               );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int) Status));
    } else {
      //
      // Update the active AlternateSetting.
      //
      Xhc->UsbDevContext[SlotId].ActiveAlternateSetting[(UINT8) Request->Index] = (UINT8) Request->Value;
    }
  }

  return Status;
}
#endif

/**
  Reset endpoint through XHCI's Reset_Endpoint cmd.

  @param  Xhc                   The XHCI Instance.
  @param  SlotId                The slot id to be configured.
  @param  Dci                   The device context index of endpoint.

  @retval EFI_SUCCESS           Reset endpoint successfully.
  @retval Others                Failed to reset endpoint.

**/
EFI_STATUS
EFIAPI
XhcResetEndpoint (
  IN USB_XHCI_INSTANCE      *Xhc,
  IN UINT8                  SlotId,
  IN UINT8                  Dci
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  CMD_TRB_RESET_ENDPOINT      CmdTrbResetED;

  DEBUG ((EFI_D_INFO, "Slot = 0x%x, Dci = 0x%x\n", SlotId, Dci));

  //
  // Send stop endpoint command to transit Endpoint from running to stop state
  //
  ZeroMem (&CmdTrbResetED, sizeof (CmdTrbResetED));
  CmdTrbResetED.CycleBit = 1;
  CmdTrbResetED.Type     = TRB_TYPE_RESET_ENDPOINT;
  CmdTrbResetED.EDID     = Dci;
  CmdTrbResetED.SlotId   = SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbResetED,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Reset Endpoint Failed, Status = %d\n", (int) Status));
  }

  return Status;
}

/**
  Set transfer ring dequeue pointer through XHCI's Set_Tr_Dequeue_Pointer cmd.

  @param  Xhc                   The XHCI Instance.
  @param  SlotId                The slot id to be configured.
  @param  Dci                   The device context index of endpoint.
  @param  Urb                   The dequeue pointer of the transfer ring specified
                                by the urb to be updated.

  @retval EFI_SUCCESS           Set transfer ring dequeue pointer succeeds.
  @retval Others                Failed to set transfer ring dequeue pointer.

**/
EFI_STATUS
EFIAPI
XhcSetTrDequeuePointer (
  IN USB_XHCI_INSTANCE      *Xhc,
  IN UINT8                  SlotId,
  IN UINT8                  Dci,
  IN URB                    *Urb
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  CMD_SET_TR_DEQ_POINTER      CmdSetTRDeq;
  EFI_PHYSICAL_ADDRESS        PhyAddr;

  DEBUG ((EFI_D_INFO, "Slot = 0x%x, Dci = 0x%x, Urb = %p\n", SlotId, Dci, Urb));

  //
  // Send stop endpoint command to transit Endpoint from running to stop state
  //
  ZeroMem (&CmdSetTRDeq, sizeof (CmdSetTRDeq));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, Urb->Ring->RingEnqueue, sizeof (CMD_SET_TR_DEQ_POINTER));
#else
  PhyAddr = bdk_ptr_to_phys(Urb->Ring->RingEnqueue);
#endif
  CmdSetTRDeq.PtrLo    = XHC_LOW_32BIT (PhyAddr) | Urb->Ring->RingPCS;
  CmdSetTRDeq.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdSetTRDeq.CycleBit = 1;
  CmdSetTRDeq.Type     = TRB_TYPE_SET_TR_DEQUE;
  CmdSetTRDeq.Endpoint = Dci;
  CmdSetTRDeq.SlotId   = SlotId;
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdSetTRDeq,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Set TR Dequeue Pointer Failed, Status = %d\n", (int) Status));
  }

  return Status;
}

/**
  Set interface through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  DeviceSpeed   The device's speed.
  @param  ConfigDesc    The pointer to the usb device configuration descriptor.
  @param  Request       USB device request to send.

  @retval EFI_SUCCESS   Successfully set interface.

**/
EFI_STATUS
EFIAPI
XhcSetInterface64 (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    DeviceSpeed,
  IN USB_CONFIG_DESCRIPTOR    *ConfigDesc,
  IN EFI_USB_DEVICE_REQUEST   *Request
  )
{
  EFI_STATUS                  Status;
  USB_INTERFACE_DESCRIPTOR    *IfDescActive;
  USB_INTERFACE_DESCRIPTOR    *IfDescSet;
  USB_INTERFACE_DESCRIPTOR    *IfDesc;
  USB_ENDPOINT_DESCRIPTOR     *EpDesc;
  UINTN                       NumEp;
  UINTN                       EpIndex;
  UINT8                       EpAddr;
  UINT8                       Direction;
  UINT8                       Dci;
  UINT8                       MaxDci;
  EFI_PHYSICAL_ADDRESS        PhyAddr;
  VOID                        *RingSeg;

  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  INPUT_CONTEXT_64            *InputContext;
  DEVICE_CONTEXT_64           *OutputContext;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;

  Status = EFI_SUCCESS;

  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;
  //
  // XHCI 4.6.6 Configure Endpoint
  // When this command is used to "Set an Alternate Interface on a device", software shall set the Drop
  // Context and Add Context flags as follows:
  // 1) If an endpoint is not modified by the Alternate Interface setting, then software shall set the Drop
  // Context and Add Context flags to '0'.
  //
  // Except the interface indicated by Reqeust->Index, no impact to other interfaces.
  // So the default Drop Context and Add Context flags can be '0' to cover 1).
  //
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT_64));
  CopyMem (&InputContext->Slot, &OutputContext->Slot, sizeof (SLOT_CONTEXT_64));

  ASSERT (ConfigDesc != NULL);

  MaxDci = 0;

  IfDescActive = NULL;
  IfDescSet = NULL;

  IfDesc = (USB_INTERFACE_DESCRIPTOR *)(ConfigDesc + 1);
  while ((UINTN) IfDesc < ((UINTN) ConfigDesc + ConfigDesc->TotalLength)) {
    if ((IfDesc->DescriptorType == USB_DESC_TYPE_INTERFACE) && (IfDesc->Length >= sizeof (USB_INTERFACE_DESCRIPTOR))) {
      if (IfDesc->InterfaceNumber == (UINT8) Request->Index) {
        if (IfDesc->AlternateSetting == Xhc->UsbDevContext[SlotId].ActiveAlternateSetting[IfDesc->InterfaceNumber]) {
          //
          // Find out the active interface descriptor.
          //
          IfDescActive = IfDesc;
        } else if (IfDesc->AlternateSetting == (UINT8) Request->Value) {
          //
          // Find out the interface descriptor to set.
          //
          IfDescSet = IfDesc;
        }
      }
    }
    IfDesc = (USB_INTERFACE_DESCRIPTOR *)((UINTN)IfDesc + IfDesc->Length);
  }

  //
  // XHCI 4.6.6 Configure Endpoint
  // When this command is used to "Set an Alternate Interface on a device", software shall set the Drop
  // Context and Add Context flags as follows:
  // 2) If an endpoint previously disabled, is enabled by the Alternate Interface setting, then software shall set
  // the Drop Context flag to '0' and Add Context flag to '1', and initialize the Input Endpoint Context.
  // 3) If an endpoint previously enabled, is disabled by the Alternate Interface setting, then software shall set
  // the Drop Context flag to '1' and Add Context flag to '0'.
  // 4) If a parameter of an enabled endpoint is modified by an Alternate Interface setting, the Drop Context
  // and Add Context flags shall be set to '1'.
  //
  // Below codes are to cover 2), 3) and 4).
  //

  if ((IfDescActive != NULL) && (IfDescSet != NULL)) {
    NumEp = IfDescActive->NumEndpoints;
    EpDesc = (USB_ENDPOINT_DESCRIPTOR *) (IfDescActive + 1);
    for (EpIndex = 0; EpIndex < NumEp; EpIndex++) {
      while (EpDesc->DescriptorType != USB_DESC_TYPE_ENDPOINT) {
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
      }

      if (EpDesc->Length < sizeof (USB_ENDPOINT_DESCRIPTOR)) {
        EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
        continue;
      }

      EpAddr    = (UINT8) (EpDesc->EndpointAddress & 0x0F);
      Direction = (UINT8) ((EpDesc->EndpointAddress & 0x80) ? EfiUsbDataIn : EfiUsbDataOut);

      Dci = XhcEndpointToDci (EpAddr, Direction);
      ASSERT (Dci < 32);
      if (Dci > MaxDci) {
        MaxDci = Dci;
      }
      //
      // XHCI 4.3.6 - Setting Alternate Interfaces
      // 1) Stop any Running Transfer Rings affected by the Alternate Interface setting.
      //
      Status = XhcStopEndpoint (Xhc, SlotId, Dci);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      //
      // XHCI 4.3.6 - Setting Alternate Interfaces
      // 2) Free Transfer Rings of all endpoints that will be affected by the Alternate Interface setting.
      //
      if (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1] != NULL) {
        RingSeg = ((TRANSFER_RING *)(UINTN)Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1])->RingSeg0;
        if (RingSeg != NULL) {
#if defined(OCTEONTX_NOT_USED)
          UsbHcFreeMem (Xhc->MemPool, RingSeg, sizeof (TRB_TEMPLATE) * TR_RING_TRB_NUMBER);
#else
          free(RingSeg);
#endif
        }
        FreePool (Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1]);
        Xhc->UsbDevContext[SlotId].EndpointTransferRing[Dci - 1] = NULL;
      }

      //
      // Set the Drop Context flag to '1'.
      //
      InputContext->InputControlContext.Dword1 |= (BIT0 << Dci);

      EpDesc = (USB_ENDPOINT_DESCRIPTOR *)((UINTN)EpDesc + EpDesc->Length);
    }

    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 3) Clear all the Endpoint Context fields of each endpoint that will be disabled by the Alternate
    // Interface setting, to '0'.
    //
    // The step 3) has been covered by the ZeroMem () to InputContext at the start of the function.
    //

    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 4) For each endpoint enabled by the Configure Endpoint Command:
    //   a. Allocate a Transfer Ring.
    //   b. Initialize the Transfer Ring Segment(s) by clearing all fields of all TRBs to '0'.
    //   c. Initialize the Endpoint Context data structure.
    //
    Dci = XhcInitializeEndpointContext64 (Xhc, SlotId, DeviceSpeed, InputContext, IfDescSet);
    if (Dci > MaxDci) {
      MaxDci = Dci;
    }

    InputContext->InputControlContext.Dword2 |= BIT0;
    InputContext->Slot.ContextEntries         = MaxDci;
    //
    // XHCI 4.3.6 - Setting Alternate Interfaces
    // 5) Issue and successfully complete a Configure Endpoint Command.
    //
    ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
    PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT_64));
#else
  PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
    CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
    CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
    CmdTrbCfgEP.CycleBit = 1;
    CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
    CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
    DEBUG ((EFI_D_INFO, "Configure Endpoint\n"));
    Status = XhcCmdTransfer (
               Xhc,
               (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
               XHC_GENERIC_TIMEOUT,
               (TRB_TEMPLATE **) (UINTN) &EvtTrb
               );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int) Status));
    } else {
      //
      // Update the active AlternateSetting.
      //
      Xhc->UsbDevContext[SlotId].ActiveAlternateSetting[(UINT8) Request->Index] = (UINT8) Request->Value;
    }
  }

  return Status;
}
#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Evaluate the endpoint 0 context through XHCI's Evaluate_Context cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be evaluated.
  @param  MaxPacketSize The max packet size supported by the device control transfer.

  @retval EFI_SUCCESS   Successfully evaluate the device endpoint 0.

**/
EFI_STATUS
EFIAPI
XhcEvaluateContext (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT32                   MaxPacketSize
  )
{
  EFI_STATUS                  Status;
  CMD_TRB_EVALUATE_CONTEXT    CmdTrbEvalu;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT               *InputContext;
  EFI_PHYSICAL_ADDRESS        PhyAddr;

  ASSERT (Xhc->UsbDevContext[SlotId].SlotId != 0);

  //
  // 4.6.7 Evaluate Context
  //
  InputContext = Xhc->UsbDevContext[SlotId].InputContext;
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT));

  InputContext->InputControlContext.Dword2 |= BIT1;
  InputContext->EP[0].MaxPacketSize         = MaxPacketSize;

  ZeroMem (&CmdTrbEvalu, sizeof (CmdTrbEvalu));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT));
#else
  PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
  CmdTrbEvalu.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbEvalu.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbEvalu.CycleBit = 1;
  CmdTrbEvalu.Type     = TRB_TYPE_EVALU_CONTXT;
  CmdTrbEvalu.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Evaluate context\n"));
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbEvalu,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Evaluate Context Failed, Status = %d\n", (int) Status));
  }
  return Status;
}
#endif

/**
  Evaluate the endpoint 0 context through XHCI's Evaluate_Context cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be evaluated.
  @param  MaxPacketSize The max packet size supported by the device control transfer.

  @retval EFI_SUCCESS   Successfully evaluate the device endpoint 0.

**/
EFI_STATUS
EFIAPI
XhcEvaluateContext64 (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT32                   MaxPacketSize
  )
{
  EFI_STATUS                  Status;
  CMD_TRB_EVALUATE_CONTEXT    CmdTrbEvalu;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT_64            *InputContext;
  EFI_PHYSICAL_ADDRESS        PhyAddr;

  ASSERT (Xhc->UsbDevContext[SlotId].SlotId != 0);

  //
  // 4.6.7 Evaluate Context
  //
  InputContext = Xhc->UsbDevContext[SlotId].InputContext;
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT_64));

  InputContext->InputControlContext.Dword2 |= BIT1;
  InputContext->EP[0].MaxPacketSize         = MaxPacketSize;

  ZeroMem (&CmdTrbEvalu, sizeof (CmdTrbEvalu));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT_64));
#else
  PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
  CmdTrbEvalu.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbEvalu.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbEvalu.CycleBit = 1;
  CmdTrbEvalu.Type     = TRB_TYPE_EVALU_CONTXT;
  CmdTrbEvalu.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Evaluate context\n"));
  Status = XhcCmdTransfer (
             Xhc,
             (TRB_TEMPLATE *) (UINTN) &CmdTrbEvalu,
             XHC_GENERIC_TIMEOUT,
             (TRB_TEMPLATE **) (UINTN) &EvtTrb
             );
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Evaluate Context Failed, Status = %d\n", (int) Status));
  }
  return Status;
}

#if !defined(BDK_XHCI_CSZ1_ONLY) || (0 == BDK_XHCI_CSZ1_ONLY)
/**
  Evaluate the slot context for hub device through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  PortNum       The total number of downstream port supported by the hub.
  @param  TTT           The TT think time of the hub device.
  @param  MTT           The multi-TT of the hub device.

  @retval EFI_SUCCESS   Successfully configure the hub device's slot context.

**/
EFI_STATUS
XhcConfigHubContext (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    PortNum,
  IN UINT8                    TTT,
  IN UINT8                    MTT
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT               *InputContext;
  DEVICE_CONTEXT              *OutputContext;
  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  EFI_PHYSICAL_ADDRESS        PhyAddr;

  ASSERT (Xhc->UsbDevContext[SlotId].SlotId != 0);
  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;

  //
  // 4.6.7 Evaluate Context
  //
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT));

  InputContext->InputControlContext.Dword2 |= BIT0;

  //
  // Copy the slot context from OutputContext to Input context
  //
  CopyMem(&(InputContext->Slot), &(OutputContext->Slot), sizeof (SLOT_CONTEXT));
  InputContext->Slot.Hub     = 1;
  InputContext->Slot.PortNum = PortNum;
  InputContext->Slot.TTT     = TTT;
  InputContext->Slot.MTT     = MTT;

  ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT));
#else
  PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
  CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbCfgEP.CycleBit = 1;
  CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
  CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Configure Hub Slot Context\n"));
  Status = XhcCmdTransfer (
              Xhc,
              (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
              XHC_GENERIC_TIMEOUT,
              (TRB_TEMPLATE **) (UINTN) &EvtTrb
              );
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int)Status));
  }
  return Status;
}
#endif

/**
  Evaluate the slot context for hub device through XHCI's Configure_Endpoint cmd.

  @param  Xhc           The XHCI Instance.
  @param  SlotId        The slot id to be configured.
  @param  PortNum       The total number of downstream port supported by the hub.
  @param  TTT           The TT think time of the hub device.
  @param  MTT           The multi-TT of the hub device.

  @retval EFI_SUCCESS   Successfully configure the hub device's slot context.

**/
EFI_STATUS
XhcConfigHubContext64 (
  IN USB_XHCI_INSTANCE        *Xhc,
  IN UINT8                    SlotId,
  IN UINT8                    PortNum,
  IN UINT8                    TTT,
  IN UINT8                    MTT
  )
{
  EFI_STATUS                  Status;
  EVT_TRB_COMMAND_COMPLETION  *EvtTrb;
  INPUT_CONTEXT_64            *InputContext;
  DEVICE_CONTEXT_64           *OutputContext;
  CMD_TRB_CONFIG_ENDPOINT     CmdTrbCfgEP;
  EFI_PHYSICAL_ADDRESS        PhyAddr;

  ASSERT (Xhc->UsbDevContext[SlotId].SlotId != 0);
  InputContext  = Xhc->UsbDevContext[SlotId].InputContext;
  OutputContext = Xhc->UsbDevContext[SlotId].OutputContext;

  //
  // 4.6.7 Evaluate Context
  //
  ZeroMem (InputContext, sizeof (INPUT_CONTEXT_64));

  InputContext->InputControlContext.Dword2 |= BIT0;

  //
  // Copy the slot context from OutputContext to Input context
  //
  CopyMem(&(InputContext->Slot), &(OutputContext->Slot), sizeof (SLOT_CONTEXT_64));
  InputContext->Slot.Hub     = 1;
  InputContext->Slot.PortNum = PortNum;
  InputContext->Slot.TTT     = TTT;
  InputContext->Slot.MTT     = MTT;

  ZeroMem (&CmdTrbCfgEP, sizeof (CmdTrbCfgEP));
#if defined(OCTEONTX_NOT_USED)
  PhyAddr = UsbHcGetPciAddrForHostAddr (Xhc->MemPool, InputContext, sizeof (INPUT_CONTEXT_64));
#else
  PhyAddr = bdk_ptr_to_phys(InputContext);
#endif
  CmdTrbCfgEP.PtrLo    = XHC_LOW_32BIT (PhyAddr);
  CmdTrbCfgEP.PtrHi    = XHC_HIGH_32BIT (PhyAddr);
  CmdTrbCfgEP.CycleBit = 1;
  CmdTrbCfgEP.Type     = TRB_TYPE_CON_ENDPOINT;
  CmdTrbCfgEP.SlotId   = Xhc->UsbDevContext[SlotId].SlotId;
  DEBUG ((EFI_D_INFO, "Configure Hub Slot Context\n"));
  Status = XhcCmdTransfer (
              Xhc,
              (TRB_TEMPLATE *) (UINTN) &CmdTrbCfgEP,
              XHC_GENERIC_TIMEOUT,
              (TRB_TEMPLATE **) (UINTN) &EvtTrb
              );
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Config Endpoint Failed, Status = %d\n", (int)Status));
  }
  return Status;
}
