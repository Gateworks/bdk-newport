/** @file

   The XHCI register operation routines.

Copyright (c) 2011 - 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Copyright (c)  2016-2017 Cavium Inc.
Adapted to CN8xxx family
**/
#include <bdk.h>
#include "Xhci.h"
#include "XhciReg.h"

/*
** Bar number for access to xhci space
*/
#define BDK_XHCI_BAR 0
/**
  Read 8-bit XHCI register.

  @param  Xhc          The XHCI Instance.
  @param  Offset       The offset of the 4-bytes width capability register.

  @return The register content read.
  @retval If err, return 0xFFFFFFFF.

**/
uint32_t
XhcRead8 (
    IN  USB_XHCI_INSTANCE   *Xhc,
    IN  UINT32              Offset)
{
     return bdk_le32_to_cpu (
        bdk_bar_read(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint8_t), Offset)
        );
}

/**
  Read 4-bytes width XHCI register.

  @param  Xhc          The XHCI Instance.
  @param  Offset       The offset of the 4-bytes width capability register.

  @return The register content read.
  @retval If err, return 0xFFFFFFFF.

**/
uint32_t
XhcRead32 (
    IN  USB_XHCI_INSTANCE   *Xhc,
    IN  UINT32              Offset)
{
     return bdk_le32_to_cpu (
        bdk_bar_read(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint32_t), Offset)
        );
}

/**
  Write the data to the 4-bytes width XHCI

  @param  Xhc      The XHCI Instance.
  @param  Offset   The offset of the 4-bytes width operational register.
  @param  Data     The data to write.

**/
void
XhcWrite32 (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
    bdk_bar_write(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint32_t), Offset, bdk_cpu_to_le32(Data));
}

/**
  Read-Modify-Write 32 bit XHCI register

  @param  Xhc          The XHCI Instance.
  @param  Offset       The offset of the operational register.
  @param  AndMask      The bit mask of the register to clear.
  @param  OrMask       The bit mask of the register to set.

**/
VOID
XhcRMW32 (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Offset,
  IN UINT32               AndMask,
  IN UINT32               OrMask
  )
{
    uint32_t value =  bdk_le32_to_cpu ( bdk_bar_read(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint32_t), Offset));
    value = (value & AndMask) | OrMask;
    bdk_bar_write(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint32_t), Offset, bdk_cpu_to_le32(value));
}

/**
  Wait the XHCI register's bit as specified by Bit
  to be set (or clear).

  @param  Xhc          The XHCI Instance.
  @param  Offset       The offset of the operational register.
  @param  Bit          The bit(mask) of the register to wait for.
  @param  WaitToSet    Wait the bit to set or clear.
  @param  Timeout      The time to wait before abort milliseconds

  @retval EFI_SUCCESS  The bit successfully changed by host controller.
  @retval EFI_TIMEOUT  The time out occurred.

**/
EFI_STATUS
XhcWait32 (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Offset,
  IN UINT32               Bit,
  IN BOOLEAN              WaitToSet,
  IN UINT32               Timeout
  )
{
    EFI_STATUS Status = EFI_TIMEOUT;
    uint64_t done = bdk_clock_get_count(BDK_CLOCK_TIME) + (uint64_t)(Timeout*1000) *
                        bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    do {
        if (!!(Bit & XhcRead32(Xhc,Offset)) == !!WaitToSet) {
            Status = EFI_SUCCESS;
            break;
        }
        bdk_thread_yield();
    } while(bdk_clock_get_count(BDK_CLOCK_TIME) < done);
    return Status;
}

/**
  Read 64 bit  XHCI register.

  @param  Xhc          The XHCI Instance.
  @param  Offset       The offset of the 4-bytes width capability register.

  @return The register content read.
  @retval If err, return 0xFFFFFFFF.

**/
uint64_t
XhcRead64 (
    IN  USB_XHCI_INSTANCE   *Xhc,
    IN  UINT32              Offset)
{
     return bdk_le64_to_cpu (
        bdk_bar_read(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint64_t), Offset)
        );
}

/**
  Write the data to the 64 bit XHCI register

  @param  Xhc      The XHCI Instance.
  @param  Offset   The offset of the 4-bytes width operational register.
  @param  Data     The data to write.

**/
void
XhcWrite64 (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT32               Offset,
  IN UINT64               Data
  )
{
    bdk_bar_write(Xhc->bdk_dev, BDK_XHCI_BAR, sizeof(uint64_t), Offset, bdk_cpu_to_le64(Data));
}

/**
  Calculate the offset of the XHCI capability.

  @param  Xhc     The XHCI Instance.
  @param  CapId   The XHCI Capability ID.

  @return The offset of XHCI legacy support capability register.

**/
UINT32
XhcGetCapabilityAddr (
  IN USB_XHCI_INSTANCE    *Xhc,
  IN UINT8                CapId
  )
{
  UINT32 ExtCapOffset;
  UINT8  NextExtCapReg;
  UINT32 Data;

  ExtCapOffset = 0;

  do {
    //
    // Check if the extended capability register's capability id is USB Legacy Support.
    //
    Data = XhcReadExtCapReg (Xhc, ExtCapOffset);
    if ((Data & 0xFF) == CapId) {
      return ExtCapOffset;
    }
    //
    // If not, then traverse all of the ext capability registers till finding out it.
    //
    NextExtCapReg = (UINT8)((Data >> 8) & 0xFF);
    ExtCapOffset += (NextExtCapReg << 2);
  } while (NextExtCapReg != 0);

  return 0xFFFFFFFFU;
}
