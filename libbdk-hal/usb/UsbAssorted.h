#ifndef __USB_ASSORTED_H__
#define  __USB_ASSORTED_H__
#include <Protocol/DevicePath.h>
typedef struct _EFI_DRIVER_BINDING_PROTOCOL  EFI_DRIVER_BINDING_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_SUPPORTED) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
/*++

  Routine Description:
    Test to see if this driver supports ControllerHandle. 

  Arguments:
    This                - Protocol instance pointer.
    ControllerHandle    - Handle of device to test
    RemainingDevicePath - Optional parameter use to pick a specific child 
                          device to start.

  Returns:
    EFI_SUCCESS         - This driver supports this device
    EFI_ALREADY_STARTED - This driver is already running on this device
    other               - This driver does not support this device

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_START) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
/*++

  Routine Description:
    Start this driver on ControllerHandle.

  Arguments:
    This                - Protocol instance pointer.
    ControllerHandle    - Handle of device to bind driver to
    RemainingDevicePath - Optional parameter use to pick a specific child 
                          device to start.

  Returns:
    EFI_SUCCESS         - This driver is added to ControllerHandle
    EFI_ALREADY_STARTED - This driver is already running on ControllerHandle
    other               - This driver does not support this device

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_STOP) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN  EFI_HANDLE                            ControllerHandle,
  IN  UINTN                                 NumberOfChildren,
  IN  EFI_HANDLE                            * ChildHandleBuffer
  )
/*++

  Routine Description:
    Stop this driver on ControllerHandle.

  Arguments:
    This              - Protocol instance pointer.
    ControllerHandle  - Handle of device to stop driver on 
    NumberOfChildren  - Number of Handles in ChildHandleBuffer. If number of 
                        children is zero stop the entire bus driver.
    ChildHandleBuffer - List of Child Handles to Stop.

  Returns:
    EFI_SUCCESS         - This driver is removed ControllerHandle
    other               - This driver was not removed from this device

--*/
;
typedef struct _EFI_SYSTEM_TABLE  EFI_SYSTEM_TABLE;

struct _EFI_SYSTEM_TABLE {
    void * dummy;
    void * dummy1;
};

/* DriverBinding.h */
//
// Interface structure for the ControllerHandle Driver Protocol
//
struct _EFI_DRIVER_BINDING_PROTOCOL {
  EFI_DRIVER_BINDING_SUPPORTED  Supported;
  EFI_DRIVER_BINDING_START      Start;
  EFI_DRIVER_BINDING_STOP       Stop;
  UINT32                        Version;
  EFI_HANDLE                    ImageHandle;
  EFI_HANDLE                    DriverBindingHandle;
};
#pragma pack(1)


//
// Device Path defines and macros
//
#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80
#define END_DEVICE_PATH_TYPE                0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE      0xff
#define END_INSTANCE_DEVICE_PATH_SUBTYPE    0x01
#define END_DEVICE_PATH_LENGTH              (sizeof(EFI_DEVICE_PATH_PROTOCOL))

#define DP_IS_END_TYPE(a)
#define DP_IS_END_SUBTYPE(a)        ( ((a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))
#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define IsDevicePathUnpacked(a)     ( (a)->Type & EFI_DP_TYPE_UNPACKED )


#define SetDevicePathNodeLength(a,l) {                \
          (a)->Length[0] = (UINT8) (l);               \
          (a)->Length[1] = (UINT8) ((l) >> 8);        \
          }

#define SetDevicePathEndNode(a)  {                       \
          (a)->Type = END_DEVICE_PATH_TYPE;              \
          (a)->SubType = END_ENTIRE_DEVICE_PATH_SUBTYPE; \
          (a)->Length[0] = (UINT8) sizeof (EFI_DEVICE_PATH_PROTOCOL);      \
          (a)->Length[1] = 0;                            \
          }

//
// Hardware Device Paths
//
//
// Hardware Device Paths
//
#define HARDWARE_DEVICE_PATH      0x01

#define HW_CONTROLLER_DP          0x05
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT32                          Controller;
} CONTROLLER_DEVICE_PATH;

#define CAVIUM_NODE_PORT_TO_CONTROLLER(n,p) ((UINT32) (((n)<<8) | (p) ))
//
// Messaging Device Paths
//
#define MESSAGING_DEVICE_PATH     0x03

///
/// USB Device Path SubType.
///
#define MSG_USB_DP                0x05
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// USB Parent Port Number.
  ///
  UINT8                         ParentPortNumber;
  ///
  /// USB Interface Number.
  ///
  UINT8                         InterfaceNumber;
} USB_DEVICE_PATH;

///
/// USB Class Device Path SubType.
///
#define MSG_USB_CLASS_DP          0x0f
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// Vendor ID assigned by USB-IF. A value of 0xFFFF will
  /// match any Vendor ID.
  ///
  UINT16                        VendorId;
  ///
  /// Product ID assigned by USB-IF. A value of 0xFFFF will
  /// match any Product ID.
  ///
  UINT16                        ProductId;
  ///
  /// The class code assigned by the USB-IF. A value of 0xFF
  /// will match any class code.
  ///
  UINT8                         DeviceClass;
  ///
  /// The subclass code assigned by the USB-IF. A value of
  /// 0xFF will match any subclass code.
  ///
  UINT8                         DeviceSubClass;
  ///
  /// The protocol code assigned by the USB-IF. A value of
  /// 0xFF will match any protocol code.
  ///
  UINT8                         DeviceProtocol;
} USB_CLASS_DEVICE_PATH;

///
/// USB WWID Device Path SubType.
///
#define MSG_USB_WWID_DP           0x10

///
/// This device path describes a USB device using its serial number.
///
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  ///
  /// USB interface number.
  ///
  UINT16                        InterfaceNumber;
  ///
  /// USB vendor id of the device.
  ///
  UINT16                        VendorId;
  ///
  /// USB product id of the device.
  ///
  UINT16                        ProductId;
  ///
  /// Last 64-or-fewer UTF-16 characters of the USB
  /// serial number. The length of the string is
  /// determined by the Length field less the offset of the
  /// Serial Number field (10)
  ///
  /// CHAR16                     SerialNumber[...];
} USB_WWID_DEVICE_PATH;



#pragma pack()
//
// Define macros to build data structure signatures from characters.
//
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))
#define SIGNATURE_64(A, B, C, D, E, F, G, H) \
    (SIGNATURE_32 (A, B, C, D) | ((UINT64) (SIGNATURE_32 (E, F, G, H)) << 32))


UINTN
/* EFIAPI */
/* Glue */GetDevicePathSize (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath
    );
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/DuplicateDevicePath (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath
      );
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/AppendDevicePath (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *FirstDevicePath,  OPTIONAL
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *SecondDevicePath  OPTIONAL
      );
EFI_DEVICE_PATH_PROTOCOL *
/*EFIAPI
  Glue*/AppendDevicePathNode (
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePath,     OPTIONAL
  IN CONST EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode  OPTIONAL
      );
#endif
