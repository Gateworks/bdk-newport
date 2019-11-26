/** @file

    Usb Bus Driver Binding and Bus IO Protocol.

Copyright (c) 2004 - 2013, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "UsbBus.h"

EFI_USB_IO_PROTOCOL mUsbIoProtocol = {
  UsbIoControlTransfer,
  UsbIoBulkTransfer,
  UsbIoAsyncInterruptTransfer,
  UsbIoSyncInterruptTransfer,
  UsbIoIsochronousTransfer,
  UsbIoAsyncIsochronousTransfer,
  UsbIoGetDeviceDescriptor,
  UsbIoGetActiveConfigDescriptor,
  UsbIoGetInterfaceDescriptor,
  UsbIoGetEndpointDescriptor,
  UsbIoGetStringDescriptor,
  UsbIoGetSupportedLanguages,
  UsbIoPortReset
};

/**
  USB_IO function to execute a control transfer. This
  function will execute the USB transfer. If transfer
  successes, it will sync the internal state of USB bus
  with device state.

  @param  This                   The USB_IO instance
  @param  Request                The control transfer request
  @param  Direction              Direction for data stage
  @param  Timeout                The time to wait before timeout
  @param  Data                   The buffer holding the data
  @param  DataLength             Then length of the data
  @param  UsbStatus              USB result

  @retval EFI_INVALID_PARAMETER  The parameters are invalid
  @retval EFI_SUCCESS            The control transfer succeeded.
  @retval Others                 Failed to execute the transfer

**/
EFI_STATUS
EFIAPI
UsbIoControlTransfer (
  IN  EFI_USB_IO_PROTOCOL     *This,
  IN  EFI_USB_DEVICE_REQUEST  *Request,
  IN  EFI_USB_DATA_DIRECTION  Direction,
  IN  UINT32                  Timeout,
  IN  OUT VOID                *Data,      OPTIONAL
  IN  UINTN                   DataLength, OPTIONAL
  OUT UINT32                  *UsbStatus
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  USB_ENDPOINT_DESC       *EpDesc;
  /* EFI_TPL                 OldTpl; */
  EFI_STATUS              Status;

  if (UsbStatus == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  Dev    = UsbIf->Device;

  Status = UsbHcControlTransfer (
             Dev->Bus,
             Dev->Address,
             Dev->Speed,
             Dev->MaxPacket0,
             Request,
             Direction,
             Data,
             &DataLength,
             (UINTN) Timeout,
             &Dev->Translator,
             UsbStatus
             );

  if (EFI_ERROR (Status) || (*UsbStatus != EFI_USB_NOERROR)) {
    //
    // Clear TT buffer when CTRL/BULK split transaction failes
    // Clear the TRANSLATOR TT buffer, not parent's buffer
    //
    ASSERT (Dev->Translator.TranslatorHubAddress < Dev->Bus->MaxDevices);
    if (Dev->Translator.TranslatorHubAddress != 0) {
      UsbHubCtrlClearTTBuffer (
        Dev->Bus->Devices[Dev->Translator.TranslatorHubAddress],
        Dev->Translator.TranslatorPortNumber,
        Dev->Address,
        0,
        USB_ENDPOINT_CONTROL
        );
    }

    goto ON_EXIT;
  }

  //
  // Some control transfer will change the device's internal
  // status, such as Set_Configuration and Set_Interface.
  // We must synchronize the bus driver's status with that in
  // device. We ignore the Set_Descriptor request because it's
  // hardly used by any device, especially in pre-boot environment
  //

  //
  // Reset the endpoint toggle when endpoint stall is cleared
  //
  if ((Request->Request     == USB_REQ_CLEAR_FEATURE) &&
      (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD,
                                                 USB_TARGET_ENDPOINT)) &&
      (Request->Value       == USB_FEATURE_ENDPOINT_HALT)) {

    EpDesc = UsbGetEndpointDesc (UsbIf, (UINT8) Request->Index);

    if (EpDesc != NULL) {
      EpDesc->Toggle = 0;
    }
  }

  //
  // Select a new configuration. This is a dangerous action. Upper driver
  // should stop use its current UsbIo after calling this driver. The old
  // UsbIo will be uninstalled and new UsbIo be installed. We can't use
  // ReinstallProtocol since interfaces in different configuration may be
  // completely irrelevant.
  //
  if ((Request->Request == USB_REQ_SET_CONFIG) &&
      (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD,
                                                 USB_TARGET_DEVICE))) {
    //
    // Don't re-create the USB interfaces if configuration isn't changed.
    //
    if ((Dev->ActiveConfig != NULL) &&
        (Request->Value == Dev->ActiveConfig->Desc.ConfigurationValue)) {

      goto ON_EXIT;
    }
    DEBUG ((EFI_D_INFO, "configure changed!!! Do NOT use old UsbIo!!!\n"));

    if (Dev->ActiveConfig != NULL) {
      UsbRemoveConfig (Dev);
    }

    if (Request->Value != 0) {
      Status = UsbSelectConfig (Dev, (UINT8) Request->Value);
    }

    //
    // Exit now, Old USB_IO is invalid now
    //
    goto ON_EXIT;
  }

  //
  // A new alternative setting is selected for the interface.
  // No need to reinstall UsbIo in this case because only
  // underlying communication endpoints are changed. Functionality
  // should remains the same.
  //
  if ((Request->Request     == USB_REQ_SET_INTERFACE) &&
      (Request->RequestType == USB_REQUEST_TYPE (EfiUsbNoData, USB_REQ_TYPE_STANDARD,
                                                 USB_TARGET_INTERFACE)) &&
      (Request->Index       == UsbIf->IfSetting->Desc.InterfaceNumber)) {

    Status = UsbSelectSetting (UsbIf->IfDesc, (UINT8) Request->Value);

    if (!EFI_ERROR (Status)) {
      ASSERT (UsbIf->IfDesc->ActiveIndex < USB_MAX_INTERFACE_SETTING);
      UsbIf->IfSetting = UsbIf->IfDesc->Settings[UsbIf->IfDesc->ActiveIndex];
    }
  }

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Execute a bulk transfer to the device endpoint.

  @param  This                   The USB IO instance.
  @param  Endpoint               The device endpoint.
  @param  Data                   The data to transfer.
  @param  DataLength             The length of the data to transfer.
  @param  Timeout                Time to wait before timeout.
  @param  UsbStatus              The result of USB transfer.

  @retval EFI_SUCCESS            The bulk transfer is OK.
  @retval EFI_INVALID_PARAMETER  Some parameters are invalid.
  @retval Others                 Failed to execute transfer, reason returned in
                                 UsbStatus.

**/
EFI_STATUS
EFIAPI
UsbIoBulkTransfer (
  IN  EFI_USB_IO_PROTOCOL *This,
  IN  UINT8               Endpoint,
  IN  OUT VOID            *Data,
  IN  OUT UINTN           *DataLength,
  IN  UINTN               Timeout,
  OUT UINT32              *UsbStatus
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  USB_ENDPOINT_DESC       *EpDesc;
  UINT8                   BufNum;
  UINT8                   Toggle;
  /* EFI_TPL                 OldTpl; */
  EFI_STATUS              Status;

  if ((USB_ENDPOINT_ADDR (Endpoint) == 0) || (USB_ENDPOINT_ADDR(Endpoint) > 15) ||
      (UsbStatus == NULL)) {

    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl  = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf   = USB_INTERFACE_FROM_USBIO (This);
  Dev     = UsbIf->Device;

  EpDesc  = UsbGetEndpointDesc (UsbIf, Endpoint);

  if ((EpDesc == NULL) || (USB_ENDPOINT_TYPE (&EpDesc->Desc) != USB_ENDPOINT_BULK)) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  BufNum  = 1;
  Toggle  = EpDesc->Toggle;
  Status  = UsbHcBulkTransfer (
              Dev->Bus,
              Dev->Address,
              Endpoint,
              Dev->Speed,
              EpDesc->Desc.MaxPacketSize,
              BufNum,
              &Data,
              DataLength,
              &Toggle,
              Timeout,
              &Dev->Translator,
              UsbStatus
              );

  EpDesc->Toggle = Toggle;

  if (EFI_ERROR (Status) || (*UsbStatus != EFI_USB_NOERROR)) {
    //
    // Clear TT buffer when CTRL/BULK split transaction failes.
    // Clear the TRANSLATOR TT buffer, not parent's buffer
    //
    ASSERT (Dev->Translator.TranslatorHubAddress < Dev->Bus->MaxDevices);
    if (Dev->Translator.TranslatorHubAddress != 0) {
      UsbHubCtrlClearTTBuffer (
        Dev->Bus->Devices[Dev->Translator.TranslatorHubAddress],
        Dev->Translator.TranslatorPortNumber,
        Dev->Address,
        0,
        USB_ENDPOINT_BULK
        );
    }
  }

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Execute a synchronous interrupt transfer.

  @param  This                   The USB IO instance.
  @param  Endpoint               The device endpoint.
  @param  Data                   The data to transfer.
  @param  DataLength             The length of the data to transfer.
  @param  Timeout                Time to wait before timeout.
  @param  UsbStatus              The result of USB transfer.

  @retval EFI_SUCCESS            The synchronous interrupt transfer is OK.
  @retval EFI_INVALID_PARAMETER  Some parameters are invalid.
  @retval Others                 Failed to execute transfer, reason returned in
                                 UsbStatus.

**/
EFI_STATUS
EFIAPI
UsbIoSyncInterruptTransfer (
  IN  EFI_USB_IO_PROTOCOL *This,
  IN  UINT8               Endpoint,
  IN  OUT VOID            *Data,
  IN  OUT UINTN           *DataLength,
  IN  UINTN               Timeout,
  OUT UINT32              *UsbStatus
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  USB_ENDPOINT_DESC       *EpDesc;
  /* EFI_TPL                 OldTpl; */
  UINT8                   Toggle;
  EFI_STATUS              Status;

  if ((USB_ENDPOINT_ADDR (Endpoint) == 0) || (USB_ENDPOINT_ADDR(Endpoint) > 15) ||
      (UsbStatus == NULL)) {

    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl  = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf   = USB_INTERFACE_FROM_USBIO (This);
  Dev     = UsbIf->Device;

  EpDesc  = UsbGetEndpointDesc (UsbIf, Endpoint);

  if ((EpDesc == NULL) || (USB_ENDPOINT_TYPE (&EpDesc->Desc) != USB_ENDPOINT_INTERRUPT)) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  Toggle = EpDesc->Toggle;
  Status = UsbHcSyncInterruptTransfer (
             Dev->Bus,
             Dev->Address,
             Endpoint,
             Dev->Speed,
             EpDesc->Desc.MaxPacketSize,
             Data,
             DataLength,
             &Toggle,
             Timeout,
             &Dev->Translator,
             UsbStatus
             );

  EpDesc->Toggle = Toggle;

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Queue a new asynchronous interrupt transfer, or remove the old
  request if (IsNewTransfer == FALSE).

  @param  This                   The USB_IO instance.
  @param  Endpoint               The device endpoint.
  @param  IsNewTransfer          Whether this is a new request, if it's old, remove
                                 the request.
  @param  PollInterval           The interval to poll the transfer result, (in ms).
  @param  DataLength             The length of perodic data transfer.
  @param  Callback               The function to call periodically when transfer is
                                 ready.
  @param  Context                The context to the callback.

  @retval EFI_SUCCESS            New transfer is queued or old request is removed.
  @retval EFI_INVALID_PARAMETER  Some parameters are invalid.
  @retval Others                 Failed to queue the new request or remove the old
                                 request.

**/
EFI_STATUS
EFIAPI
UsbIoAsyncInterruptTransfer (
  IN EFI_USB_IO_PROTOCOL              *This,
  IN UINT8                            Endpoint,
  IN BOOLEAN                          IsNewTransfer,
  IN UINTN                            PollInterval,       OPTIONAL
  IN UINTN                            DataLength,         OPTIONAL
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  Callback,           OPTIONAL
  IN VOID                             *Context            OPTIONAL
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  USB_ENDPOINT_DESC       *EpDesc;
  /* EFI_TPL                 OldTpl; */
  UINT8                   Toggle;
  EFI_STATUS              Status;

  if ((USB_ENDPOINT_ADDR (Endpoint) == 0) || (USB_ENDPOINT_ADDR (Endpoint) > 15)) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl  = gBS->RaiseTPL (USB_BUS_TPL); */
  UsbIf   = USB_INTERFACE_FROM_USBIO (This);
  Dev     = UsbIf->Device;

  EpDesc  = UsbGetEndpointDesc (UsbIf, Endpoint);

  if ((EpDesc == NULL) || (USB_ENDPOINT_TYPE (&EpDesc->Desc) != USB_ENDPOINT_INTERRUPT)) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  Toggle  = EpDesc->Toggle;
  Status  = UsbHcAsyncInterruptTransfer (
              Dev->Bus,
              Dev->Address,
              Endpoint,
              Dev->Speed,
              EpDesc->Desc.MaxPacketSize,
              IsNewTransfer,
              &Toggle,
              PollInterval,
              DataLength,
              &Dev->Translator,
              Callback,
              Context
              );

  EpDesc->Toggle = Toggle;

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Execute a synchronous isochronous transfer.

  @param  This                   The USB IO instance.
  @param  DeviceEndpoint         The device endpoint.
  @param  Data                   The data to transfer.
  @param  DataLength             The length of the data to transfer.
  @param  UsbStatus              The result of USB transfer.

  @retval EFI_UNSUPPORTED        Currently isochronous transfer isn't supported.

**/
EFI_STATUS
EFIAPI
UsbIoIsochronousTransfer (
  IN  EFI_USB_IO_PROTOCOL *This,
  IN  UINT8               DeviceEndpoint,
  IN  OUT VOID            *Data,
  IN  UINTN               DataLength,
  OUT UINT32              *Status
  )
{
  return EFI_UNSUPPORTED;
}


/**
  Queue an asynchronous isochronous transfer.

  @param  This                   The USB_IO instance.
  @param  DeviceEndpoint         The device endpoint.
  @param  Data                   The data to transfer.
  @param  DataLength             The length of perodic data transfer.
  @param  IsochronousCallBack    The function to call periodically when transfer is
                                 ready.
  @param  Context                The context to the callback.

  @retval EFI_UNSUPPORTED        Currently isochronous transfer isn't supported.

**/
EFI_STATUS
EFIAPI
UsbIoAsyncIsochronousTransfer (
  IN EFI_USB_IO_PROTOCOL              *This,
  IN UINT8                            DeviceEndpoint,
  IN OUT VOID                         *Data,
  IN UINTN                            DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallBack,
  IN VOID                             *Context              OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}


/**
  Retrieve the device descriptor of the device.

  @param  This                   The USB IO instance.
  @param  Descriptor             The variable to receive the device descriptor.

  @retval EFI_SUCCESS            The device descriptor is returned.
  @retval EFI_INVALID_PARAMETER  The parameter is invalid.

**/
EFI_STATUS
EFIAPI
UsbIoGetDeviceDescriptor (
  IN  EFI_USB_IO_PROTOCOL       *This,
  OUT EFI_USB_DEVICE_DESCRIPTOR *Descriptor
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  /* EFI_TPL                 OldTpl; */

  if (Descriptor == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  Dev    = UsbIf->Device;

  CopyMem (Descriptor, &Dev->DevDesc->Desc, sizeof (EFI_USB_DEVICE_DESCRIPTOR));

  /* gBS->RestoreTPL (OldTpl); */
  return EFI_SUCCESS;
}


/**
  Return the configuration descriptor of the current active configuration.

  @param  This                   The USB IO instance.
  @param  Descriptor             The USB configuration descriptor.

  @retval EFI_SUCCESS            The active configuration descriptor is returned.
  @retval EFI_INVALID_PARAMETER  Some parameter is invalid.
  @retval EFI_NOT_FOUND          Currently no active configuration is selected.

**/
EFI_STATUS
EFIAPI
UsbIoGetActiveConfigDescriptor (
  IN  EFI_USB_IO_PROTOCOL       *This,
  OUT EFI_USB_CONFIG_DESCRIPTOR *Descriptor
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  EFI_STATUS              Status;
  /* EFI_TPL                 OldTpl; */

  if (Descriptor == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  Dev    = UsbIf->Device;

  if (Dev->ActiveConfig == NULL) {
    Status = EFI_NOT_FOUND;
    goto ON_EXIT;
  }

  CopyMem (Descriptor, &(Dev->ActiveConfig->Desc), sizeof (EFI_USB_CONFIG_DESCRIPTOR));

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Retrieve the active interface setting descriptor for this USB IO instance.

  @param  This                   The USB IO instance.
  @param  Descriptor             The variable to receive active interface setting.

  @retval EFI_SUCCESS            The active interface setting is returned.
  @retval EFI_INVALID_PARAMETER  Some parameter is invalid.

**/
EFI_STATUS
EFIAPI
UsbIoGetInterfaceDescriptor (
  IN  EFI_USB_IO_PROTOCOL           *This,
  OUT EFI_USB_INTERFACE_DESCRIPTOR  *Descriptor
  )
{
  USB_INTERFACE           *UsbIf;
  /* EFI_TPL                 OldTpl; */

  if (Descriptor == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  CopyMem (Descriptor, &(UsbIf->IfSetting->Desc), sizeof (EFI_USB_INTERFACE_DESCRIPTOR));

  /* gBS->RestoreTPL (OldTpl); */
  return EFI_SUCCESS;
}


/**
  Retrieve the endpoint descriptor from this interface setting.

  @param  This                   The USB IO instance.
  @param  Index                  The index (start from zero) of the endpoint to
                                 retrieve.
  @param  Descriptor             The variable to receive the descriptor.

  @retval EFI_SUCCESS            The endpoint descriptor is returned.
  @retval EFI_INVALID_PARAMETER  Some parameter is invalid.

**/
EFI_STATUS
EFIAPI
UsbIoGetEndpointDescriptor (
  IN  EFI_USB_IO_PROTOCOL         *This,
  IN  UINT8                       Index,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR *Descriptor
  )
{
  USB_INTERFACE           *UsbIf;
  /* EFI_TPL                 OldTpl; */

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);

  if ((Descriptor == NULL) || (Index > 15)) {
    /* gBS->RestoreTPL (OldTpl); */
    return EFI_INVALID_PARAMETER;
  }

  if (Index >= UsbIf->IfSetting->Desc.NumEndpoints) {
    /* gBS->RestoreTPL (OldTpl); */
    return EFI_NOT_FOUND;
  }

  CopyMem (
    Descriptor,
    &(UsbIf->IfSetting->Endpoints[Index]->Desc),
    sizeof (EFI_USB_ENDPOINT_DESCRIPTOR)
    );

  /* gBS->RestoreTPL (OldTpl); */
  return EFI_SUCCESS;
}


/**
  Retrieve the supported language ID table from the device.

  @param  This                   The USB IO instance.
  @param  LangIDTable            The table to return the language IDs.
  @param  TableSize              The size, in bytes, of the table LangIDTable.

  @retval EFI_SUCCESS            The language ID is return.

**/
EFI_STATUS
EFIAPI
UsbIoGetSupportedLanguages (
  IN  EFI_USB_IO_PROTOCOL *This,
  OUT UINT16              **LangIDTable,
  OUT UINT16              *TableSize
  )
{
  USB_DEVICE              *Dev;
  USB_INTERFACE           *UsbIf;
  /* EFI_TPL                 OldTpl; */

  /* OldTpl        = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf         = USB_INTERFACE_FROM_USBIO (This);
  Dev           = UsbIf->Device;

  *LangIDTable  = Dev->LangId;
  *TableSize    = (UINT16) (Dev->TotalLangId * sizeof (UINT16));

  /* gBS->RestoreTPL (OldTpl); */
  return EFI_SUCCESS;
}


/**
  Retrieve an indexed string in the language of LangID.

  @param  This                   The USB IO instance.
  @param  LangID                 The language ID of the string to retrieve.
  @param  StringIndex            The index of the string.
  @param  String                 The variable to receive the string.

  @retval EFI_SUCCESS            The string is returned.
  @retval EFI_NOT_FOUND          No such string existed.

**/
EFI_STATUS
EFIAPI
UsbIoGetStringDescriptor (
  IN  EFI_USB_IO_PROTOCOL   *This,
  IN  UINT16                LangID,
  IN  UINT8                 StringIndex,
  OUT CHAR16                **String
  )
{
  USB_DEVICE                *Dev;
  USB_INTERFACE             *UsbIf;
  EFI_USB_STRING_DESCRIPTOR *StrDesc;
  /* EFI_TPL                   OldTpl; */
  UINT8                     *Buf;
  UINT8                     Index;
  EFI_STATUS                Status;

  if ((StringIndex == 0) || (LangID == 0)) {
    return EFI_NOT_FOUND;
  }

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  Dev    = UsbIf->Device;

  //
  // Check whether language ID is supported
  //
  Status = EFI_NOT_FOUND;

  for (Index = 0; Index < Dev->TotalLangId; Index++) {
    ASSERT (Index < USB_MAX_LANG_ID);
    if (Dev->LangId[Index] == LangID) {
      break;
    }
  }

  if (Index == Dev->TotalLangId) {
    goto ON_EXIT;
  }

  //
  // Retrieve the string descriptor then allocate a buffer
  // to hold the string itself.
  //
  StrDesc = UsbGetOneString (Dev, StringIndex, LangID);

  if (StrDesc == NULL) {
    goto ON_EXIT;
  }

  if (StrDesc->Length <= 2) {
    goto FREE_STR;
  }

  Buf = AllocateZeroPool (StrDesc->Length);

  if (Buf == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto FREE_STR;
  }

  CopyMem (Buf, StrDesc->String, StrDesc->Length - 2);
  *String = (CHAR16 *) Buf;
  Status  = EFI_SUCCESS;

FREE_STR:
#if defined(OCTEONTX_NOT_USED)
  gBS->FreePool (StrDesc);
#else
  free(StrDesc);
#endif
ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Reset the device, then if that succeeds, reconfigure the
  device with its address and current active configuration.

  @param  This                   The USB IO instance.

  @retval EFI_SUCCESS            The device is reset and configured.
  @retval Others                 Failed to reset the device.

**/
EFI_STATUS
EFIAPI
UsbIoPortReset (
  IN EFI_USB_IO_PROTOCOL  *This
  )
{
  USB_INTERFACE           *UsbIf;
  USB_INTERFACE           *HubIf;
  USB_DEVICE              *Dev;
  /* EFI_TPL                 OldTpl; */
  EFI_STATUS              Status;
  UINT8                   DevAddress;

  /* OldTpl = gBS->RaiseTPL (USB_BUS_TPL); */

  UsbIf  = USB_INTERFACE_FROM_USBIO (This);
  Dev    = UsbIf->Device;

  if (UsbIf->IsHub) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  HubIf  = Dev->ParentIf;
  Status = HubIf->HubApi->ResetPort (HubIf, Dev->ParentPort);

  if (EFI_ERROR (Status)) {
    DEBUG (( EFI_D_ERROR, "failed to reset hub port %d@hub  %d, %d \n",
                Dev->ParentPort, Dev->ParentAddr, (int) Status));

    goto ON_EXIT;
  }

  HubIf->HubApi->ClearPortChange (HubIf, Dev->ParentPort);

  //
  // Reset the device to its current address. The device now has an address
  // of ZERO after port reset, so need to set Dev->Address to the device again for
  // host to communicate with it.
  //
  DevAddress   = Dev->Address;
  Dev->Address = 0;
  Status  = UsbSetAddress (Dev, DevAddress);
  Dev->Address = DevAddress;
#if defined(OCTEONTX_NOT_USED)
  gBS->Stall (USB_SET_DEVICE_ADDRESS_STALL);
#else
  bdk_wait_usec(USB_SET_DEVICE_ADDRESS_STALL);
#endif
  if (EFI_ERROR (Status)) {
    //
    // It may fail due to device disconnection or other reasons.
    //
    DEBUG (( EFI_D_ERROR, "failed to set address for device %d - %d\n",
                Dev->Address, (int) Status));

    goto ON_EXIT;
  }

  DEBUG (( EFI_D_INFO, "device is now ADDRESSED at %d\n", Dev->Address));

  //
  // Reset the current active configure, after this device
  // is in CONFIGURED state.
  //
  if (Dev->ActiveConfig != NULL) {
    Status = UsbSetConfig (Dev, Dev->ActiveConfig->Desc.ConfigurationValue);

    if (EFI_ERROR (Status)) {
      DEBUG (( EFI_D_ERROR, "failed to set configure for device %d - %d\n",
                  Dev->Address, (int) Status));
    }
  }

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}

#if defined(OCTEONTX_NOT_USED)


/**
  Install Usb Bus Protocol on host controller, and start the Usb bus.

  @param This                    The USB bus driver binding instance.
  @param Controller              The controller to check.
  @param RemainingDevicePath     The remaining device patch.

  @retval EFI_SUCCESS            The controller is controlled by the usb bus.
  @retval EFI_ALREADY_STARTED    The controller is already controlled by the usb bus.
  @retval EFI_OUT_OF_RESOURCES   Failed to allocate resources.

**/
EFI_STATUS
EFIAPI
UsbBusBuildProtocol (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  USB_BUS                 *UsbBus;
  USB_DEVICE              *RootHub;
  USB_INTERFACE           *RootIf;
  EFI_STATUS              Status;

  UsbBus = AllocateZeroPool (sizeof (USB_BUS));

  if (UsbBus == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  /* UsbBus->Signature  = USB_BUS_SIGNATURE; */
  UsbBus->HostHandle = Controller;
  UsbBus->MaxDevices = USB_MAX_DEVICES;
#if defined(OCTEONTX_NOT_USED)
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &UsbBus->DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to open device path %d\n", (int) Status));

    FreePool (UsbBus);
    return Status;
  }

  //
  // Get USB_HC2/USB_HC host controller protocol (EHCI/UHCI).
  // This is for backward compatibility with EFI 1.x. In UEFI
  // 2.x, USB_HC2 replaces USB_HC. We will open both USB_HC2
  // and USB_HC because EHCI driver will install both protocols
  // (for the same reason). If we don't consume both of them,
  // the unconsumed one may be opened by others.
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiUsb2HcProtocolGuid,
                  (VOID **) &(UsbBus->Usb2Hc),
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  EFI_STATUS              Status2;

  Status2 = gBS->OpenProtocol (
                   Controller,
                   &gEfiUsbHcProtocolGuid,
                   (VOID **) &(UsbBus->UsbHc),
                   This->DriverBindingHandle,
                   Controller,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );

  if (EFI_ERROR (Status) && EFI_ERROR (Status2)) {
    DEBUG ((EFI_D_ERROR, "Failed to open USB_HC/USB2_HC %d\n", (int) Status));

    Status = EFI_DEVICE_ERROR;
    goto CLOSE_HC;
  }
#else
  CAVIUM_NOTYET("Build protocols Device and Usb2Hc");
Status = EFI_SUCCESS;
#endif
  if (!EFI_ERROR (Status)) {
    //
    // The EFI_USB2_HC_PROTOCOL is produced for XHCI support.
    // Then its max supported devices are 256. Otherwise it's 128.
    //
    ASSERT (UsbBus->Usb2Hc != NULL);
    if (UsbBus->Usb2Hc->MajorRevision == 0x3) {
      UsbBus->MaxDevices = 256;
    }
  }

  UsbHcReset (UsbBus, EFI_USB_HC_RESET_GLOBAL);
  UsbHcSetState (UsbBus, EfiUsbHcStateOperational);

  //
  // Install an EFI_USB_BUS_PROTOCOL to host controller to identify it.
  //
#if defined(OCTEONTX_NOT_USED)
  Status = gBS->InstallProtocolInterface (
                  &Controller,
                  &gEfiCallerIdGuid,
                  EFI_NATIVE_INTERFACE,
                  &UsbBus->BusId
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to install bus protocol %d\n", (int) Status));
    goto CLOSE_HC;
  }
#else
CAVIUM_NOTYET(InstallProtocolInterface);
Status = EFI_SUCCESS;
#endif
  //
  // Initial the wanted child device path list, and add first RemainingDevicePath
  //
  InitializeListHead (&UsbBus->WantedUsbIoDPList);
  Status = UsbBusAddWantedUsbIoDP (&UsbBus->BusId, RemainingDevicePath);
  ASSERT (!EFI_ERROR (Status));
  //
  // Create a fake usb device for root hub
  //
  RootHub = AllocateZeroPool (sizeof (USB_DEVICE));

  if (RootHub == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto UNINSTALL_USBBUS;
  }

  RootIf = AllocateZeroPool (sizeof (USB_INTERFACE));

  if (RootIf == NULL) {
    FreePool (RootHub);
    Status = EFI_OUT_OF_RESOURCES;
    goto FREE_ROOTHUB;
  }

  RootHub->Bus            = UsbBus;
  RootHub->NumOfInterface = 1;
  RootHub->Interfaces[0]  = RootIf;
  RootHub->Tier           = 0;
  /* RootIf->Signature       = USB_INTERFACE_SIGNATURE; */
  RootIf->Device          = RootHub;
  RootIf->DevicePath      = UsbBus->DevicePath;

  //
  // Report Status Code here since we will enumerate the USB devices
  //
  REPORT_STATUS_CODE_WITH_DEVICE_PATH (
    EFI_PROGRESS_CODE,
    (EFI_IO_BUS_USB | EFI_IOB_PC_DETECT),
    UsbBus->DevicePath
    );

  Status                  = mUsbRootHubApi.Init (RootIf);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to init root hub %d\n", (int) Status));
    goto FREE_ROOTHUB;
  }

  UsbBus->Devices[0] = RootHub;

  DEBUG ((EFI_D_INFO, "usb bus started on %p, root hub %p\n", Controller, RootIf));
  return EFI_SUCCESS;

FREE_ROOTHUB:
  if (RootIf != NULL) {
    FreePool (RootIf);
  }
  if (RootHub != NULL) {
    FreePool (RootHub);
  }

UNINSTALL_USBBUS:
#if defined(OCTEONTX_NOT_USED)
  gBS->UninstallProtocolInterface (Controller, &gEfiCallerIdGuid, &UsbBus->BusId);

CLOSE_HC:
  if (UsbBus->Usb2Hc != NULL) {
    gBS->CloseProtocol (
          Controller,
          &gEfiUsb2HcProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );
  }
  if (UsbBus->UsbHc != NULL) {
    gBS->CloseProtocol (
          Controller,
          &gEfiUsbHcProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );
  }
  gBS->CloseProtocol (
         Controller,
         &gEfiDevicePathProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );
#else
//CLOSE_HC:
#endif
  FreePool (UsbBus);

  DEBUG ((EFI_D_ERROR, "Failed to start bus driver %d\n", (int) Status));
  return Status;
}
#endif
