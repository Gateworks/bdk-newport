/** @file
  USB Mass Storage Driver that manages USB Mass Storage Device and produces Block I/O Protocol.

Copyright (c) 2007 - 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#if defined(notdef_cavium)
#include "UsbMass.h"

#define USB_MASS_TRANSPORT_COUNT    3
//
// Array of USB transport interfaces.
//
USB_MASS_TRANSPORT *mUsbMassTransport[USB_MASS_TRANSPORT_COUNT] = {
  &mUsbCbi0Transport,
  &mUsbCbi1Transport,
  &mUsbBotTransport,
};

EFI_DRIVER_BINDING_PROTOCOL gUSBMassDriverBinding = {
  USBMassDriverBindingSupported,
  USBMassDriverBindingStart,
  USBMassDriverBindingStop,
  0x11,
  NULL,
  NULL
};
#else
#include <bdk.h>
#include "Xhci.h" // need  cvm_usbif2node
#include "UsbBus.h"
#include "UsbMass.h"
#include "UsbMassImpl.h"

#define USB_MASS_TRANSPORT_COUNT    1
USB_MASS_TRANSPORT *mUsbMassTransport[USB_MASS_TRANSPORT_COUNT] = {
  &mUsbBotTransport,
};
#endif
/**
  Reset the block device.

  This function implements EFI_BLOCK_IO_PROTOCOL.Reset().
  It resets the block device hardware.
  ExtendedVerification is ignored in this implementation.

  @param  This                   Indicates a pointer to the calling context.
  @param  ExtendedVerification   Indicates that the driver may perform a more exhaustive
                                 verification operation of the device during reset.

  @retval EFI_SUCCESS            The block device was reset.
  @retval EFI_DEVICE_ERROR       The block device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
UsbMassReset (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN BOOLEAN                  ExtendedVerification
  )
{
  USB_MASS_DEVICE *UsbMass;
  /* EFI_TPL         OldTpl; */
  EFI_STATUS      Status;

  //
  // Raise TPL to TPL_NOTIFY to serialize all its operations
  // to protect shared data structures.
  //
  /* OldTpl  = gBS->RaiseTPL (TPL_CALLBACK); */

  UsbMass = USB_MASS_DEVICE_FROM_BLOCK_IO (This);
  Status  = UsbMass->Transport->Reset (UsbMass->Context, ExtendedVerification);

  /* gBS->RestoreTPL (OldTpl); */

  return Status;
}

/**
  Reads the requested number of blocks from the device.

  This function implements EFI_BLOCK_IO_PROTOCOL.ReadBlocks().
  It reads the requested number of blocks from the device.
  All the blocks are read, or an error is returned.

  @param  This                   Indicates a pointer to the calling context.
  @param  MediaId                The media ID that the read request is for.
  @param  Lba                    The starting logical block address to read from on the device.
  @param  BufferSize             The size of the Buffer in bytes.
                                 This must be a multiple of the intrinsic block size of the device.
  @param  Buffer                 A pointer to the destination buffer for the data. The caller is
                                 responsible for either having implicit or explicit ownership of the buffer.

  @retval EFI_SUCCESS            The data was read correctly from the device.
  @retval EFI_DEVICE_ERROR       The device reported an error while attempting to perform the read operation.
  @retval EFI_NO_MEDIA           There is no media in the device.
  @retval EFI_MEDIA_CHANGED      The MediaId is not for the current media.
  @retval EFI_BAD_BUFFER_SIZE    The BufferSize parameter is not a multiple of the intrinsic block size of the device.
  @retval EFI_INVALID_PARAMETER  The read request contains LBAs that are not valid,
                                 or the buffer is not on proper alignment.

**/
EFI_STATUS
EFIAPI
UsbMassReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN UINT32                   MediaId,
  IN EFI_LBA                  Lba,
  IN UINTN                    BufferSize,
  OUT VOID                    *Buffer
  )
{
  USB_MASS_DEVICE     *UsbMass;
  EFI_BLOCK_IO_MEDIA  *Media;
  EFI_STATUS          Status;
  /* EFI_TPL             OldTpl; */
  UINTN               TotalBlock;

  //
  // Raise TPL to TPL_NOTIFY to serialize all its operations
  // to protect shared data structures.
  //
  /* OldTpl  = gBS->RaiseTPL (TPL_CALLBACK); */
  UsbMass = USB_MASS_DEVICE_FROM_BLOCK_IO (This);
  Media   = &UsbMass->BlockIoMedia;

  //
  // If it is a removable media, such as CD-Rom or Usb-Floppy,
  // need to detect the media before each read/write. While some of
  // Usb-Flash is marked as removable media.
  //
#if !defined(notdef_cavium)
  if (Media->RemovableMedia) {
      // Will detect media change or removal
      Status = UsbBootIsUnitReady (UsbMass);
      if (EFI_ERROR (Status)) {
          goto ON_EXIT;
      }
  }
#else
  if (Media->RemovableMedia) {
    Status = UsbBootDetectMedia (UsbMass);
    if (EFI_ERROR (Status)) {
      goto ON_EXIT;
    }
  }

  if (!(Media->MediaPresent)) {
    Status = EFI_NO_MEDIA;
    goto ON_EXIT;
  }

  if (MediaId != Media->MediaId) {
    Status = EFI_MEDIA_CHANGED;
    goto ON_EXIT;
  }
#endif
  if (BufferSize == 0) {
    Status = EFI_SUCCESS;
    goto ON_EXIT;
  }

  if (Buffer == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  //
  // BufferSize must be a multiple of the intrinsic block size of the device.
  //
  if ((BufferSize % Media->BlockSize) != 0) {
    Status = EFI_BAD_BUFFER_SIZE;
    goto ON_EXIT;
  }

  TotalBlock = BufferSize / Media->BlockSize;

  //
  // Make sure the range to read is valid.
  //
  if (Lba + TotalBlock - 1 > Media->LastBlock) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  if (UsbMass->Cdb16Byte) {
    Status = UsbBootReadBlocks16 (UsbMass, Lba, TotalBlock, Buffer);
  } else {
    Status = UsbBootReadBlocks (UsbMass, (UINT32) Lba, TotalBlock, Buffer);
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UsbBootReadBlocks (%d) -> Reset\n", (int) Status));
    //UsbMassReset (This, TRUE);
    Status = EFI_DO_RESET;
  }

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}


/**
  Writes a specified number of blocks to the device.

  This function implements EFI_BLOCK_IO_PROTOCOL.WriteBlocks().
  It writes a specified number of blocks to the device.
  All blocks are written, or an error is returned.

  @param  This                   Indicates a pointer to the calling context.
  @param  MediaId                The media ID that the write request is for.
  @param  Lba                    The starting logical block address to be written.
  @param  BufferSize             The size of the Buffer in bytes.
                                 This must be a multiple of the intrinsic block size of the device.
  @param  Buffer                 Pointer to the source buffer for the data.

  @retval EFI_SUCCESS            The data were written correctly to the device.
  @retval EFI_WRITE_PROTECTED    The device cannot be written to.
  @retval EFI_NO_MEDIA           There is no media in the device.
  @retval EFI_MEDIA_CHANGED      The MediaId is not for the current media.
  @retval EFI_DEVICE_ERROR       The device reported an error while attempting to perform the write operation.
  @retval EFI_BAD_BUFFER_SIZE    The BufferSize parameter is not a multiple of the intrinsic
                                 block size of the device.
  @retval EFI_INVALID_PARAMETER  The write request contains LBAs that are not valid,
                                 or the buffer is not on proper alignment.

**/
EFI_STATUS
EFIAPI
UsbMassWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN UINT32                   MediaId,
  IN EFI_LBA                  Lba,
  IN UINTN                    BufferSize,
  CONST IN VOID                     *Buffer
  )
{
  USB_MASS_DEVICE     *UsbMass;
  EFI_BLOCK_IO_MEDIA  *Media;
  EFI_STATUS          Status;
  /* EFI_TPL             OldTpl; */
  UINTN               TotalBlock;

  //
  // Raise TPL to TPL_NOTIFY to serialize all its operations
  // to protect shared data structures.
  //
  /* OldTpl  = gBS->RaiseTPL (TPL_CALLBACK); */
  UsbMass = USB_MASS_DEVICE_FROM_BLOCK_IO (This);
  Media   = &UsbMass->BlockIoMedia;

  //
  // If it is a removable media, such as CD-Rom or Usb-Floppy,
  // need to detect the media before each read/write. Some of
  // USB Flash is marked as removable media.
  //
#if !defined(notdef_cavium)
  if (Media->RemovableMedia) {
      // Will detect media change or removal
      Status = UsbBootIsUnitReady (UsbMass);
      if (EFI_ERROR (Status)) {
          goto ON_EXIT;
      }
  }
#else
  if (Media->RemovableMedia) {
    Status = UsbBootDetectMedia (UsbMass);
    if (EFI_ERROR (Status)) {
      goto ON_EXIT;
    }
  }

  if (!(Media->MediaPresent)) {
    Status = EFI_NO_MEDIA;
    goto ON_EXIT;
  }

  if (MediaId != Media->MediaId) {
    Status = EFI_MEDIA_CHANGED;
    goto ON_EXIT;
  }
#endif
  if (BufferSize == 0) {
    Status = EFI_SUCCESS;
    goto ON_EXIT;
  }

  if (Buffer == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  //
  // BufferSize must be a multiple of the intrinsic block size of the device.
  //
  if ((BufferSize % Media->BlockSize) != 0) {
    Status = EFI_BAD_BUFFER_SIZE;
    goto ON_EXIT;
  }

  TotalBlock = BufferSize / Media->BlockSize;

  //
  // Make sure the range to write is valid.
  //
  if (Lba + TotalBlock - 1 > Media->LastBlock) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  //
  // Try to write the data even the device is marked as ReadOnly,
  // and clear the status should the write succeed.
  //
  if (UsbMass->Cdb16Byte) {
    Status = UsbBootWriteBlocks16 (UsbMass, Lba, TotalBlock, Buffer);
  } else {
    Status = UsbBootWriteBlocks (UsbMass, (UINT32) Lba, TotalBlock, Buffer);
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UsbBootWriteBlocks (%d) -> Reset\n", (int) Status));
    // UsbMassReset (This, TRUE);
    Status = EFI_DO_RESET;
  }

ON_EXIT:
  /* gBS->RestoreTPL (OldTpl); */
  return Status;
}

/**
  Flushes all modified data to a physical block device.

  This function implements EFI_BLOCK_IO_PROTOCOL.FlushBlocks().
  USB mass storage device doesn't support write cache,
  so return EFI_SUCCESS directly.

  @param  This                   Indicates a pointer to the calling context.

  @retval EFI_SUCCESS            All outstanding data were written correctly to the device.
  @retval EFI_DEVICE_ERROR       The device reported an error while attempting to write data.
  @retval EFI_NO_MEDIA           There is no media in the device.

**/
EFI_STATUS
EFIAPI
UsbMassFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}

/**
  Initialize the media parameter data for EFI_BLOCK_IO_MEDIA of Block I/O Protocol.

  @param  UsbMass                The USB mass storage device

  @retval EFI_SUCCESS            The media parameters are updated successfully.
  @retval Others                 Failed to get the media parameters.

**/
static EFI_STATUS
UsbMassInitMedia (
  IN USB_MASS_DEVICE          *UsbMass
  )
{
  EFI_BLOCK_IO_MEDIA          *Media;
  EFI_STATUS                  Status;

  Media = &UsbMass->BlockIoMedia;

  //
  // Fields of EFI_BLOCK_IO_MEDIA are defined in UEFI 2.0 spec,
  // section for Block I/O Protocol.
  //
  Media->MediaPresent     = FALSE;
  Media->LogicalPartition = FALSE;
  Media->ReadOnly         = FALSE;
  Media->WriteCaching     = FALSE;
  Media->IoAlign          = 0;
  Media->MediaId          = 1;

  Status = UsbBootGetParams (UsbMass);
  return Status;
}
#if defined(notdef_cavium)
/**
  Initialize data for device that supports multiple LUNSs.

  @param  This                 The Driver Binding Protocol instance.
  @param  Controller           The device to initialize.
  @param  Transport            Pointer to USB_MASS_TRANSPORT.
  @param  Context              Parameter for USB_MASS_DEVICE.Context.
  @param  DevicePath           The remaining device path.
  @param  MaxLun               The max LUN number.

  @retval EFI_SUCCESS          At least one LUN is initialized successfully.
  @retval EFI_NOT_FOUND        Fail to initialize any of multiple LUNs.

**/
static
EFI_STATUS
UsbMassInitMultiLun (
  IN EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN EFI_HANDLE                    Controller,
  IN USB_MASS_TRANSPORT            *Transport,
  IN VOID                          *Context,
  IN EFI_DEVICE_PATH_PROTOCOL      *DevicePath,
  IN UINT8                         MaxLun
  )
{
  USB_MASS_DEVICE                  *UsbMass;
  EFI_USB_IO_PROTOCOL              *UsbIo;
  DEVICE_LOGICAL_UNIT_DEVICE_PATH  LunNode;
  UINT8                            Index;
  EFI_STATUS                       Status;
  EFI_STATUS                       ReturnStatus;

  ASSERT (MaxLun > 0);
  ReturnStatus = EFI_NOT_FOUND;

  for (Index = 0; Index <= MaxLun; Index++) {

    DEBUG ((EFI_D_INFO, "Start to initialize No.%d logic unit\n", Index));

    UsbIo   = NULL;
    UsbMass = AllocateZeroPool (sizeof (USB_MASS_DEVICE));
    ASSERT (UsbMass != NULL);

    UsbMass->Signature            = USB_MASS_SIGNATURE;
    UsbMass->UsbIo                = UsbIo;
    UsbMass->BlockIo.Media        = &UsbMass->BlockIoMedia;
    UsbMass->BlockIo.Reset        = UsbMassReset;
    UsbMass->BlockIo.ReadBlocks   = UsbMassReadBlocks;
    UsbMass->BlockIo.WriteBlocks  = UsbMassWriteBlocks;
    UsbMass->BlockIo.FlushBlocks  = UsbMassFlushBlocks;
    UsbMass->OpticalStorage       = FALSE;
    UsbMass->Transport            = Transport;
    UsbMass->Context              = Context;
    UsbMass->Lun                  = Index;

    //
    // Initialize the media parameter data for EFI_BLOCK_IO_MEDIA of Block I/O Protocol.
    //
    Status = UsbMassInitMedia (UsbMass);
    if ((EFI_ERROR (Status)) && (Status != EFI_NO_MEDIA)) {
      DEBUG ((EFI_D_ERROR, "UsbMassInitMedia (%d)\n", (int) Status));
      FreePool (UsbMass);
      continue;
    }

    //
    // Create a device path node for device logic unit, and append it.
    //
    LunNode.Header.Type    = MESSAGING_DEVICE_PATH;
    LunNode.Header.SubType = MSG_DEVICE_LOGICAL_UNIT_DP;
    LunNode.Lun            = UsbMass->Lun;

    SetDevicePathNodeLength (&LunNode.Header, sizeof (LunNode));

    UsbMass->DevicePath = AppendDevicePathNode (DevicePath, &LunNode.Header);

    if (UsbMass->DevicePath == NULL) {
      DEBUG ((EFI_D_ERROR, "failed to create device logic unit device path\n"));
      Status = EFI_OUT_OF_RESOURCES;
      FreePool (UsbMass);
      continue;
    }

    InitializeDiskInfo (UsbMass);

    //
    // Create a new handle for each LUN, and install Block I/O Protocol and Device Path Protocol.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &UsbMass->Controller,
                    &gEfiDevicePathProtocolGuid,
                    UsbMass->DevicePath,
                    &gEfiBlockIoProtocolGuid,
                    &UsbMass->BlockIo,
                    &gEfiDiskInfoProtocolGuid,
                    &UsbMass->DiskInfo,
                    NULL
                    );

    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "InstallMultipleProtocolInterfaces (%d)\n", (int) Status));
      FreePool (UsbMass->DevicePath);
      FreePool (UsbMass);
      continue;
    }

    //
    // Open USB I/O Protocol by child to setup a parent-child relationship.
    //
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiUsbIoProtocolGuid,
                    (VOID **) &UsbIo,
                    This->DriverBindingHandle,
                    UsbMass->Controller,
                    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                    );

    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "OpenUsbIoProtocol By Child (%d)\n", (int) Status));
      gBS->UninstallMultipleProtocolInterfaces (
             &UsbMass->Controller,
             &gEfiDevicePathProtocolGuid,
             UsbMass->DevicePath,
             &gEfiBlockIoProtocolGuid,
             &UsbMass->BlockIo,
             &gEfiDiskInfoProtocolGuid,
             &UsbMass->DiskInfo,
             NULL
             );
      FreePool (UsbMass->DevicePath);
      FreePool (UsbMass);
      continue;
    }
    ReturnStatus = EFI_SUCCESS;
    DEBUG ((EFI_D_INFO, "Success to initialize No.%d logic unit\n", Index));
  }

  return ReturnStatus;
}

#endif
/*
** cavium bdk portion
*/

/* Accounting of active usb mass storage devices */
typedef struct _MASSDEV
{
    USB_INTERFACE * volatile ifHandle; // Interface handle provided by USB HCI layer
    USB_MASS_DEVICE * volatile UsbMass; // Pointer to UsbMassDevice
} MASSDEV;

static bdk_rlock_t musb_list_lock = {0,0};
static MASSDEV musb_list[8];

/*
** Cavium IO methods for /dev/nX.usbY
*/

/*
** Internal helper to reset port after the failure to read or write blocks.
** Unlike stock one it accounts for possibility that device was removed
** Caller is expected to hold bus lock.
** Lock is released by reset routine if at all possible.
**
** @param UsbMass 	Pointer to usb mass context
** @param devIndex      Index assigned to usb device, ie X in "/dev/n0.usbX"
**
** @retval EFI_STATUS
*/
static
int cvm_do_reset(USB_MASS_DEVICE *UsbMass, const int devIndex)
{
    bdk_rlock_lock(&musb_list_lock);
    USB_INTERFACE *thisUsbIf = musb_list[devIndex].ifHandle;
    bdk_rlock_unlock(&musb_list_lock);
    if (NULL == thisUsbIf) return EFI_INVALID_PARAMETER;
    if (musb_list[devIndex].UsbMass != UsbMass) return EFI_INVALID_PARAMETER;

    // We are doing reset because of previous hard error.
    // Device may have been physically disturbed.
    // Normal root hub enumeration is not running because our caller holds bus lock.
    // a) Run enumeration and async transfer checks on the root complex,
    //   this interface belongs to
    // b) Check if the device still exists.
    // c) If it does exist, reset it.

    // a) Poll root complex
    bdk_node_t if_node;
    int if_phys_port ;
    if (cvm_usbif2node(thisUsbIf, &if_node, &if_phys_port, NULL))
        return EFI_INVALID_PARAMETER;
    bdk_rlock_t *my_bus_lock = UsbMass->bus_lock; // Get bus lock address while we have it
    bdk_usb_HCPoll(if_node,if_phys_port,0); // skip locking as we are holding the lock

    // b) Check that device is still there
    if ((UsbMass != musb_list[devIndex].UsbMass) ||
        (thisUsbIf !=  musb_list[devIndex].ifHandle))
    {
        BDK_TRACE(USB_XHCI, "DevIndex %d have been removed from node %d port %d\n",
                  devIndex, if_node, if_phys_port);
        bdk_rlock_unlock(my_bus_lock);
        return EFI_MEDIA_CHANGED;
    }
    // c) If we got here, do reset
    int Status = UsbMassReset(&UsbMass->BlockIo,TRUE);
    bdk_rlock_unlock(my_bus_lock);
    return Status;
}

static USB_MASS_DEVICE *findUsbMass(const unsigned index, const bool lockIt) {
    if ( index   >= ARRAY_SIZE(musb_list)) {
        DEBUG((EFI_D_ERROR,"Index %u out of bounds max %lu\n",index,ARRAY_SIZE(musb_list) ));
        return NULL;
    }
    USB_MASS_DEVICE *UsbMass = musb_list[index].UsbMass;
    if (lockIt) {
        if (NULL == UsbMass) {
            DEBUG((EFI_D_ERROR,"Index %d points to empty slot\n",index ));
            return NULL;
        }
        bdk_rlock_lock(UsbMass->bus_lock);
    }
    return UsbMass;
}

static int cvm_usb_open(__bdk_fs_dev_t *handle, int flags)
{

    USB_MASS_DEVICE *UsbMass = findUsbMass(handle->dev_index,true);
    if (NULL == UsbMass) return -1;

    EFI_BLOCK_IO_MEDIA  *Media = &UsbMass->BlockIoMedia;
    bdk_rlock_unlock(UsbMass->bus_lock);

    EFI_STATUS Status = EFI_SUCCESS;
    if ((0 == Media->BlockSize) || (Media->RemovableMedia)) {
        Status = UsbBootDetectMedia (UsbMass);
    }
    if (!EFI_ERROR(Status) && !Media->MediaPresent) {
            Status = EFI_NO_MEDIA;
    }
    DEBUG((EFI_D_BLKIO,"Opening usb%d block size 0x%x MaxLBA 0x%lx Removable %d MediaId %u ReadOnly %d Status %d\n",
           handle->dev_index,
           Media->BlockSize,
           (uint64_t)Media->LastBlock,
           Media->RemovableMedia ? 1:0,
           (uint32_t)Media->MediaId,
           Media->ReadOnly ? 1: 0, (int) Status));

    return (Status == EFI_SUCCESS) ? 0 : -1;
}

static int cvm_usb_read(__bdk_fs_dev_t *handle, void *buffer, int length)
{
    DEBUG((EFI_D_BLKIO," H:%p-%d called %d bytes @%lu\n",
            handle, handle->dev_index, length,handle->location));
    USB_MASS_DEVICE *UsbMass = findUsbMass(handle->dev_index,true);
    if (NULL == UsbMass) return -1;
    EFI_BLOCK_IO_MEDIA  *Media = &UsbMass->BlockIoMedia;
    uint32_t BlockSize = Media->BlockSize;
    int BlockShift = HighBitSet(Media->BlockSize);
    uint64_t BlockMask = (1ULL<<BlockShift) -1;
    // Check for unaligned beginning
    int head = handle->location & BlockMask;
    char *scratchbuf = NULL;
    int rc = length; // assume we have read everything
    EFI_STATUS Status;
    if (head || length&BlockMask) {
        scratchbuf = malloc(BlockSize);
        if (NULL == scratchbuf) {
            rc = -1;
            goto read_done_noIO;
        }
    }
    uint64_t LBA = handle->location >>BlockShift;
    if (head) {
        Status = UsbMassReadBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, scratchbuf);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) reading first block\n", (int) Status));
            rc = -1;
            goto read_done;
        }
        int lcopy = BlockSize - head;
        if (lcopy > length) lcopy = length;
        memcpy(buffer,scratchbuf+head,lcopy);
        buffer = ((char*)buffer) + lcopy;
        length -= lcopy;
        LBA += 1;
    }
    if (0 >= length) goto read_done;
    int numBlocks = length >> BlockShift;
    Status =  UsbMassReadBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, (numBlocks<<BlockShift), buffer);
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "Error (%d) reading middle blocks\n", (int) Status));
        rc = 0;
        goto read_done;
    }
    length -=  (numBlocks<<BlockShift);
    if (length) {
        LBA += numBlocks;
        buffer = ((char*) buffer) + (numBlocks<<BlockShift);
        Status = UsbMassReadBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, scratchbuf);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) reading tail block\n",  (int) Status));
            rc = -1;
            goto read_done;
        }
        memcpy(buffer,scratchbuf,length);
    }
read_done:
    if (EFI_DO_RESET == Status) {
        cvm_do_reset(UsbMass, handle->dev_index);
    } else {
read_done_noIO:
        bdk_rlock_unlock(UsbMass->bus_lock);
    }
    if (scratchbuf) free(scratchbuf);
    return rc;
}

static int cvm_usb_write(__bdk_fs_dev_t *handle, const void *buffer, int length)
{
    DEBUG((EFI_D_BLKIO,"H:%p-%d called for %d bytes @%lu\n",
           handle, handle->dev_index, length,handle->location));
    USB_MASS_DEVICE *UsbMass = findUsbMass(handle->dev_index, true);
    if (NULL == UsbMass) return -1;
    EFI_BLOCK_IO_MEDIA  *Media = &UsbMass->BlockIoMedia;
    uint32_t BlockSize = Media->BlockSize;
    int rc = length; // assume we have written everything
    char *scratchbuf = NULL;
    if (Media->ReadOnly ) {
        DEBUG ((EFI_D_ERROR, "Write is called for read-only media\n"));
        rc = -1;
        goto write_done_noIO;
    }
    int BlockShift = HighBitSet(Media->BlockSize);
    uint64_t BlockMask = (1ULL<<BlockShift)-1;
    int head = handle->location & BlockMask; // Check for unaligned start
    EFI_STATUS Status;
    if (head || length&BlockMask) {
        scratchbuf = malloc(BlockSize);
        if (NULL == scratchbuf) {
            rc = -1;
            goto write_done_noIO;
        }
    }
    uint64_t LBA = handle->location >>BlockShift;
    if (head) {
        Status = UsbMassReadBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, scratchbuf);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) reading first block\n", (int) Status));
            rc = -1;
            goto write_done;
        }
        int lcopy = BlockSize - head;
        if (lcopy > length) lcopy = length;
        memcpy(scratchbuf+head,buffer,lcopy);
        Status = UsbMassWriteBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, scratchbuf);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) writing first block\n", (int) Status));
            rc = -1;
            goto write_done;
        }
        buffer = ((char*)buffer) + lcopy;
        length -= lcopy;
        LBA += 1;
    }
    if ( 0 >= length) goto write_done;
    int numBlocks = length >> BlockShift;
    Status =  UsbMassWriteBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, (numBlocks<<BlockShift), buffer);
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "Error (%d) writing middle blocks\n", (int) Status));
        rc = 0;
        goto write_done;
    }
    length -= (numBlocks<<BlockShift);
    if (length) {
        LBA += numBlocks;
        Status = UsbMassReadBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, scratchbuf);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) reading last block\n", (int) Status));
            rc = -1;
            goto write_done;
        }
        memcpy(scratchbuf,buffer,length);
        Status =  UsbMassWriteBlocks(&UsbMass->BlockIo, Media->MediaId, LBA, BlockSize, buffer);
        if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "Error (%d) writing last block\n", (int) Status));
            rc = 0;
            goto write_done;
        }
    }

write_done:
    if (EFI_DO_RESET == Status) {
        cvm_do_reset(UsbMass, handle->dev_index);
    } else {
write_done_noIO:
        bdk_rlock_unlock(UsbMass->bus_lock);
    }
    if (scratchbuf) free(scratchbuf);
    return rc;
}
#if 1
// At this time close does nothing but adds trace entry
// Remove from ops to save space
#else
static int cvm_usb_close(__bdk_fs_dev_t *handle)
{
    DEBUG((EFI_D_BLKIO," H:%p %d \n",
           handle, handle ?  handle->dev_index : -1));
#if 0
    if (NULL == handle) return 0;

    // FIXME - do something with handle
    USB_MASS_DEVICE *UsbMass = findUsbMass(handle->dev_index,false);
    if (NULL == UsbMass) return 0; // Null means it was never open
#endif
    return 0;
}
#endif

static const __bdk_fs_dev_ops_t bdk_fs_usb_ops =
{
    .open = cvm_usb_open,
    .close = NULL, //cvm_usb_close,
    .read = cvm_usb_read,
    .write = cvm_usb_write,
};



/*
** Interface to USB proper for Device add/remove
*/


/**
  Start controlling the usb mass storage interface

  @param  UsbIo                 Pointer to UsbIo for the interface
  @param  RemainingDevicePath   The remaining device path.
  @param  ifHandle              Opaque handle which will be passed when stopping the interface

  @retval EFI_SUCCESS           The driver stopped from controlling the device.
  @retval EFI_UNSUPPORTED       This driver does not support this device.
  @retval EFI_DEVICE_ERROR      This driver cannot be started due to device Error.
  @retval EFI_OUT_OF_RESOURCES  Can't allocate memory resources.
  @retval EFI_ALREADY_STARTED   Interface have been already registered

**/
EFI_STATUS
UsbMassIfStart(EFI_USB_IO_PROTOCOL *UsbIo,
              EFI_DEVICE_PATH_PROTOCOL      *DevicePath,
              void *ifHandle
    )
{
    EFI_USB_INTERFACE_DESCRIPTOR  Interface;
    EFI_STATUS                    Status;

    // Find and initialize transport
    USB_MASS_TRANSPORT            *Transport;
    VOID                          *tContext;
    UINT8                         MaxLun = 0;
    Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &Interface);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    // Traverse the USB_MASS_TRANSPORT arrary and try to find the
    // matching transport protocol.
    // If not found, return EFI_UNSUPPORTED.
    // If found, execute USB_MASS_TRANSPORT.Init() to initialize the transport context.
    Status = EFI_UNSUPPORTED;

    tContext = NULL;
    for (unsigned Index = 0; Index < USB_MASS_TRANSPORT_COUNT; Index++) {
        Transport = mUsbMassTransport[Index];

        if (Interface.InterfaceProtocol == Transport->Protocol) {
            Status  = Transport->Init (UsbIo, &tContext);
            break;
        }
    }
    if (EFI_ERROR (Status)) {
        goto err_exit;
    }
    if (Transport->Protocol == USB_MASS_STORE_BOT) {
        Transport->GetMaxLun (tContext, &MaxLun);
    }

    // Initialize mass device
    if (MaxLun > 0) {
        CAVIUM_NOTYET("MultiLun support is not implemented");
        Status = EFI_UNSUPPORTED;
        goto err_exit;
    }
    // make sure there is accounting space before going further
    int devIndex = -1;
    bdk_rlock_lock(&musb_list_lock); // There may be multiple xhci polls going on
    for(unsigned ndx = 0; ndx < ARRAY_SIZE(musb_list); ndx++) {
        if (ifHandle == musb_list[ndx].ifHandle) {
            Status = EFI_ALREADY_STARTED;
            DEBUG((EFI_D_ERROR, "attempt to register ifHandle %p twice", ifHandle));
            goto err_exit;
        }
        if ((NULL == musb_list[ndx].ifHandle) && (devIndex < 0) ) devIndex = ndx;
    }
    if (devIndex < 0) {
        bdk_rlock_unlock(&musb_list_lock);
        DEBUG((EFI_D_ERROR, "No space for ifHandle %p in device list",  ifHandle));
        Status =  EFI_OUT_OF_RESOURCES;
        goto err_exit;
    }
    USB_MASS_DEVICE *UsbMass =
        musb_list[devIndex].UsbMass = calloc(1,sizeof(*musb_list[devIndex].UsbMass));
    if (NULL == UsbMass) {
        bdk_rlock_unlock(&musb_list_lock);
        DEBUG((EFI_D_ERROR, "Failed to malloc USB_MASS_DEVICE for ifHandle %p ", ifHandle));
        Status =  EFI_OUT_OF_RESOURCES;
        goto err_exit;
    }
    musb_list[devIndex].ifHandle = ifHandle;
    bdk_rlock_unlock(&musb_list_lock);

    UsbMass->UsbIo                = UsbIo;
    UsbMass->BlockIo.Media        = &UsbMass->BlockIoMedia;
    UsbMass->BlockIo.Reset        = UsbMassReset;
    UsbMass->BlockIo.ReadBlocks   = UsbMassReadBlocks;
    UsbMass->BlockIo.WriteBlocks  = UsbMassWriteBlocks;
    UsbMass->BlockIo.FlushBlocks  = UsbMassFlushBlocks;
    UsbMass->OpticalStorage       = FALSE;
    UsbMass->Transport            = Transport;
    UsbMass->Context              = tContext;

    Status = UsbMassInitMedia (UsbMass);
    int retry = 3;
    while ((Status == EFI_MEDIA_CHANGED) && retry) {
         Status = UsbMassInitMedia (UsbMass);
         retry--;
    }
    if ((EFI_ERROR (Status)) && (Status != EFI_NO_MEDIA)) {
        DEBUG ((EFI_D_ERROR, "UsbMassInitMedia (%d)\n", (int)Status));
        free(UsbMass);
        bdk_rlock_lock(&musb_list_lock);
        musb_list[devIndex].ifHandle = NULL;
        musb_list[devIndex].UsbMass = NULL;
        bdk_rlock_unlock(&musb_list_lock);
        goto err_exit;
    }

    USB_INTERFACE *thisUsbIf = USB_INTERFACE_FROM_USBIO (UsbIo);
    if (ifHandle != thisUsbIf) {
        bdk_error("USB: Mismatch between UsbIf(UsbIO) and ifhandle %p vs %p\n",thisUsbIf,ifHandle);
        goto err_exit;
    }

    USB_DEVICE *thisDevice = thisUsbIf->Device;
    bdk_node_t node = 0;
    int usb_port = 0;

    cvm_usbif2node(thisUsbIf, &node, &usb_port, (void**)&UsbMass->bus_lock);

    DEBUG((EFI_D_INFO,"Initializing USB_MASS %p ifhandle %p @devindex %d for node %u usb_port %d lock @%p\n", UsbMass, ifHandle, devIndex, (unsigned) node, usb_port,UsbMass->bus_lock ));
    int rc = bdk_fs_register_dev("usb",devIndex,&bdk_fs_usb_ops);
    printf("\nRegistered device \"/dev/n%d.usb%d\" for node %d usb port %d - %s %s\n", (int) node, devIndex, (int) node, usb_port,
           (rc) ? "??" : "OK",  __bdk_usb_speed2token(thisDevice->Speed));

    if (rc == 0 && __bdk_fs_fatfs_usbnotify) {
       __bdk_fs_fatfs_usbnotify(devIndex, 1);
    }

    return rc;

err_exit:
    if (Transport && tContext)
        Transport->CleanUp(tContext);

    return Status;
}

/**
  Stop controlling the usb mass storage interface

  @param  ifHandle              Opaque handle which will be passed when stopping the interface

**/
void
UsbMassIfStop(void *ifHandle)
{
    USB_MASS_DEVICE *UsbMass = NULL;
    USB_INTERFACE *thisUsbIf = ifHandle;
    bdk_rlock_lock(&musb_list_lock);
    unsigned devIndex;
    for(devIndex = 0;  devIndex < ARRAY_SIZE(musb_list); devIndex++) {
        if (ifHandle == musb_list[devIndex].ifHandle) {
            UsbMass = musb_list[devIndex].UsbMass;
            musb_list[devIndex].UsbMass = NULL;
            musb_list[devIndex].ifHandle = NULL;
            break;
        }
    }
    bdk_rlock_unlock(&musb_list_lock);
    if (NULL == UsbMass) {
        DEBUG((EFI_D_ERROR, "Failed to find index for ifHandle %p in device list\n", ifHandle));
    } else {
        bdk_node_t if_node = 0;
        int if_phys_port = 0;
        cvm_usbif2node(thisUsbIf, &if_node, &if_phys_port, NULL);

        if (__bdk_fs_fatfs_usbnotify) {
            __bdk_fs_fatfs_usbnotify(devIndex, 0);
         }

        int rc = bdk_fs_unregister_dev("usb",devIndex);
        printf("\nUnregistered device \"/dev/n%d.usb%d\" for node %d port %d from bdk_fs - %s\n", if_node, devIndex , if_node, if_phys_port, (rc) ? "ERROR" : "OK");
        UsbMass->Transport->CleanUp (UsbMass->Context);
        free(UsbMass);
    }
    DEBUG((EFI_D_INFO, "Stopped USbMass %p for ifHandle %p\n", UsbMass, ifHandle));
}

/**
  Find  the usb mass storage interface

  @param  ifHandle              Opaque handle which will be passed when stopping the interface

**/
int
UsbMassIfFind(const void *ifHandle)
{
    int rc = -1;
    bdk_rlock_lock(&musb_list_lock);
    unsigned devIndex;
    for(devIndex = 0;  devIndex < ARRAY_SIZE(musb_list); devIndex++) {
        if (ifHandle == musb_list[devIndex].ifHandle) {
            rc = devIndex;
            break;
        }
    }
    bdk_rlock_unlock(&musb_list_lock);
    return rc;
}

