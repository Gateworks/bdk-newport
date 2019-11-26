/*++

Copyright (c) 2004 - 2006, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.  


Module Name:

  LinkedList.c
  
Abstract: 

  Linked List Library Functions.

--*/
#include <bdk.h> // Only assertions need it
#include "usb-xhci-compat.h"

/**
  Checks to see if a doubly linked list is empty or not.

  Checks to see if the doubly linked list is empty. If the linked list contains
  zero nodes, this function returns TRUE. Otherwise, it returns FALSE.

  If ListHead is NULL, then ASSERT().
  If ListHead was not initialized with InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLenth is not zero, and the number of nodes
  in List, including the List node, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.

  @retval TRUE  The linked list is empty.
  @retval FALSE The linked list is not empty.

**/
BOOLEAN
/* EFIAPI */
/* Glue */IsListEmpty (
  IN      CONST LIST_ENTRY      *List
  )
{
  //
  // ASSERT List not too long
  //
  ASSERT (IsNodeInList (List, List));

  return (BOOLEAN)(List->ForwardLink == List);
}

/**
  Worker function that locates the Node in the List

  By searching the List, finds the location of the Node in List. At the same time,
  verifies the validity of this list.

  If List is NULL, then ASSERT().
  If List->ForwardLink is NULL, then ASSERT().
  If List->backLink is NULL, then ASSERT().
  If Node is NULL, then ASSERT();
  If PcdMaximumLinkedListLenth is not zero, and prior to insertion the number
  of nodes in ListHead, including the ListHead node, is greater than or
  equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  List  A pointer to a node in a linked list.
  @param  Node  A pointer to one nod.

  @retval TRUE   Node is in List
  @retval FALSE  Node isn't in List, or List is invalid

**/
BOOLEAN
IsNodeInList (
  IN      CONST LIST_ENTRY      *List,
  IN      CONST LIST_ENTRY      *Node
  )
{
  UINTN                         Count;
  CONST LIST_ENTRY              *Ptr;
  BOOLEAN                       Found;

  //
  // Test the validity of List and Node
  //
  ASSERT (List != NULL);
  ASSERT (List->ForwardLink != NULL);
  ASSERT (List->BackLink != NULL);
  ASSERT (Node != NULL);

  Count = /* PcdGet32 (PcdMaximumLinkedListLength); */ 8192;

  Ptr = List;
  do {
    Ptr = Ptr->ForwardLink;
    Count--;
  } while ((Ptr != List) && (Ptr != Node) && (Count > 0));
  Found = (BOOLEAN)(Ptr == Node);

  /* if (PcdGet32 (PcdMaximumLinkedListLength) > 0) { */
    while ((Count > 0) && (Ptr != List)) {
      Ptr = Ptr->ForwardLink;
      Count--;
    }
    ASSERT (Count > 0);
  /* } */

  return Found;
}



/**
  Initializes the head node of a doubly linked list, and returns the pointer to
  the head node of the doubly linked list.

  Initializes the forward and backward links of a new linked list. After
  initializing a linked list with this function, the other linked list
  functions may be used to add and remove nodes from the linked list. It is up
  to the caller of this function to allocate the memory for ListHead.

  If ListHead is NULL, then ASSERT().

  @param  ListHead  A pointer to the head node of a new doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
//EFIAPI
/*Glue*/InitializeListHead (
  IN OUT  LIST_ENTRY            *List
  )

{
  ASSERT (List != NULL);

  List->ForwardLink = List;
  List->BackLink = List;
  return List;
}

/**
  Removes a node from a doubly linked list, and returns the node that follows
  the removed node.

  Removes the node Entry from a doubly linked list. It is up to the caller of
  this function to release the memory used by this node if that is required. On

  exit, the node following Entry in the doubly linked list is returned. If
  Entry is the only node in the linked list, then the head node of the linked
  list is returned.

  If Entry is NULL, then ASSERT().
  If Entry is the head node of an empty list, then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes in the
  linked list containing Entry, including the Entry node, is greater than
  or equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  Entry A pointer to a node in a linked list

  @return Entry

**/
LIST_ENTRY *
/*EFIAPI
  Glue*/RemoveEntryList (
  IN      CONST LIST_ENTRY      *Entry
  )
{
  ASSERT (!IsListEmpty (Entry));

  Entry->ForwardLink->BackLink = Entry->BackLink;
  Entry->BackLink->ForwardLink = Entry->ForwardLink;
  return Entry->ForwardLink;
}

/**
  Adds a node to the beginning of a doubly linked list, and returns the pointer
  to the head node of the doubly linked list.

  Adds the node Entry at the beginning of the doubly linked list denoted by
  ListHead, and returns ListHead.

  If ListHead is NULL, then ASSERT().
  If Entry is NULL, then ASSERT().
  If ListHead was not initialized with InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLenth is not zero, and prior to insertion the number
  of nodes in ListHead, including the ListHead node, is greater than or
  equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.
  @param  Entry     A pointer to a node that is to be inserted at the beginning
                    of a doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
/* EFIAPI */
/* Glue */InsertHeadList (
  IN OUT  LIST_ENTRY            *List,
  IN OUT  LIST_ENTRY            *Entry
  )
{
  //
  // ASSERT List not too long and Entry is not one of the nodes of List
  //
  ASSERT (!IsNodeInList (List, Entry));

  Entry->ForwardLink = List->ForwardLink;
  Entry->BackLink = List;
  Entry->ForwardLink->BackLink = Entry;
  List->ForwardLink = Entry;
  return List;
}

/**
  Adds a node to the end of a doubly linked list, and returns the pointer to
  the head node of the doubly linked list.

  Adds the node Entry to the end of the doubly linked list denoted by ListHead,
  and returns ListHead.

  If ListHead is NULL, then ASSERT().
  If Entry is NULL, then ASSERT().
  If ListHead was not initialized with InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLenth is not zero, and prior to insertion the number
  of nodes in ListHead, including the ListHead node, is greater than or
  equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.
  @param  Entry     A pointer to a node that is to be added at the end of the
                    doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
/* EFIAPI */
/* Glue */InsertTailList (
  IN OUT  LIST_ENTRY            *List,
  IN OUT  LIST_ENTRY            *Entry
  )
{
  //
  // ASSERT List not too long and Entry is not one of the nodes of List
  //
  ASSERT (!IsNodeInList (List, Entry));

  Entry->ForwardLink = List;
  Entry->BackLink = List->BackLink;
  Entry->BackLink->ForwardLink = Entry;
  List->BackLink = Entry;
  return List;
}

/*
** Device path support
*/
#include <bdk.h>
#include "Protocol/DevicePath.h"
#include "UsbAssorted.h"
/**
  Returns the size of a device path in bytes.

  This function returns the size, in bytes, of the device path data structure specified by
  DevicePath including the end of device path node.  If DevicePath is NULL, then 0 is returned.

  @param  DevicePath                 A pointer to a device path data structure.

  @return The size of a device path in bytes.

**/
UINTN
/* EFIAPI */
/* Glue */GetDevicePathSize (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  CONST EFI_DEVICE_PATH_PROTOCOL  *Start;

  if (DevicePath == NULL) {
    return 0;
  }

  //
  // Search for the end of the device path structure
  //
  Start = DevicePath;
  while (!EfiIsDevicePathEnd (DevicePath)) {
    DevicePath = EfiNextDevicePathNode (DevicePath);
  }

  //
  // Compute the size and add back in the size of the end device path structure
  //
  return ((UINTN) DevicePath - (UINTN) Start) + sizeof (EFI_DEVICE_PATH_PROTOCOL);
}


/**
  Creates a new device path by appending a second device path to a first device path.

  This function allocates space for a new copy of the device path specified by DevicePath.  If
  DevicePath is NULL, then NULL is returned.  If the memory is successfully allocated, then the
  contents of DevicePath are copied to the newly allocated buffer, and a pointer to that buffer
  is returned.  Otherwise, NULL is returned.  
  
  @param  DevicePath                 A pointer to a device path data structure.

  @return A pointer to the duplicated device path.

**/
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/DuplicateDevicePath (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  UINTN                     Size;

  //
  // Compute the size
  //
  Size = GetDevicePathSize (DevicePath);
  if (Size == 0) {
    return NULL;
  }

  //
  // Allocate space for duplicate device path
  //
#if defined(OCTEONTX_NOT_USED)
  NewDevicePath = AllocateCopyPool (Size, DevicePath);
#else
  NewDevicePath = malloc(Size);
  if (NewDevicePath) memcpy(NewDevicePath,DevicePath,Size);
#endif
  return NewDevicePath;
}

/**
  Creates a new device path by appending a second device path to a first device path.

  This function creates a new device path by appending a copy of SecondDevicePath to a copy of
  FirstDevicePath in a newly allocated buffer.  Only the end-of-device-path device node from
  SecondDevicePath is retained. The newly created device path is returned.  
  If FirstDevicePath is NULL, then it is ignored, and a duplicate of SecondDevicePath is returned.  
  If SecondDevicePath is NULL, then it is ignored, and a duplicate of FirstDevicePath is returned.  
  If both FirstDevicePath and SecondDevicePath are NULL, then NULL is returned.  
  If there is not enough memory for the newly allocated buffer, then NULL is returned.
  The memory for the new device path is allocated from EFI boot services memory. It is the
  responsibility of the caller to free the memory allocated.

  @param  FirstDevicePath            A pointer to a device path data structure.
  @param  SecondDevicePath           A pointer to a device path data structure.

  @return A pointer to the new device path.

**/
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/AppendDevicePath (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *FirstDevicePath,  OPTIONAL
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *SecondDevicePath  OPTIONAL
  )
{
  UINTN                     Size;
  UINTN                     Size1;
  UINTN                     Size2;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath2;

  //
  // If there's only 1 path, just duplicate it.
  //
  if (FirstDevicePath == NULL) {
    return DuplicateDevicePath (SecondDevicePath);
  }

  if (SecondDevicePath == NULL) {
    return DuplicateDevicePath (FirstDevicePath);
  }

  //
  // Allocate space for the combined device path. It only has one end node of
  // length EFI_DEVICE_PATH_PROTOCOL.
  //
  Size1         = GetDevicePathSize (FirstDevicePath);
  Size2         = GetDevicePathSize (SecondDevicePath);
  Size          = Size1 + Size2 - sizeof (EFI_DEVICE_PATH_PROTOCOL);

  NewDevicePath = /* AllocatePool (Size); */ calloc(1,Size);

  if (NewDevicePath != NULL) {
    NewDevicePath = CopyMem (NewDevicePath, FirstDevicePath, Size1);
    //
    // Over write FirstDevicePath EndNode and do the copy
    //
    DevicePath2 = (EFI_DEVICE_PATH_PROTOCOL *) ((CHAR8 *) NewDevicePath +
                  (Size1 - sizeof (EFI_DEVICE_PATH_PROTOCOL)));
    CopyMem (DevicePath2, SecondDevicePath, Size2);
  }

  return NewDevicePath;
}

/**
  Creates a new path by appending the device node to the device path.

  This function creates a new device path by appending a copy of the device node specified by
  DevicePathNode to a copy of the device path specified by DevicePath in an allocated buffer.
  The end-of-device-path device node is moved after the end of the appended device node.
  If DevicePath is NULL, then NULL is returned.
  If DevicePathNode is NULL, then NULL is returned.
  If there is not enough memory to allocate space for the new device path, then NULL is returned.  
  The memory is allocated from EFI boot services memory. It is the responsibility of the caller to
  free the memory allocated.

  @param  DevicePath                 A pointer to a device path data structure.
  @param  DevicePathNode             A pointer to a single device path node.

  @return A pointer to the new device path.

**/
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/AppendDevicePathNode (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath,     OPTIONAL
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode  OPTIONAL
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *NextNode;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  UINTN                     NodeLength;

  if (DevicePath == NULL || DevicePathNode == NULL) {
    return NULL;
  }
  //
  // Build a Node that has a terminator on it
  //
  NodeLength = DevicePathNodeLength (DevicePathNode);

  TempDevicePath = /*AllocatePool (NodeLength + sizeof (EFI_DEVICE_PATH_PROTOCOL));*/ calloc(1,(NodeLength + sizeof (EFI_DEVICE_PATH_PROTOCOL))); 
  if (TempDevicePath == NULL) {
    return NULL;
  }
  TempDevicePath = CopyMem (TempDevicePath, DevicePathNode, NodeLength);
  //
  // Add and end device path node to convert Node to device path
  //
  NextNode = NextDevicePathNode (TempDevicePath);
  SetDevicePathEndNode (NextNode);
  //
  // Append device paths
  //
  NewDevicePath = AppendDevicePath (DevicePath, TempDevicePath);

  FreePool (TempDevicePath);

  return NewDevicePath;
}

/*
** Various value-to-string convertors
*/
const char* debuglvl2s(uint32_t lvl)
{
    switch (lvl)
    {
    default: break;
    case EFI_D_WARN: return "WARN";
    case EFI_D_EVENT: return "EVENT";
    case EFI_D_INFO: return "INFO";
    case EFI_D_ERROR: return "ERROR";
    case EFI_D_BLKIO: return "BLKIO";
    }
    return "????";
}
