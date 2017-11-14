/** @file
  Defines base data types and constants introduced in UEFI and XHCI.

  Copyright (c) 2006 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution.  The full text of the license may be found at
    http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __USB_XHCI_COMPAT_H__
#define __USB_XHCI_COMPAT_H__
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Aarch64_ProcessorBind.h"

#if !defined(IN)
#	define IN
#	define OUT
#	define OPTIONAL
#endif
#if !defined(EFI_API)
#define EFIAPI
#endif


#if !defined(TRUE)
#define TRUE  ((BOOLEAN)(1==1))
#endif
#if !defined(FALSE)
#define FALSE  ((BOOLEAN)(0==1))
#endif
typedef void VOID;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
#endif

#if !defined(CONST)
#define CONST const

#if ! defined(MIN)
#define MIN(a, b)                       \
  (((a) < (b)) ? (a) : (b))
#endif
#if ! defined(MAX)
#define MAX(a, b)                       \
  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(ABS)
#define ABS(a)                          \
  (((a) < 0) ? (-(a)) : (a))
#endif


# if !defined(MT_DEBUG)
#define MT_DEBUG(fmt, args...) printf(fmt , ## args)
#endif
#if ! defined(EFI_D_INIT)
#	define EFI_D_INIT        0x00000001          // Initialization style messages
#	define EFI_D_WARN        0x00000002          // Warnings
#	define EFI_D_LOAD        0x00000004          // Load events
#	define EFI_D_FS          0x00000008          // EFI File system
#	define EFI_D_POOL        0x00000010          // Alloc & Free's
#	define EFI_D_PAGE        0x00000020          // Alloc & Free's
#	define EFI_D_INFO        0x00000040          // Informational debug messages
#	define EFI_D_VARIABLE    0x00000100          // Variable
#	define EFI_D_BM          0x00000400          // Boot Manager (BDS)
#	define EFI_D_BLKIO       0x00001000          // BlkIo Driver
#	define EFI_D_NET         0x00004000          // SNI Driver
#	define EFI_D_UNDI        0x00010000          // UNDI Driver
#	define EFI_D_LOADFILE    0x00020000          // UNDI Driver
#	define EFI_D_EVENT       0x00080000          // Event messages
#	define EFI_D_VERBOSE     0x00400000          // Detailed debug messages that may significantly impact boot performance
#	define EFI_D_ERROR       0x80000000          // Error
#endif

const char* debuglvl2s(uint32_t lvl);

#define _DEBUG_INNER(lvl, fmt, ...) \
    if (lvl & (/*EFI_D_WARN |*/ EFI_D_ERROR)) {  \
        printf("USB_XHCI: %s %s:%d " fmt, debuglvl2s(lvl), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } else {                                                            \
        BDK_TRACE(USB_XHCI,"%s %s:%d " fmt, debuglvl2s(lvl), __FUNCTION__, __LINE__,  ##__VA_ARGS__); \
    }

#define DEBUG(x) do {\
        _DEBUG_INNER x ;                        \
    } while(0)

//#define ASSERT(x) if (!(x)){ printf("\n%s:%d ASSERT Failed\n", __FUNCTION__, __LINE__);}
#define ASSERT(x)
#define ASSERT_HANG(x) if (!(x)){ printf("\n%s:%d ASSERT Failed\n", __FUNCTION__, __LINE__); while(1);}

#if ! defined(CAVIUM_NOTYET)
#define CAVIUM_NOTYET(x...) printf("NOTYET: " #x "%s:%d %s\n", __FILE__, __LINE__, __FUNCTION__)
#endif
#define NOT_CAVIUM(x...)

#define FreePool(x_ptr) free(x_ptr)
#define AllocateZeroPool(sz) calloc(1,(sz))

#define  BIT0     0x00000001
#define  BIT1     0x00000002
#define  BIT2     0x00000004
#define  BIT3     0x00000008
#define  BIT4     0x00000010
#define  BIT5     0x00000020
#define  BIT6     0x00000040
#define  BIT7     0x00000080
#define  BIT8     0x00000100
#define  BIT9     0x00000200
#define  BIT10    0x00000400
#define  BIT11    0x00000800
#define  BIT12    0x00001000
#define  BIT13    0x00002000
#define  BIT14    0x00004000
#define  BIT15    0x00008000
#define  BIT16    0x00010000
#define  BIT17    0x00020000
#define  BIT18    0x00040000
#define  BIT19    0x00080000
#define  BIT20    0x00100000
#define  BIT21    0x00200000
#define  BIT22    0x00400000
#define  BIT23    0x00800000
#define  BIT24    0x01000000
#define  BIT25    0x02000000
#define  BIT26    0x04000000
#define  BIT27    0x08000000
#define  BIT28    0x10000000
#define  BIT29    0x20000000
#define  BIT30    0x40000000
#define  BIT31    0x80000000
#define  BIT32    0x0000000100000000ULL
#define  BIT33    0x0000000200000000ULL
#define  BIT34    0x0000000400000000ULL
#define  BIT35    0x0000000800000000ULL
#define  BIT36    0x0000001000000000ULL
#define  BIT37    0x0000002000000000ULL
#define  BIT38    0x0000004000000000ULL
#define  BIT39    0x0000008000000000ULL
#define  BIT40    0x0000010000000000ULL
#define  BIT41    0x0000020000000000ULL
#define  BIT42    0x0000040000000000ULL
#define  BIT43    0x0000080000000000ULL
#define  BIT44    0x0000100000000000ULL
#define  BIT45    0x0000200000000000ULL
#define  BIT46    0x0000400000000000ULL
#define  BIT47    0x0000800000000000ULL
#define  BIT48    0x0001000000000000ULL
#define  BIT49    0x0002000000000000ULL
#define  BIT50    0x0004000000000000ULL
#define  BIT51    0x0008000000000000ULL
#define  BIT52    0x0010000000000000ULL
#define  BIT53    0x0020000000000000ULL
#define  BIT54    0x0040000000000000ULL
#define  BIT55    0x0080000000000000ULL
#define  BIT56    0x0100000000000000ULL
#define  BIT57    0x0200000000000000ULL
#define  BIT58    0x0400000000000000ULL
#define  BIT59    0x0800000000000000ULL
#define  BIT60    0x1000000000000000ULL
#define  BIT61    0x2000000000000000ULL
#define  BIT62    0x4000000000000000ULL
#define  BIT63    0x8000000000000000ULL

// uefi'isms
typedef INTN RETURN_STATUS;
typedef RETURN_STATUS             EFI_STATUS;
typedef VOID                      *EFI_EVENT;
typedef
EFI_STATUS
(EFIAPI *EFI_ASYNC_USB_TRANSFER_CALLBACK) (
  IN VOID         *Data,
  IN UINTN        DataLength,
  IN VOID         *Context,
  IN UINT32       Status
  );

///
/// LIST_ENTRY structure definition.
///
typedef struct _LIST_ENTRY LIST_ENTRY;

///
/// _LIST_ENTRY structure definition.
///
struct _LIST_ENTRY {
  LIST_ENTRY  *ForwardLink;
  LIST_ENTRY  *BackLink;
};

BOOLEAN IsListEmpty(IN CONST LIST_ENTRY *List);
BOOLEAN IsNodeInList (IN CONST LIST_ENTRY *List, IN CONST LIST_ENTRY *Node);
LIST_ENTRY* InitializeListHead (IN OUT LIST_ENTRY            *List);
LIST_ENTRY* RemoveEntryList (IN      CONST LIST_ENTRY      *Entry);
LIST_ENTRY* InsertHeadList (IN OUT  LIST_ENTRY* List, IN OUT  LIST_ENTRY            *Entry);
LIST_ENTRY* InsertTailList (IN OUT  LIST_ENTRY* List, IN OUT  LIST_ENTRY* Entry);
#define ENCODE_ERROR(a)              (- (a))

#define ENCODE_WARNING(a)            (a)
#define RETURN_ERROR(a)              ((a) < 0)

typedef VOID                      *EFI_HANDLE;

typedef VOID                      *EFI_EVENT;

typedef UINTN                     EFI_TPL;


typedef UINT64                    EFI_LBA;


typedef UINT16                    STRING_REF;

#define RETURN_SUCCESS               0
#define RETURN_LOAD_ERROR            ENCODE_ERROR (1)
#define RETURN_INVALID_PARAMETER     ENCODE_ERROR (2)
#define RETURN_UNSUPPORTED           ENCODE_ERROR (3)
#define RETURN_BAD_BUFFER_SIZE       ENCODE_ERROR (4)
#define RETURN_BUFFER_TOO_SMALL      ENCODE_ERROR (5)
#define RETURN_NOT_READY             ENCODE_ERROR (6)
#define RETURN_DEVICE_ERROR          ENCODE_ERROR (7)
#define RETURN_WRITE_PROTECTED       ENCODE_ERROR (8)
#define RETURN_OUT_OF_RESOURCES      ENCODE_ERROR (9)
#define RETURN_VOLUME_CORRUPTED      ENCODE_ERROR (10)
#define RETURN_VOLUME_FULL           ENCODE_ERROR (11)
#define RETURN_NO_MEDIA              ENCODE_ERROR (12)
#define RETURN_MEDIA_CHANGED         ENCODE_ERROR (13)
#define RETURN_NOT_FOUND             ENCODE_ERROR (14)
#define RETURN_ACCESS_DENIED         ENCODE_ERROR (15)
#define RETURN_NO_RESPONSE           ENCODE_ERROR (16)
#define RETURN_NO_MAPPING            ENCODE_ERROR (17)
#define RETURN_TIMEOUT               ENCODE_ERROR (18)
#define RETURN_NOT_STARTED           ENCODE_ERROR (19)
#define RETURN_ALREADY_STARTED       ENCODE_ERROR (20)
#define RETURN_ABORTED               ENCODE_ERROR (21)
#define RETURN_ICMP_ERROR            ENCODE_ERROR (22)
#define RETURN_TFTP_ERROR            ENCODE_ERROR (23)
#define RETURN_PROTOCOL_ERROR        ENCODE_ERROR (24)
#define RETURN_INCOMPATIBLE_VERSION  ENCODE_ERROR (25)
#define RETURN_SECURITY_VIOLATION    ENCODE_ERROR (26)
#define RETURN_CRC_ERROR             ENCODE_ERROR (27)
#define RETURN_END_OF_MEDIA          ENCODE_ERROR (28)
#define RETURN_END_OF_FILE           ENCODE_ERROR (31)
#define RETURN_DO_RESET              ENCODE_ERROR (32)

#define RETURN_WARN_UNKNOWN_GLYPH    ENCODE_WARNING (1)
#define RETURN_WARN_DELETE_FAILURE   ENCODE_WARNING (2)
#define RETURN_WARN_WRITE_FAILURE    ENCODE_WARNING (3)
#define RETURN_WARN_BUFFER_TOO_SMALL ENCODE_WARNING (4)
#define EFI_SUCCESS               RETURN_SUCCESS
#define EFI_LOAD_ERROR            RETURN_LOAD_ERROR
#define EFI_INVALID_PARAMETER     RETURN_INVALID_PARAMETER
#define EFI_UNSUPPORTED           RETURN_UNSUPPORTED
#define EFI_BAD_BUFFER_SIZE       RETURN_BAD_BUFFER_SIZE
#define EFI_BUFFER_TOO_SMALL      RETURN_BUFFER_TOO_SMALL
#define EFI_NOT_READY             RETURN_NOT_READY
#define EFI_DEVICE_ERROR          RETURN_DEVICE_ERROR
#define EFI_WRITE_PROTECTED       RETURN_WRITE_PROTECTED
#define EFI_OUT_OF_RESOURCES      RETURN_OUT_OF_RESOURCES
#define EFI_VOLUME_CORRUPTED      RETURN_VOLUME_CORRUPTED
#define EFI_VOLUME_FULL           RETURN_VOLUME_FULL
#define EFI_NO_MEDIA              RETURN_NO_MEDIA
#define EFI_MEDIA_CHANGED         RETURN_MEDIA_CHANGED
#define EFI_NOT_FOUND             RETURN_NOT_FOUND
#define EFI_ACCESS_DENIED         RETURN_ACCESS_DENIED
#define EFI_NO_RESPONSE           RETURN_NO_RESPONSE
#define EFI_NO_MAPPING            RETURN_NO_MAPPING
#define EFI_TIMEOUT               RETURN_TIMEOUT
#define EFI_NOT_STARTED           RETURN_NOT_STARTED
#define EFI_ALREADY_STARTED       RETURN_ALREADY_STARTED
#define EFI_ABORTED               RETURN_ABORTED
#define EFI_ICMP_ERROR            RETURN_ICMP_ERROR
#define EFI_TFTP_ERROR            RETURN_TFTP_ERROR
#define EFI_PROTOCOL_ERROR        RETURN_PROTOCOL_ERROR
#define EFI_INCOMPATIBLE_VERSION  RETURN_INCOMPATIBLE_VERSION
#define EFI_SECURITY_VIOLATION    RETURN_SECURITY_VIOLATION
#define EFI_CRC_ERROR             RETURN_CRC_ERROR
#define EFI_END_OF_MEDIA          RETURN_END_OF_MEDIA
#define EFI_END_OF_FILE           RETURN_END_OF_FILE
#define EFI_DO_RESET              RETURN_DO_RESET

#define EFI_WARN_UNKNOWN_GLYPH    RETURN_WARN_UNKNOWN_GLYPH
#define EFI_WARN_DELETE_FAILURE   RETURN_WARN_DELETE_FAILURE
#define EFI_WARN_WRITE_FAILURE    RETURN_WARN_WRITE_FAILURE
#define EFI_WARN_BUFFER_TOO_SMALL RETURN_WARN_BUFFER_TOO_SMALL

#define EFI_ERROR(A)              RETURN_ERROR(A)
#define ASSERT_EFI_ERROR(x...)

#define USB_BIT(a)                  ((UINTN)(1 << (a)))
#define USB_BIT_IS_SET(Data, Bit)   ((BOOLEAN)(((Data) & (Bit)) == (Bit)))
#if ! defined(CR)
#define CR(Record, TYPE, Field, Dummy...)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#endif
/*
 * Useful stuff
 */

#if !defined(BDK_BARRIER)
#define BDK_BARRIER     asm volatile ("" : : :"memory") /* noop, compiler will not cross */
#endif
#if !defined(ARRAY_SIZE)
#       define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#if !defined(ROUNDUP)
#define ROUNDUP(x,sz) ((((sz)+(x) -1)/(x)) * (x))
#endif

#define CopyMem(to,from,size) ({void *p;do {    \
    BDK_BARRIER;                  \
    p=memcpy((to),(from),(size));\
    BDK_DSB;\
        } while(0);p;})

#define ZeroMem(at,size) bzero((at),(size));
/*
** defines to make things compile
*/
#define REPORT_STATUS_CODE_WITH_DEVICE_PATH(x...)

/**
  Returns the bit position of the highest bit set in a 64-bit value. Equivalent
  to log2(x).

  This function computes the bit position of the highest bit set in the 32-bit
  value specified by Operand. If Operand is zero, then -1 is returned.
  Otherwise, a value between 0 and 63 is returned.

  @param  Operand The unsigned integer to evaluate.

  @return Position of the highest bit set in Operand if found.
  @retval -1  Operand is zero.

**/
static inline int HighBitSet (unsigned int Operand) __attribute__((always_inline));
static inline int
/*EFIAPI */
HighBitSet (
  IN      unsigned int                    Operand
  )
{

  if (Operand == 0) {
    return - 1;
  }
  return (8*sizeof(unsigned int) - __builtin_clz(Operand)) -1 ;
}

#endif
