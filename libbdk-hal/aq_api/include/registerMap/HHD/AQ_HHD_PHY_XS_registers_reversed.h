/*! \file 
*   This file contains the data structures and doxygen comments
*   for the PHY_XS Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup PHY_XS_registers PHY_XS Registers
*   This module contains the data structures and doxygen comments
*   for the PHY_XS Registers block.
 */        
/***********************************************************************
*                 Copyright Aquantia Corporation
*                             Freeware
*
* $Date: 2015/09/25 $
*
* $Label: $
*
* Description:
*
*   This file contains the c header structures for the registers contained in the PHY_XS Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_HHD_PHY_XS_REGS_HEADER
#define AQ_HHD_PHY_XS_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Control 1: 04.0000 */
/*                  PHY XS Standard Control 1: 04.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 04.0000.F R/WSC Reset
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.reset

                        Default = 0x1

                        1 = PHY XS reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        Resets the entire PHY.
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PHY XS registers after this bit is set.
                          */
      unsigned int   reset : 1;    /* 04.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PHY XS reset
                        0 = Normal operation
                          */
                    /*! \brief 04.0000.E R/W Loopback
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.loopback

                        Default = 0x0

                        1 = System Interface Network Loopback
                        0 = Normal operation

                 <B>Notes:</B>
                        This enables network loopback on the designated system interface.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopback : 1;    /* 04.0000.E  R/W      Default = 0x0 */
                     /* 1 = System Interface Network Loopback
                        0 = Normal operation  */
                    /*! \brief 04.0000.D ROS Speed Selection 0
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.speedSelection_0

                        Default = 0x1

                        1 = 10Gb/s and above
                        0 = Unspecified

                 <B>Notes:</B>
                        This should always be set to 1  */
      unsigned int   speedSelection_0 : 1;    /* 04.0000.D  ROS      Default = 0x1 */
                     /* 1 = 10Gb/s and above
                        0 = Unspecified  */
      unsigned int   reserved0 : 1;
                    /*! \brief 04.0000.B R/W Low Power
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.lowPower

                        Default = 0x0

                        1 = Low-power mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        A one written to this register causes the PHY XS to enter low-power mode. If a global chip low-power state is desired, use Bit B in  See PHY XS Standard Control 1 - Address 4.0 should be set.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   lowPower : 1;    /* 04.0000.B  R/W      Default = 0x0 */
                     /* 1 = Low-power mode
                        0 = Normal operation
                          */
                    /*! \brief 04.0000.A R/W Clock Stop Enable
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.clockStopEnable

                        Default = 0x0

                        1 = The PHY XS may stop the clock during LPI
                        0 = Clock not stoppable
  */
      unsigned int   clockStopEnable : 1;    /* 04.0000.A  R/W      Default = 0x0 */
                     /* 1 = The PHY XS may stop the clock during LPI
                        0 = Clock not stoppable  */
                    /*! \brief 04.0000.9 R/W XAUI Stop Enable
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.xauiStopEnable

                        Default = 0x0

                        1 = The PHY XS may stop XAUI signals during LPI
                        0 = XAUI not stoppable
  */
      unsigned int   xauiStopEnable : 1;    /* 04.0000.9  R/W      Default = 0x0 */
                     /* 1 = The PHY XS may stop XAUI signals during LPI
                        0 = XAUI not stoppable  */
      unsigned int   reserved1 : 2;
                    /*! \brief 04.0000.6 ROS Speed Selection 1
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.speedSelection_1

                        Default = 0x1

                        1 = 10Gb/s and above
                        0 = Unspecified

                 <B>Notes:</B>
                        This should always be set to 1  */
      unsigned int   speedSelection_1 : 1;    /* 04.0000.6  ROS      Default = 0x1 */
                     /* 1 = 10Gb/s and above
                        0 = Unspecified  */
                    /*! \brief 04.0000.5:2 ROS Speed Selection 2 [3:0]
                        AQ_PhyXS_StandardControl_1_HHD.u0.bits_0.speedSelection_2

                        Default = 0x0

                        1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s

                 <B>Notes:</B>
                        This should always be set to 0  */
      unsigned int   speedSelection_2 : 4;    /* 04.0000.5:2  ROS      Default = 0x0 */
                     /* 1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardControl_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Status 1: 04.0001 */
/*                  PHY XS Standard Status 1: 04.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Status 1 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 04.0001.B LH Tx LPI Received
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.txLpiReceived

                        

                        1 = Tx PHY XS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.3:0.   */
      unsigned int   txLpiReceived : 1;    /* 04.0001.B  LH       */
                     /* 1 = Tx PHY XS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 04.0001.A LH Rx LPI Received
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.rxLpiReceived

                        

                        1 = Rx PHY XS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.3:0.   */
      unsigned int   rxLpiReceived : 1;    /* 04.0001.A  LH       */
                     /* 1 = Rx PHY XS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 04.0001.9 RO Tx LPI Indication
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.txLpiIndication

                        

                        1 = Tx PHY XS is currently receiving LPI
                        0 = Tx PHY XS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.3:0.  */
      unsigned int   txLpiIndication : 1;    /* 04.0001.9  RO       */
                     /* 1 = Tx PHY XS is currently receiving LPI
                        0 = Tx PHY XS is not currently receiving LPI
                          */
                    /*! \brief 04.0001.8 RO Rx LPI Indication
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.rxLpiIndication

                        

                        1 = Rx PHY XS is currently receiving LPI
                        0 = Rx PHY XS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.3:0.  */
      unsigned int   rxLpiIndication : 1;    /* 04.0001.8  RO       */
                     /* 1 = Rx PHY XS is currently receiving LPI
                        0 = Rx PHY XS is not currently receiving LPI
                          */
                    /*! \brief 04.0001.7 RO Fault
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PHY XS (aka XAUI) block, This bit is set if either of the two bits 4.8.B or 4.8.A are set.  */
      unsigned int   fault : 1;    /* 04.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
                    /*! \brief 04.0001.6 ROS Clock Stop Capable
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.clockStopCapable

                        Default = 0x0

                        1 = The attached PHY may stop the clock during LPI
                        0 = Clock not stoppable
                        
  */
      unsigned int   clockStopCapable : 1;    /* 04.0001.6  ROS      Default = 0x0 */
                     /* 1 = The attached PHY may stop the clock during LPI
                        0 = Clock not stoppable
                          */
      unsigned int   reserved1 : 3;
                    /*! \brief 04.0001.2 LL PHY XS Transmit Link Alignment Status
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.phyXS_TransmitLinkAlignmentStatus

                        

                        Status of receive XAUI interface alignment:
                        
                        1 = XAUI receiver is aligned correctly
                        0 = XAUI receiver is not aligned
                        

                 <B>Notes:</B>
                        This indicates the status of the lane alignment function on the receive XAUI interface. This is a latching low version of Bit 4.18.C.  */
      unsigned int   phyXS_TransmitLinkAlignmentStatus : 1;    /* 04.0001.2  LL       */
                     /* Status of receive XAUI interface alignment:
                        
                        1 = XAUI receiver is aligned correctly
                        0 = XAUI receiver is not aligned
                          */
                    /*! \brief 04.0001.1 ROS Low Power Ability
                        AQ_PhyXS_StandardStatus_1_HHD.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PHY XS supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the XAUI interface supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 04.0001.1  ROS      Default = 0x1 */
                     /* 1 = PHY XS supports low-power mode
                        0 = no low-power mode supported  */
      unsigned int   reserved2 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardStatus_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Device Identifier: 04.0002 */
/*                  PHY XS Standard Device Identifier: 04.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_PhyXS_StandardDeviceIdentifier_HHD.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 04.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.0003.F:0 RO Device ID LSW [F:0]
                        AQ_PhyXS_StandardDeviceIdentifier_HHD.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 04.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardDeviceIdentifier_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Speed Ability: 04.0004 */
/*                  PHY XS Standard Speed Ability: 04.0004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Speed Ability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.0004.0 ROS 10G Capable
                        AQ_PhyXS_StandardSpeedAbility_HHD.u0.bits_0._10gCapable

                        Default = 0x1

                        1 = PHY XS is 10 Gb/s capable
                        0 = PHY XS is not 10 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   _10gCapable : 1;    /* 04.0004.0  ROS      Default = 0x1 */
                     /* 1 = PHY XS is 10 Gb/s capable
                        0 = PHY XS is not 10 Gb/s capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardSpeedAbility_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Devices in Package: 04.0005 */
/*                  PHY XS Standard Devices in Package: 04.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 04.0005.7 ROS Autonegotiation Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 04.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 04.0005.6 ROS TC Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 04.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 04.0005.5 ROS DTE XS Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 04.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package  */
                    /*! \brief 04.0005.4 ROS PHY XS Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 04.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 04.0005.3 ROS PCS Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 04.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 04.0005.2 ROS WIS Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 04.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 04.0005.1 ROS PMA Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 04.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 04.0005.0 ROS Clause 22 Registers Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 04.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 04.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 04.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 04.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the Global registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 04.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 04.0006.D ROS Clause 22 Extension Present
                        AQ_PhyXS_StandardDevicesInPackage_HHD.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 04.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardDevicesInPackage_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Status 2: 04.0008 */
/*                  PHY XS Standard Status 2: 04.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 04.0008.F:E ROS Device Present [1:0]
                        AQ_PhyXS_StandardStatus_2_HHD.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address
                        

                 <B>Notes:</B>
                        This field is always set to 2, as the PHY XS is present in the PHY.
                          */
      unsigned int   devicePresent : 2;    /* 04.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 04.0008.B LH Transmit Fault
                        AQ_PhyXS_StandardStatus_2_HHD.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. A fault will be indicated if there is an alignment fault, a synchronization fault on any lane, or a FIFO underflow/overflow error.  */
      unsigned int   transmitFault : 1;    /* 04.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
                    /*! \brief 04.0008.A LH Receive Fault
                        AQ_PhyXS_StandardStatus_2_HHD.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path. A fault will be indicated if there is a FIFO underflow/overflow error.  */
      unsigned int   receiveFault : 1;    /* 04.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
      unsigned int   reserved1 : 10;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardStatus_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Package Identifier: 04.000E */
/*                  PHY XS Standard Package Identifier: 04.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_PhyXS_StandardPackageIdentifier_HHD.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 04.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.000F.F:0 RO Package ID LSW [F:0]
                        AQ_PhyXS_StandardPackageIdentifier_HHD.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 04.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardPackageIdentifier_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS EEE Capability Register: 04.0014 */
/*                  PHY XS EEE Capability Register: 04.0014 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS EEE Capability Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 04.0014.4 ROS PHY XS EEE
                        AQ_PhyXS_EeeCapabilityRegister_HHD.u0.bits_0.phyXS_Eee

                        Default = 0x1

                        1 = EEE is supported for PHY XS
                        0 = EEE is not supported for PHY XS
  */
      unsigned int   phyXS_Eee : 1;    /* 04.0014.4  ROS      Default = 0x1 */
                     /* 1 = EEE is supported for PHY XS
                        0 = EEE is not supported for PHY XS  */
      unsigned int   reserved1 : 3;
                    /*! \brief 04.0014.0 ROS XAUI Stop Capable
                        AQ_PhyXS_EeeCapabilityRegister_HHD.u0.bits_0.xauiStopCapable

                        Default = 0x0

                        1 = The DTE XS may stop XAUI signals during LPI
                        0 = XAUI signals not stoppable
  */
      unsigned int   xauiStopCapable : 1;    /* 04.0014.0  ROS      Default = 0x0 */
                     /* 1 = The DTE XS may stop XAUI signals during LPI
                        0 = XAUI signals not stoppable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_EeeCapabilityRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS EEE Wake Error Counter: 04.0016 */
/*                  PHY XS EEE Wake Error Counter: 04.0016 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS EEE Wake Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.0016.F:0 SCT EEE Wake Error Counter [F:0]
                        AQ_PhyXS_EeeWakeErrorCounter_HHD.u0.bits_0.eeeWakeErrorCounter

                        Default = 0x0000

                        EEE wake error counter
                        

                 <B>Notes:</B>
                        This register is a 16-bit saturating clear on read counter. The wake error source is configured with 1E.C4A2.A:8. The default wake error source is from the TXI.  */
      unsigned int   eeeWakeErrorCounter : 16;    /* 04.0016.F:0  SCT      Default = 0x0000 */
                     /* EEE wake error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_EeeWakeErrorCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard XGXS Lane Status: 04.0018 */
/*                  PHY XS Standard XGXS Lane Status: 04.0018 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard XGXS Lane Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 3;
                    /*! \brief 04.0018.C RO PHY XGXS Lane Alignment Status
                        AQ_PhyXS_StandardXGXS_LaneStatus_HHD.u0.bits_0.phyXGXS_LaneAlignmentStatus

                        

                        1 = XAUI Rx lanes aligned
                        0 = XAUI Rx lanes not aligned
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the four XAUI Rx lanes are properly aligned. This is a non-latching version of bit 4.1.2.  */
      unsigned int   phyXGXS_LaneAlignmentStatus : 1;    /* 04.0018.C  RO       */
                     /* 1 = XAUI Rx lanes aligned
                        0 = XAUI Rx lanes not aligned
                          */
                    /*! \brief 04.0018.B ROS PHY XGXS Pattern Testing Ability
                        AQ_PhyXS_StandardXGXS_LaneStatus_HHD.u0.bits_0.phyXGXS_PatternTestingAbility

                        Default = 0x1

                        1 = XAUI has the ability to generate XAUI Tx test patterns
                        0 = XAUI does not have the ability to generate XAUI Tx test patterns

                 <B>Notes:</B>
                        This is always set to 1 as the PHY is capable of generating test patterns at the XAUI interface.  */
      unsigned int   phyXGXS_PatternTestingAbility : 1;    /* 04.0018.B  ROS      Default = 0x1 */
                     /* 1 = XAUI has the ability to generate XAUI Tx test patterns
                        0 = XAUI does not have the ability to generate XAUI Tx test patterns  */
                    /*! \brief 04.0018.A ROS PHY XGXS Loopback Ability
                        AQ_PhyXS_StandardXGXS_LaneStatus_HHD.u0.bits_0.phyXGXS_LoopbackAbility

                        Default = 0x1

                        1 = XAUI has the ability to perform a loopback function
                        0 = XAUI does not have the ability to perform a loopback function

                 <B>Notes:</B>
                        This is always set to 1 as the PHY is capable of performing loopback at the XAUI interface.  */
      unsigned int   phyXGXS_LoopbackAbility : 1;    /* 04.0018.A  ROS      Default = 0x1 */
                     /* 1 = XAUI has the ability to perform a loopback function
                        0 = XAUI does not have the ability to perform a loopback function  */
      unsigned int   reserved1 : 6;
                    /*! \brief 04.0018.3:0 RO Lane Sync [3:0]
                        AQ_PhyXS_StandardXGXS_LaneStatus_HHD.u0.bits_0.laneSync

                        

                        1 = Lane is synchronized
                        0 = Lane is not synchronized
                        Bit 0 corresponds to Lane 0 and so on
                        

                 <B>Notes:</B>
                        When set, these bits indicates that the corresponding lane of the XAUI interface is synchronized.  */
      unsigned int   laneSync : 4;    /* 04.0018.3:0  RO       */
                     /* 1 = Lane is synchronized
                        0 = Lane is not synchronized
                        Bit 0 corresponds to Lane 0 and so on
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardXGXS_LaneStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard XGXS Test Control: 04.0019 */
/*                  PHY XS Standard XGXS Test Control: 04.0019 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard XGXS Test Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 04.0019.2 R/WPD Receive Test- Pattern Enable
                        AQ_PhyXS_StandardXGXS_TestControl_HHD.u0.bits_0.receiveTest_PatternEnable

                        Provisionable Default = 0x0

                        1 = XAUI Tx test pattern enabled
                        0 = XAUI Tx test pattern not enabled
                        
                        

                 <B>Notes:</B>
                        When set, this bit places the transmitters of the XAUI interface into test pattern mode.  */
      unsigned int   receiveTest_PatternEnable : 1;    /* 04.0019.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = XAUI Tx test pattern enabled
                        0 = XAUI Tx test pattern not enabled
                        
                          */
                    /*! \brief 04.0019.1:0 R/WPD Test-Pattern Select [1:0]
                        AQ_PhyXS_StandardXGXS_TestControl_HHD.u0.bits_0.test_patternSelect

                        Provisionable Default = 0x2

                        0x3 = Reserved
                        0x2 = Mixed-frequency test pattern
                        0x1 = Low-frequency test pattern
                        0x0 = High-frequency test pattern
                        

                 <B>Notes:</B>
                        These test patterns are described in Annex 48A of 802.3ae. These bits also interact with the Extended Test Pattern Control bits [C:B] in  See PHY XS Vendor Transmit Control - Address 4.8800 . The full range of options is described there, but for these functions to correspond to the test-patterns described here, bits [C:B] must be set to zero.  */
      unsigned int   test_patternSelect : 2;    /* 04.0019.1:0  R/WPD      Provisionable Default = 0x2 */
                     /* 0x3 = Reserved
                        0x2 = Mixed-frequency test pattern
                        0x1 = Low-frequency test pattern
                        0x0 = High-frequency test pattern
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardXGXS_TestControl_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PHY XS Capability: 04.1800 */
/*                  TimeSync PHY XS Capability: 04.1800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PHY XS Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 04.1800.1 RO TimeSync Transmit Path Data Delay
                        AQ_TimesyncPhyXsCapability_HHD.u0.bits_0.timesyncTransmitPathDataDelay

                        

                        1 = PHY XS provides information on transmit path data delay in registers 4.1801 through 4.1804
                        0 = PHY XS does not provide information on transmit path data delay
  */
      unsigned int   timesyncTransmitPathDataDelay : 1;    /* 04.1800.1  RO       */
                     /* 1 = PHY XS provides information on transmit path data delay in registers 4.1801 through 4.1804
                        0 = PHY XS does not provide information on transmit path data delay  */
                    /*! \brief 04.1800.0 RO TimeSync Receive Path Data Delay
                        AQ_TimesyncPhyXsCapability_HHD.u0.bits_0.timesyncReceivePathDataDelay

                        

                        1 = PHY XS provides information on receive path data delay in registers 4.1805 through 4.1808
                        0 = PHY XS does not provide information on receive path data delay
  */
      unsigned int   timesyncReceivePathDataDelay : 1;    /* 04.1800.0  RO       */
                     /* 1 = PHY XS provides information on receive path data delay in registers 4.1805 through 4.1808
                        0 = PHY XS does not provide information on receive path data delay  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_TimesyncPhyXsCapability_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PHY XS Transmit Path Data Delay: 04.1801 */
/*                  TimeSync PHY XS Transmit Path Data Delay: 04.1801 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PHY XS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1801.F:0 RO Maximum PHY XS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPhyXsTransmitPathDataDelay_HHD.u0.bits_0.maximumPhyXsTransmitPathDataDelayLSW

                        

                        LSW of maximum PHY XS transmit delay in nanoseconds
  */
      unsigned int   maximumPhyXsTransmitPathDataDelayLSW : 16;    /* 04.1801.F:0  RO       */
                     /* LSW of maximum PHY XS transmit delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PHY XS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1802.F:0 RO Maximum PHY XS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPhyXsTransmitPathDataDelay_HHD.u1.bits_1.maximumPhyXsTransmitPathDataDelayMSW

                        

                        MSW of maximum PHY XS transmit delay in nanoseconds
  */
      unsigned int   maximumPhyXsTransmitPathDataDelayMSW : 16;    /* 04.1802.F:0  RO       */
                     /* MSW of maximum PHY XS transmit delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PHY XS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1803.F:0 RO Minimum PHY XS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPhyXsTransmitPathDataDelay_HHD.u2.bits_2.minimumPhyXsTransmitPathDataDelayLSW

                        

                        LSW of minimum PHY XS transmit delay in nanoseconds
  */
      unsigned int   minimumPhyXsTransmitPathDataDelayLSW : 16;    /* 04.1803.F:0  RO       */
                     /* LSW of minimum PHY XS transmit delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PHY XS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1804.F:0 RO Minimum PHY XS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPhyXsTransmitPathDataDelay_HHD.u3.bits_3.minimumPhyXsTransmitPathDataDelayMSW

                        

                        MSW of minimum PHY XS transmit delay in nanoseconds
  */
      unsigned int   minimumPhyXsTransmitPathDataDelayMSW : 16;    /* 04.1804.F:0  RO       */
                     /* MSW of minimum PHY XS transmit delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPhyXsTransmitPathDataDelay_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PHY XS Receive Path Data Delay: 04.1805 */
/*                  TimeSync PHY XS Receive Path Data Delay: 04.1805 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PHY XS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1805.F:0 RO Maximum PHY XS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPhyXsReceivePathDataDelay_HHD.u0.bits_0.maximumPhyXsReceivePathDataDelayLSW

                        

                        LSW of maximum PHY XS receive delay in nanoseconds
  */
      unsigned int   maximumPhyXsReceivePathDataDelayLSW : 16;    /* 04.1805.F:0  RO       */
                     /* LSW of maximum PHY XS receive delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PHY XS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1806.F:0 RO Maximum PHY XS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPhyXsReceivePathDataDelay_HHD.u1.bits_1.maximumPhyXsReceivePathDataDelayMSW

                        

                        MSW of maximum PHY XS receive delay in nanoseconds
  */
      unsigned int   maximumPhyXsReceivePathDataDelayMSW : 16;    /* 04.1806.F:0  RO       */
                     /* MSW of maximum PHY XS receive delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PHY XS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1807.F:0 RO Minimum PHY XS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPhyXsReceivePathDataDelay_HHD.u2.bits_2.minimumPhyXsReceivePathDataDelayLSW

                        

                        LSW of minimum PHY XS receive delay in nanoseconds
  */
      unsigned int   minimumPhyXsReceivePathDataDelayLSW : 16;    /* 04.1807.F:0  RO       */
                     /* LSW of minimum PHY XS receive delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PHY XS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 04.1808.F:0 RO Minimum PHY XS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPhyXsReceivePathDataDelay_HHD.u3.bits_3.minimumPhyXsReceivePathDataDelayMSW

                        

                        MSW of minimum PHY XS receive delay in nanoseconds
  */
      unsigned int   minimumPhyXsReceivePathDataDelayMSW : 16;    /* 04.1808.F:0  RO       */
                     /* MSW of minimum PHY XS receive delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPhyXsReceivePathDataDelay_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Configuration: 04.C180 */
/*                  PHY XS SERDES Configuration: 04.C180 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 04.C180.4 R/W SERDES Configuration Reserved 1-1
                        AQ_PhyXS_SerdesConfiguration_HHD.u0.bits_0.serdesConfigurationReserved_1_1

                        Default = 0x0

                        Reserved
                        
  */
      unsigned int   serdesConfigurationReserved_1_1 : 1;    /* 04.C180.4  R/W      Default = 0x0 */
                     /* Reserved
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.C180.2:0 R/W SERDES Configuration Reserved 1-2 [2:0]
                        AQ_PhyXS_SerdesConfiguration_HHD.u0.bits_0.serdesConfigurationReserved_1_2

                        Default = 0x0

                        Reserved
                        
  */
      unsigned int   serdesConfigurationReserved_1_2 : 3;    /* 04.C180.2:0  R/W      Default = 0x0 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesConfiguration_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 0 Configuration: 04.C1C0 */
/*                  PHY XS SERDES Lane 0 Configuration: 04.C1C0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 0 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1C0.0 R/W SERDES Lane 0 Configuration Reserved 1
                        AQ_PhyXS_SerdesLane_0Configuration_HHD.u0.bits_0.serdesLane_0ConfigurationReserved_1

                        Default = 0x1

                        Reserved
                        
  */
      unsigned int   serdesLane_0ConfigurationReserved_1 : 1;    /* 04.C1C0.0  R/W      Default = 0x1 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_0Configuration_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 1 Configuration: 04.C1D0 */
/*                  PHY XS SERDES Lane 1 Configuration: 04.C1D0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 1 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1D0.0 R/W SERDES Lane 1 Configuration Reserved 1
                        AQ_PhyXS_SerdesLane_1Configuration_HHD.u0.bits_0.serdesLane_1ConfigurationReserved_1

                        Default = 0x1

                        Reserved
                        
  */
      unsigned int   serdesLane_1ConfigurationReserved_1 : 1;    /* 04.C1D0.0  R/W      Default = 0x1 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_1Configuration_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 2 Configuration: 04.C1E0 */
/*                  PHY XS SERDES Lane 2 Configuration: 04.C1E0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 2 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1E0.0 R/W SERDES Lane 2 Configuration Reserved 1
                        AQ_PhyXS_SerdesLane_2Configuration_HHD.u0.bits_0.serdesLane_2ConfigurationReserved_1

                        Default = 0x1

                        Reserved
                        
  */
      unsigned int   serdesLane_2ConfigurationReserved_1 : 1;    /* 04.C1E0.0  R/W      Default = 0x1 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_2Configuration_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 3 Configuration: 04.C1F0 */
/*                  PHY XS SERDES Lane 3 Configuration: 04.C1F0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 3 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1F0.0 R/W SERDES Lane 3 Configuration Reserved 1
                        AQ_PhyXS_SerdesLane_3Configuration_HHD.u0.bits_0.serdesLane_3ConfigurationReserved_1

                        Default = 0x1

                        Reserved
                        
  */
      unsigned int   serdesLane_3ConfigurationReserved_1 : 1;    /* 04.C1F0.0  R/W      Default = 0x1 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_3Configuration_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES LUT: 04.C200 */
/*                  PHY XS SERDES LUT: 04.C200 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES LUT */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 04.C200.7:0 R/W SERDES LUT 256 Reserved [7:0]
                        AQ_PhyXS_SerdesLut_HHD.u0.bits_0.serdesLut_256Reserved

                        Default = 0x00

                        Reserved
                        

                 <B>Notes:</B>
                        Spans 0xC200 to 0xC2FF.
                          */
      unsigned int   serdesLut_256Reserved : 8;    /* 04.C200.7:0  R/W      Default = 0x00 */
                     /* Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLut_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning: 04.C440 */
/*                  PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning: 04.C440 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C440.F:D R/WPD Reserved Transmit Provisioning C440 [2:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u0.bits_0.reservedTransmitProvisioningC440

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioningC440 : 3;    /* 04.C440.F:D  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C440.C R/WPD 50 MHz Primary Output Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u0.bits_0._50MhzPrimaryOutputEnable

                        Provisionable Default = 0x0

                        This bit enables the output of the 50 MHz reference clock on the primary output:
                        1 = Enable the 50 MHz primary output
                        0 = Disable the 50 MHz primary output
                        

                 <B>Notes:</B>
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _50MhzPrimaryOutputEnable : 1;    /* 04.C440.C  R/WPD      Provisionable Default = 0x0 */
                     /* This bit enables the output of the 50 MHz reference clock on the primary output:
                        1 = Enable the 50 MHz primary output
                        0 = Disable the 50 MHz primary output
                          */
                    /*! \brief 04.C440.B R/WPD 50 MHz Secondary Output Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u0.bits_0._50MhzSecondaryOutputEnable

                        Provisionable Default = 0x0

                        This bit enables the output of the 50 MHz reference clock on the secondary output:
                        1 = Enable the 50 MHz secondary output
                        0 = Disable the 50 MHz secondary output
                        

                 <B>Notes:</B>
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _50MhzSecondaryOutputEnable : 1;    /* 04.C440.B  R/WPD      Provisionable Default = 0x0 */
                     /* This bit enables the output of the 50 MHz reference clock on the secondary output:
                        1 = Enable the 50 MHz secondary output
                        0 = Disable the 50 MHz secondary output
                          */
                    /*! \brief 04.C440.A:1 R/WPD Reserved Transmit Provisioning 1 [9:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u0.bits_0.reservedTransmitProvisioning_1

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_1 : 10;    /* 04.C440.A:1  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C440.0 R/WSC SERDES Reset
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u0.bits_0.serdesReset

                        Default = 0x0

                        1 = Reset SERDES
                        0 = Reset completed

                 <B>Notes:</B>
                        This self-clearing register reinitializes the SERDES. If the network interface is linked, the SERDES will be reinitialized at the current line rate. If not, the rate used will be based on the SERDES startup mode.
                        
                        NOTE! This bit will not self-clear in the absence of a valid Rx signal that can be used to perform Rx autocal
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   serdesReset : 1;    /* 04.C440.0  R/WSC      Default = 0x0 */
                     /* 1 = Reset SERDES
                        0 = Reset completed  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C441.F:E R/WPD System I/F 10G Operating Mode [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.systemI_f10G_OperatingMode

                        Provisionable Default = 0x0

                        This field sets the 10G configuration of the system I/F:
                        0x0 = XAUI
                        0x1 = RXAUI
                        0x2 = KR (SERDES2 = XFI1)
                        0x3 = Reserved
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.
                        
                        NOTE! The start-up mode for these rates is selected in 7.C410.F:D. Also - KR autonegotiation is not supported as it is not defined to operate with Clause 28 Autonegotation. If UXSGMII operation is desired, select KR, and it will be used for all rates.  */
      unsigned int   systemI_f10G_OperatingMode : 2;    /* 04.C441.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This field sets the 10G configuration of the system I/F:
                        0x0 = XAUI
                        0x1 = RXAUI
                        0x2 = KR (SERDES2 = XFI1)
                        0x3 = Reserved
                          */
                    /*! \brief 04.C441.D R/WPD System I/F 2500BASE-X Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.systemI_f_2500base_xEnable

                        Provisionable Default = 0x0

                        0 = Normal mode
                        1 = Enable 2500BASE-X mode for 2.5G
                        

                 <B>Notes:</B>
                        If enabled, 2500BASE-X mode will be used for 2.5G. In normal mode, 2.5G operation depends on the 10G Operating Mode setting (4.C441.[F:E])
                        
                        Operation mode of other speeds depend on the 10G Operating Mode setting and SERDES Start-Up Mode (7.C410.[F:D]).  */
      unsigned int   systemI_f_2500base_xEnable : 1;    /* 04.C441.D  R/WPD      Provisionable Default = 0x0 */
                     /* 0 = Normal mode
                        1 = Enable 2500BASE-X mode for 2.5G
                          */
                    /*! \brief 04.C441.C:B R/WPD System I/F 1G/100M Operating Mode [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.systemI_f1G_100M_OperatingMode

                        Provisionable Default = 0x0

                        This field sets the 1G/100M configuration of the system I/F:
                        0x0 = Normal mode
                        0x1 = XFI
                        0x2 - 0x3 = reserved
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.
                        
                        In normal mode, 1G/100M operating mode depends on the SERDES Start-Up Mode (7.C410.[F:D])  */
      unsigned int   systemI_f1G_100M_OperatingMode : 2;    /* 04.C441.C:B  R/WPD      Provisionable Default = 0x0 */
                     /* This field sets the 1G/100M configuration of the system I/F:
                        0x0 = Normal mode
                        0x1 = XFI
                        0x2 - 0x3 = reserved
                          */
                    /*! \brief 04.C441.A R/WPD SGMII 1G/100M Autoneg Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.sgmii1G_100M_AutonegEnable

                        Provisionable Default = 0x0

                        1 = Enable Clause 37 SGMII 1G/100M Autoneg
                        0 = Disable Clause 37 SGMII 1G/100M Autoneg
                        
  */
      unsigned int   sgmii1G_100M_AutonegEnable : 1;    /* 04.C441.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable Clause 37 SGMII 1G/100M Autoneg
                        0 = Disable Clause 37 SGMII 1G/100M Autoneg
                          */
                    /*! \brief 04.C441.9 R/WPD OCSGMII 2.5G Autoneg Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.ocsgmii_2_5gAutonegEnable

                        Provisionable Default = 0x0

                        1 = Enable Clause 37 OCSGMII 2.5G Autoneg
                        0 = Disable Clause 37 OCSGMII 2.5G Autoneg
                        
  */
      unsigned int   ocsgmii_2_5gAutonegEnable : 1;    /* 04.C441.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable Clause 37 OCSGMII 2.5G Autoneg
                        0 = Disable Clause 37 OCSGMII 2.5G Autoneg
                          */
                    /*! \brief 04.C441.8:6 R/WPD PHY Operating Mode [2:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.phyOperatingMode

                        Provisionable Default = 0x0

                        This field sets the connectivity of the PHY:
                        0x0 = Selected 10G mode on System I/F
                        UTP (RJ-45) is Network I/F
                        0x1 = Look-aside Mode: KR1 is System I/F (SERDES 2 = XFI1 / SGMII1)
                        KR0 is Network I/F (SERDES 0 = SFI0 / SGMII0)
                        0x2 = 1+ 1 (SERDES 2 = KR1 / SGMII1 of the selected PHY (see Bit 5) is the System I/F)
                        0x3 = Reserved
                        0x4 -> 0x7 = Reserved
                        

                 <B>Notes:</B>
                        This register selects the basic PHY configuration. This field can only be changed via provisioning.  */
      unsigned int   phyOperatingMode : 3;    /* 04.C441.8:6  R/WPD      Provisionable Default = 0x0 */
                     /* This field sets the connectivity of the PHY:
                        0x0 = Selected 10G mode on System I/F
                        UTP (RJ-45) is Network I/F
                        0x1 = Look-aside Mode: KR1 is System I/F (SERDES 2 = XFI1 / SGMII1)
                        KR0 is Network I/F (SERDES 0 = SFI0 / SGMII0)
                        0x2 = 1+ 1 (SERDES 2 = KR1 / SGMII1 of the selected PHY (see Bit 5) is the System I/F)
                        0x3 = Reserved
                        0x4 -> 0x7 = Reserved
                          */
                    /*! \brief 04.C441.5 R/WPD RXAUI Operating Mode
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.rxauiOperatingMode

                        Provisionable Default = 0x0

                        1 = Dune
                        0 = Marvell
                        

                 <B>Notes:</B>
                        This bit governs whether the RXAUI functions
                        in Marvell mode (default) or Dune mode.  */
      unsigned int   rxauiOperatingMode : 1;    /* 04.C441.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Dune
                        0 = Marvell
                          */
                    /*! \brief 04.C441.4 R/WPD Enable KR Training
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.enableKrTraining

                        Provisionable Default = 0x0

                        1 = KR Training Enabled
                        0 = KR Training Disabled
                        

                 <B>Notes:</B>
                        This bit governs whether KR training is performed if KR is selected as the 10G operating interface. NOTE! KR without training enabled is essentially XFI+.  */
      unsigned int   enableKrTraining : 1;    /* 04.C441.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = KR Training Enabled
                        0 = KR Training Disabled
                          */
                    /*! \brief 04.C441.3 R/WPD USX Autoneg Control For MAC
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.usxAutonegControlForMac

                        Provisionable Default = 0x0

                        1 = Enable
                        0 = Disable
                        

                 <B>Notes:</B>
                        USX enable/disable control for MAC. This gives USX autonegotiation control to MAC to enable/disable at any time after PHY reset.  */
      unsigned int   usxAutonegControlForMac : 1;    /* 04.C441.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable
                        0 = Disable
                          */
                    /*! \brief 04.C441.2 R/WPD Backplane ANG Enable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.backplaneAngEnable

                        Provisionable Default = 0x0

                        1000BASE-KX or 10GBASE-KR Autoneg enable/disable bit.
                        
  */
      unsigned int   backplaneAngEnable : 1;    /* 04.C441.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1000BASE-KX or 10GBASE-KR Autoneg enable/disable bit.
                          */
                    /*! \brief 04.C441.1:0 R/WPD Lookaside Port Operating Mode [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u1.bits_1.lookasidePortOperatingMode

                        Provisionable Default = 0x0

                        0x0 = 10GBASE-R (XFI0)
                        0x1 = 1000BASE-X (SGMII0)
                        0x3 = KR / USXGMII
                        

                 <B>Notes:</B>
                        This field is used to control the start-up behavior of the PHY's lookaside port I/F, when the PHY Operation Mode (Bits 7:6) is set to 0x1.  */
      unsigned int   lookasidePortOperatingMode : 2;    /* 04.C441.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = 10GBASE-R (XFI0)
                        0x1 = 1000BASE-X (SGMII0)
                        0x3 = KR / USXGMII
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C442.F:E R/WPD XAUI Rx Lane 3 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.xauiRxLane_3Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 3
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_3Serdes : 2;    /* 04.C442.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 3
                          */
                    /*! \brief 04.C442.D:C R/WPD XAUI Rx Lane 2 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.xauiRxLane_2Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 2
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_2Serdes : 2;    /* 04.C442.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 2
                          */
                    /*! \brief 04.C442.B:A R/WPD XAUI Rx Lane 1 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.xauiRxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 1
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_1Serdes : 2;    /* 04.C442.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 1
                          */
                    /*! \brief 04.C442.9:8 R/WPD XAUI Rx Lane 0 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.xauiRxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 0
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_0Serdes : 2;    /* 04.C442.9:8  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 0
                          */
                    /*! \brief 04.C442.7:4 R/WPD XAUI Rx Lane Invert [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.xauiRxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                        
  */
      unsigned int   xauiRxLaneInvert : 4;    /* 04.C442.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.C442.3:2 R/WPD System SGMII Rx SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.systemSgmiiRxSerdes

                        Provisionable Default = 0x0

                        This sets the lane to be used for System SGMII Rx Interface (GbE Tx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                        

                 <B>Notes:</B>
                        This selection is independent of what rate / format the system 10G interface is running at, except if look-aside mode (Bits 4.C441.7:6). In this case, Lane 2 must be used as the SGMII interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiRxSerdes : 2;    /* 04.C442.3:2  R/WPD      Provisionable Default = 0x0 */
                     /* This sets the lane to be used for System SGMII Rx Interface (GbE Tx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                          */
                    /*! \brief 04.C442.1 R/WPD System SGMII Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u2.bits_2.systemSgmiiRxInvert

                        Provisionable Default = 0x0

                        1 = Invert the System SGMII Rx Interface
                        

                 <B>Notes:</B>
                        This inverts the SGMII Rx interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiRxInvert : 1;    /* 04.C442.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert the System SGMII Rx Interface
                          */
      unsigned int   reserved0 : 1;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C443.F:C R/WPD Reserved Transmit Provisioning 4a [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u3.bits_3.reservedTransmitProvisioning_4a

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_4a : 4;    /* 04.C443.F:C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C443.B R/WPD System KR Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u3.bits_3.systemKrRxInvert

                        Provisionable Default = 0x0

                        1 = Invert System KR Rx (SERDES2 = KR1)
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   systemKrRxInvert : 1;    /* 04.C443.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System KR Rx (SERDES2 = KR1)
                          */
                    /*! \brief 04.C443.A R/WPD Lookaside Port Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u3.bits_3.lookasidePortRxInvert

                        Provisionable Default = 0x0

                        1 = Invert KR0 / SGMII0 Rx
                        

                 <B>Notes:</B>
                        SERDES0 = KR0 / SGMII0 is the network interface. This field can only be changed via provisioning.  */
      unsigned int   lookasidePortRxInvert : 1;    /* 04.C443.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert KR0 / SGMII0 Rx
                          */
                    /*! \brief 04.C443.9:0 R/WPD Reserved Transmit Provisioning 4 [9:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u3.bits_3.reservedTransmitProvisioning_4

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_4 : 10;    /* 04.C443.9:0  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C444.F:B R/WPD Loopback Control [4:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.loopbackControl

                        Provisionable Default = 0x00

                        0x00 = No loopback
                        0x01 = System Interface - System Loopback
                        0x02 = Reserved
                        0x03 = System Interface - Network Loopback
                        0x04 - 0x08 = Reserved
                        0x09 = Network Interface - System Loopback
                        0x0A = Reserved
                        0x0B = Network Interface - Network Loopback
                        0x0C - 0x1F = Reserved
                        
                        

                 <B>Notes:</B>
                        These bits, in conjunction with the chip configuration and the rate (Bits 1:0), select the loopback to configure for the chip. Setting one of these loopbacks provisions the chip for the specified loopback. Upon clearing the loopback, the chip returns to it's configuration prior to entering loopback (irregardless of whether other loopbacks were selected after the initial loopback).
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopbackControl : 5;    /* 04.C444.F:B  R/WPD      Provisionable Default = 0x00 */
                     /* 0x00 = No loopback
                        0x01 = System Interface - System Loopback
                        0x02 = Reserved
                        0x03 = System Interface - Network Loopback
                        0x04 - 0x08 = Reserved
                        0x09 = Network Interface - System Loopback
                        0x0A = Reserved
                        0x0B = Network Interface - Network Loopback
                        0x0C - 0x1F = Reserved
                        
                          */
                    /*! \brief 04.C444.A:6 R/WPD Reserved Transmit Provisioning 5 [4:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.reservedTransmitProvisioning_5

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_5 : 5;    /* 04.C444.A:6  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C444.5 R/WPD MDI Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.mdiPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out MDI interface
                        0 = No CRPAT packet generation out MDI interface
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output on the MDI interface at the selected rate.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   mdiPacketGeneration : 1;    /* 04.C444.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out MDI interface
                        0 = No CRPAT packet generation out MDI interface
                          */
                    /*! \brief 04.C444.4 R/WPD Look-Aside Port Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.look_asidePortPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out 10G look-aside interface (KR0)
                        0 = No CRPAT packet generation out 10G look-aside interface (KR0)
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output on KR0.
                        
                        NOTE!! This only functions if KR1 (SERDES2) is selected as the system interface in (4.C441.F:E).
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   look_asidePortPacketGeneration : 1;    /* 04.C444.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out 10G look-aside interface (KR0)
                        0 = No CRPAT packet generation out 10G look-aside interface (KR0)
                          */
                    /*! \brief 04.C444.3 R/WPD System I/F Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.systemI_fPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out 10G system interface
                        0 = No CRPAT packet generation out 10G system interface
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output CRPAT packets on the selected 10G system interface (4.C441.F:E)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   systemI_fPacketGeneration : 1;    /* 04.C444.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out 10G system interface
                        0 = No CRPAT packet generation out 10G system interface
                          */
                    /*! \brief 04.C444.2:0 R/WPD Rate [2:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u4.bits_4.rate

                        Provisionable Default = 0x0

                        0x7 - 0x6 = reserved
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10G
                        0x2 = 1G
                        0x1 = 100M
                        0x0 = reserved
                        

                 <B>Notes:</B>
                        These bits select the rate for the loopback and packet generation. SERDES configuration, as well autonegotiation is controlled accordingly when a loopback is selected. For instance, if 100M system loopback on the network interface is selected, SGMII on the system interface is enabled to connect at 100M, and if passthrough is enabled 100BASE-TX will be the only advertised rate and will force a re-autonegotiation if not already connected at 100M.  */
      unsigned int   rate : 3;    /* 04.C444.2:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x7 - 0x6 = reserved
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10G
                        0x2 = 1G
                        0x1 = 100M
                        0x0 = reserved
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C445.F:0 R/WPD Reserved Transmit Provisioning 6 [F:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u5.bits_5.reservedTransmitProvisioning_6

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_6 : 16;    /* 04.C445.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C446.F R/WPD Reserved Transmit Provisioning 7
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u6.bits_6.reservedTransmitProvisioning_7

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_7 : 1;    /* 04.C446.F  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C446.E:A R/WPD KR Trng Cpost min value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u6.bits_6.krTrngCpostMinValue

                        Provisionable Default = 0x00

                        KR Trng Cpost min value
                        

                 <B>Notes:</B>
                        KR Trng Cpost min value  */
      unsigned int   krTrngCpostMinValue : 5;    /* 04.C446.E:A  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpost min value
                          */
                    /*! \brief 04.C446.9:5 R/WPD KR Trng main min value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u6.bits_6.krTrngMainMinValue

                        Provisionable Default = 0x00

                        KR Trng Cmain min value
                        

                 <B>Notes:</B>
                        KR Trng Cmain min value  */
      unsigned int   krTrngMainMinValue : 5;    /* 04.C446.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cmain min value
                          */
                    /*! \brief 04.C446.4:0 R/WPD KR Trng Cpre min value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u6.bits_6.krTrngCpreMinValue

                        Provisionable Default = 0x00

                        KR Trng Cpre min value
                        

                 <B>Notes:</B>
                        KR Trng Cpre min value  */
      unsigned int   krTrngCpreMinValue : 5;    /* 04.C446.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpre min value
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C447.F R/WPD Reserved Transmit Provisioning 8
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u7.bits_7.reservedTransmitProvisioning_8

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_8 : 1;    /* 04.C447.F  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C447.E:A R/WPD KR Trng Cpost max value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u7.bits_7.krTrngCpostMaxValue

                        Provisionable Default = 0x00

                        KR Trng Cpost max value
                        

                 <B>Notes:</B>
                        KR Trng Cpost max value  */
      unsigned int   krTrngCpostMaxValue : 5;    /* 04.C447.E:A  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpost max value
                          */
                    /*! \brief 04.C447.9:5 R/WPD KR Trng main max value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u7.bits_7.krTrngMainMaxValue

                        Provisionable Default = 0x00

                        KR Trng Cmain max value
                        

                 <B>Notes:</B>
                        KR Trng Cmain max value  */
      unsigned int   krTrngMainMaxValue : 5;    /* 04.C447.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cmain max value
                          */
                    /*! \brief 04.C447.4:0 R/WPD KR Trng Cpre max value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u7.bits_7.krTrngCpreMaxValue

                        Provisionable Default = 0x00

                        KR Trng Cpre max value
                        

                 <B>Notes:</B>
                        KR Trng Cpre max value  */
      unsigned int   krTrngCpreMaxValue : 5;    /* 04.C447.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpre max value
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C448.F R/WPD Reserved Transmit Provisioning 9
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u8.bits_8.reservedTransmitProvisioning_9

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_9 : 1;    /* 04.C448.F  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C448.E:A R/WPD KR Trng Cpost INIT value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u8.bits_8.krTrngCpostInitValue

                        Provisionable Default = 0x00

                        KR Trng Cpost INIT value
                        

                 <B>Notes:</B>
                        KR Trng Cpost INIT value  */
      unsigned int   krTrngCpostInitValue : 5;    /* 04.C448.E:A  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpost INIT value
                          */
                    /*! \brief 04.C448.9:5 R/WPD KR Trng main INIT value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u8.bits_8.krTrngMainInitValue

                        Provisionable Default = 0x00

                        KR Trng Cmain INIT value
                        

                 <B>Notes:</B>
                        KR Trng Cmain INIT value  */
      unsigned int   krTrngMainInitValue : 5;    /* 04.C448.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cmain INIT value
                          */
                    /*! \brief 04.C448.4:0 R/WPD KR Trng Cpre INIT value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u8.bits_8.krTrngCpreInitValue

                        Provisionable Default = 0x00

                        KR Trng Cpre INIT value
                        

                 <B>Notes:</B>
                        KR Trng Cpre INIT value  */
      unsigned int   krTrngCpreInitValue : 5;    /* 04.C448.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpre INIT value
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C449.F R/WPD Reserved Transmit Provisioning 10
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u9.bits_9.reservedTransmitProvisioning_10

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_10 : 1;    /* 04.C449.F  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C449.E:A R/WPD KR Trng Cpost PRESET value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u9.bits_9.krTrngCpostPresetValue

                        Provisionable Default = 0x00

                        KR Trng Cpost PRESET value
                        

                 <B>Notes:</B>
                        KR Trng Cpost PRESET value  */
      unsigned int   krTrngCpostPresetValue : 5;    /* 04.C449.E:A  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpost PRESET value
                          */
                    /*! \brief 04.C449.9:5 R/WPD KR Trng main PRESET value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u9.bits_9.krTrngMainPresetValue

                        Provisionable Default = 0x00

                        KR Trng Cmain PRESET value
                        

                 <B>Notes:</B>
                        KR Trng Cmain PRESET value  */
      unsigned int   krTrngMainPresetValue : 5;    /* 04.C449.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cmain PRESET value
                          */
                    /*! \brief 04.C449.4:0 R/WPD KR Trng Cpre PRESET value
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD.u9.bits_9.krTrngCprePresetValue

                        Provisionable Default = 0x00

                        KR Trng Cpre PRESET value
                        

                 <B>Notes:</B>
                        KR Trng Cpre PRESET value  */
      unsigned int   krTrngCprePresetValue : 5;    /* 04.C449.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* KR Trng Cpre PRESET value
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) PCS Status: 04.C802 */
/*                  PHY XS Transmit (XAUI Rx) PCS Status: 04.C802 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.C802.F:0 SCTL Tx Frame Counter LSW [F:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_HHD.u0.bits_0.txFrameCounterLSW

                        Default = 0x0000

                        Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   txFrameCounterLSW : 16;    /* 04.C802.F:0  SCTL      Default = 0x0000 */
                     /* Tx Good Frame Counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.C803.9:0 SCTM Tx Frame Counter MSW [9:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_HHD.u1.bits_1.txFrameCounterMSW

                        Default = 0x000

                        Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   txFrameCounterMSW : 10;    /* 04.C803.9:0  SCTM      Default = 0x000 */
                     /* Tx Good Frame Counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.C804.F:0 SCTL Tx Frame Error Counter LSW [F:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_HHD.u2.bits_2.txFrameErrorCounterLSW

                        Default = 0x0000

                        Tx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   txFrameErrorCounterLSW : 16;    /* 04.C804.F:0  SCTL      Default = 0x0000 */
                     /* Tx Bad Frame Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.C805.9:0 SCTM Tx Frame Error Counter MSW [9:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_HHD.u3.bits_3.txFrameErrorCounterMSW

                        Default = 0x000

                        Tx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   txFrameErrorCounterMSW : 10;    /* 04.C805.9:0  SCTM      Default = 0x000 */
                     /* Tx Bad Frame Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PhyXS_Transmit_xauiRx_PcsStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Reserved Vendor State: 04.C820 */
/*                  PHY XS Transmit (XAUI Rx) Reserved Vendor State: 04.C820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 04.C820.F:0 RO Numbers of Serdes Cals [F:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorState_HHD.u0.bits_0.numbersOfSerdesCals

                        

                        Number of SERDES calibrations since the last PHY reset (or power-up).
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   numbersOfSerdesCals : 16;    /* 04.C820.F:0  RO       */
                     /* Number of SERDES calibrations since the last PHY reset (or power-up).
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 04.C821.F:8 RO Number of SIF Block Lock Transtitions 1 - 0 [7:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorState_HHD.u1.bits_1.numberOfSifBlockLockTranstitions_1__0

                        

                        Number of SIF block lock transitions since PHY reset from 1 to 0 i.e. loss of block lock.
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   numberOfSifBlockLockTranstitions_1__0 : 8;    /* 04.C821.F:8  RO       */
                     /* Number of SIF block lock transitions since PHY reset from 1 to 0 i.e. loss of block lock.
                          */
                    /*! \brief 04.C821.7:0 RO Number of SIF Block Lock Transtitions 0 - 1 [7:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorState_HHD.u1.bits_1.numberOfSifBlockLockTranstitions_0__1

                        

                        Number of SIF block lock transitions since PHY reset from 0 to 1, i.e. regained block lock.
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   numberOfSifBlockLockTranstitions_0__1 : 8;    /* 04.C821.7:0  RO       */
                     /* Number of SIF block lock transitions since PHY reset from 0 to 1, i.e. regained block lock.
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 04.C822.F:0 RO Number of SIF XGS Switch-overs [F:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorState_HHD.u2.bits_2.numberOfSifXgsSwitch_overs

                        

                        Number of SIF side XGS Switch-overs since Phy Reset.
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   numberOfSifXgsSwitch_overs : 16;    /* 04.C822.F:0  RO       */
                     /* Number of SIF side XGS Switch-overs since Phy Reset.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Transmit_xauiRx_ReservedVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Alarms: 04.CC00 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Alarms: 04.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.CC00.F LH CRPAT Test Pattern Checker Sync Error
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u0.bits_0.crpatTestPatternCheckerSyncError

                        

                        1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
  */
      unsigned int   crpatTestPatternCheckerSyncError : 1;    /* 04.CC00.F  LH       */
                     /* 1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                          */
                    /*! \brief 04.CC00.E:B LH PRBS Test Pattern Checker Sync Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u0.bits_0.prbsTestPatternCheckerSyncError

                        

                        1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   prbsTestPatternCheckerSyncError : 4;    /* 04.CC00.E:B  LH       */
                     /* 1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
      unsigned int   reserved0 : 10;
                    /*! \brief 04.CC00.0 LH MACSEC Egress Interrupt
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u0.bits_0.macsecEgressInterrupt

                        

                        1 = MACSEC Egress Interrupt
                        
  */
      unsigned int   macsecEgressInterrupt : 1;    /* 04.CC00.0  LH       */
                     /* 1 = MACSEC Egress Interrupt
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 04.CC01.D LH XAUI Rx Sequence Ordered Set Deletion
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxSequenceOrderedSetDeletion

                        

                        1 = Sequence ordered set was deleted on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxSequenceOrderedSetDeletion : 1;    /* 04.CC01.D  LH       */
                     /* 1 = Sequence ordered set was deleted on the XAUI Rx interface
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.CC01.B:A LL XAUI Rx Lane Alignment Lock Status [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxLaneAlignmentLockStatus

                        

                        1 = Lanes locked
                        
  */
      unsigned int   xauiRxLaneAlignmentLockStatus : 2;    /* 04.CC01.B:A  LL       */
                     /* 1 = Lanes locked
                          */
                    /*! \brief 04.CC01.9 LH XAUI Rx Reserved XGMII Character Received
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII character was received on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxReservedXgmiiCharacterReceived : 1;    /* 04.CC01.9  LH       */
                     /* 1 = Reserved XGMII character was received on the XAUI Rx interface
                          */
                    /*! \brief 04.CC01.8 LH XAUI Rx Invalid XGMII Character Received
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII character was received on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxInvalidXgmiiCharacterReceived : 1;    /* 04.CC01.8  LH       */
                     /* 1 = Invalid XGMII character was received on the XAUI Rx interface
                          */
                    /*! \brief 04.CC01.7:4 LH XAUI Rx Code Violation Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxCodeViolationError

                        

                        1 = A code violation error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   xauiRxCodeViolationError : 4;    /* 04.CC01.7:4  LH       */
                     /* 1 = A code violation error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
                    /*! \brief 04.CC01.3:0 LH XAUI Rx Running Disparity Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u1.bits_1.xauiRxRunningDisparityError

                        

                        1 = A running disparity error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   xauiRxRunningDisparityError : 4;    /* 04.CC01.3:0  LH       */
                     /* 1 = A running disparity error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.CC02.F:C LH Loss of Signal [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u2.bits_2.lossOfSignal

                        

                        1 = Loss of Signal on associated logical lane:
                        Bit 0: KR0, XAUI Lane 0, SGMII
                        Bit 1: XAUI Lane 1
                        Bit 2: KR1, XAUI Lane 2
                        Bit 3: XAUI Lane 3
                        

                 <B>Notes:</B>
                        These bits provide the Loss of Signal indication for the logical SERDES lane that loses signal.
                          */
      unsigned int   lossOfSignal : 4;    /* 04.CC02.F:C  LH       */
                     /* 1 = Loss of Signal on associated logical lane:
                        Bit 0: KR0, XAUI Lane 0, SGMII
                        Bit 1: XAUI Lane 1
                        Bit 2: KR1, XAUI Lane 2
                        Bit 3: XAUI Lane 3
                          */
                    /*! \brief 04.CC02.B:0 LH Reserved PHY XS Transmit Alarms [B:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD.u2.bits_2.reservedPhyXsTransmitAlarms

                        

                        Reserved
                        
  */
      unsigned int   reservedPhyXsTransmitAlarms : 12;    /* 04.CC02.B:0  LH       */
                     /* Reserved
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Transmit_xauiRx_VendorAlarms_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Standard Interrupt Mask: 04.D000 */
/*                  PHY XS Transmit (XAUI Rx) Standard Interrupt Mask: 04.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 04.D000.B R/WPD Tx LPI Received Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD.u0.bits_0.txLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 4.1.B.  */
      unsigned int   txLpiReceivedMask : 1;    /* 04.D000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.D000.A R/WPD Rx LPI Received Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD.u0.bits_0.rxLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 4.1.A.  */
      unsigned int   rxLpiReceivedMask : 1;    /* 04.D000.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 04.D000.2 R/WPD PHY XS Transmit Link Alignment Status Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD.u0.bits_0.phyXS_TransmitLinkAlignmentStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 4.1.2. Note this bit also shows up as Bit 4.24.C, but only as a status bit.  */
      unsigned int   phyXS_TransmitLinkAlignmentStatusMask : 1;    /* 04.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 04.D001.B R/WPD Transmit Fault Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 4.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 04.D001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D001.A R/WPD Receive Fault Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 4.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 04.D001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask: 04.D400 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask: 04.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.D400.F R/WPD CRPAT Test Pattern Checker Sync Error Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u0.bits_0.crpatTestPatternCheckerSyncErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   crpatTestPatternCheckerSyncErrorMask : 1;    /* 04.D400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D400.E:B R/WPD PRBS Test Pattern Checker Sync Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u0.bits_0.prbsTestPatternCheckerSyncErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   prbsTestPatternCheckerSyncErrorMask : 4;    /* 04.D400.E:B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 10;
                    /*! \brief 04.D400.0 R/WPD MACSEC Egress Interrupt Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u0.bits_0.macsecEgressInterruptMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   macsecEgressInterruptMask : 1;    /* 04.D400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 04.D401.D R/WPD XAUI Rx Sequence Ordered Set Deletion Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxSequenceOrderedSetDeletionMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxSequenceOrderedSetDeletionMask : 1;    /* 04.D401.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.D401.B:A R/WPD XAUI Rx Lane Alignment Lock Status Mask [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxLaneAlignmentLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xauiRxLaneAlignmentLockStatusMask : 2;    /* 04.D401.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.D401.9 R/WPD XAUI Rx Reserved XGMII Character Received Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxReservedXgmiiCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxReservedXgmiiCharacterReceivedMask : 1;    /* 04.D401.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.8 R/WPD XAUI Rx Invalid XGMII Character Received Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxInvalidXgmiiCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxInvalidXgmiiCharacterReceivedMask : 1;    /* 04.D401.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.7:4 R/WPD XAUI Rx Code Violation Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxCodeViolationErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxCodeViolationErrorMask : 4;    /* 04.D401.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.3:0 R/WPD XAUI Rx Running Disparity Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u1.bits_1.xauiRxRunningDisparityErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxRunningDisparityErrorMask : 4;    /* 04.D401.3:0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.D402.F:C R/W Loss of Signal Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u2.bits_2.lossOfSignalMask

                        Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   lossOfSignalMask : 4;    /* 04.D402.F:C  R/W      Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.D402.B:0 R/W Reserved PHY XS Transmit Alarms Mask [B:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD.u2.bits_2.reservedPhyXsTransmitAlarmsMask

                        Default = 0x000

                        Reserved
                        
  */
      unsigned int   reservedPhyXsTransmitAlarmsMask : 12;    /* 04.D402.B:0  R/W      Default = 0x000 */
                     /* Reserved
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Debug: 04.D800 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Debug: 04.D800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.D800.F R/W Test Pattern Force Error
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternForceError

                        Default = 0x0

                        1 = Force test pattern error
                        

                 <B>Notes:</B>
                        This injects 10 PRBS Errors or 32 CRPAT errors  */
      unsigned int   testPatternForceError : 1;    /* 04.D800.F  R/W      Default = 0x0 */
                     /* 1 = Force test pattern error
                          */
                    /*! \brief 04.D800.E R/W Test Pattern Mode 7 Force Error
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternMode_7ForceError

                        Default = 0x0

                        1 = Force test pattern #7 error
                        

                 <B>Notes:</B>
                        This injects 32 errors  */
      unsigned int   testPatternMode_7ForceError : 1;    /* 04.D800.E  R/W      Default = 0x0 */
                     /* 1 = Force test pattern #7 error
                          */
                    /*! \brief 04.D800.D R/W XAUI Rx Local Fault Injection
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.xauiRxLocalFaultInjection

                        Default = 0x0

                        1 = Inject local fault towards UTP Line
                        
  */
      unsigned int   xauiRxLocalFaultInjection : 1;    /* 04.D800.D  R/W      Default = 0x0 */
                     /* 1 = Inject local fault towards UTP Line
                          */
                    /*! \brief 04.D800.C:B R/WPD Test-Pattern Extended Select [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.test_patternExtendedSelect

                        Provisionable Default = 0x0

                        {Test-Pattern Extended Select [C:B],
                        Test-Pattern Select[1:0]}
                        0x0 = Annex 48A.1 High Frequency
                        0x1 = Annex 48A.2 Low Frequency
                        0x2 = Annex 48A.3 Mixed Frequency
                        0x4 = Annex 48A.4 CRPAT
                        0x5 = Annex 48A.5 CJPAT
                        0x6 = At speed CRPAT out the line
                        0x7 = PRBS-31 (x^31+x^28+1)
                        0x8 = PRBS-23 (x^23+x^18+1)
                        0x9 = PRBS-7 (x^7+x^6+1)
                        0xA = PRBS-15 (x^15+x^14+1)
                        0x3, 0xC -> 0xF = Reserved
                        

                 <B>Notes:</B>
                        These bits combine with the standard defined bits [1:0] in "PHY XS Standard XGXS Test Control: Address 4.19" on page 10 to define a broader suite of tests. 
                        
                          */
      unsigned int   test_patternExtendedSelect : 2;    /* 04.D800.C:B  R/WPD      Provisionable Default = 0x0 */
                     /* {Test-Pattern Extended Select [C:B],
                        Test-Pattern Select[1:0]}
                        0x0 = Annex 48A.1 High Frequency
                        0x1 = Annex 48A.2 Low Frequency
                        0x2 = Annex 48A.3 Mixed Frequency
                        0x4 = Annex 48A.4 CRPAT
                        0x5 = Annex 48A.5 CJPAT
                        0x6 = At speed CRPAT out the line
                        0x7 = PRBS-31 (x^31+x^28+1)
                        0x8 = PRBS-23 (x^23+x^18+1)
                        0x9 = PRBS-7 (x^7+x^6+1)
                        0xA = PRBS-15 (x^15+x^14+1)
                        0x3, 0xC -> 0xF = Reserved
                          */
                    /*! \brief 04.D800.A R/WPD Test Pattern Check Enable
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternCheckEnable

                        Provisionable Default = 0x0

                        1 = Test pattern checker enabled
                        0 = Test pattern checker not enabled
                        

                 <B>Notes:</B>
                        Test pattern checker enable. (Used for PRBS, Annex 48.4, and datapath error checking.) This should only be enabled after the test mode is selected.  */
      unsigned int   testPatternCheckEnable : 1;    /* 04.D800.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Test pattern checker enabled
                        0 = Test pattern checker not enabled
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 04.D800.7 R/WPD Test Pattern Check Point
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternCheckPoint

                        Provisionable Default = 0x0

                        Test pattern check point for CRPAT and data path tests.
                        

                 <B>Notes:</B>
                        This is latched on the rising edge of  See Test Pattern Check Enable   */
      unsigned int   testPatternCheckPoint : 1;    /* 04.D800.7  R/WPD      Provisionable Default = 0x0 */
                     /* Test pattern check point for CRPAT and data path tests.
                          */
                    /*! \brief 04.D800.6 R/WPD Test Pattern Mode 7 Check Enable
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternMode_7CheckEnable

                        Provisionable Default = 0x0

                        Enable checking for Test Mode 7
                        
  */
      unsigned int   testPatternMode_7CheckEnable : 1;    /* 04.D800.6  R/WPD      Provisionable Default = 0x0 */
                     /* Enable checking for Test Mode 7
                          */
                    /*! \brief 04.D800.5 R/WPD Test Pattern Invert
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternInvert

                        Provisionable Default = 0x1

                        Inverts the PRBS generation and checking
                        

                 <B>Notes:</B>
                        Inversion can also be done using the individual Tx and Rx lane inversion bits.  */
      unsigned int   testPatternInvert : 1;    /* 04.D800.5  R/WPD      Provisionable Default = 0x1 */
                     /* Inverts the PRBS generation and checking
                          */
                    /*! \brief 04.D800.4:0 R/WPD Test Pattern Synchronization Threshold [4:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u0.bits_0.testPatternSynchronizationThreshold

                        Provisionable Default = 0x0A

                        PRBS synchronization threshold configuration. If the number of PRBS bit errors is greater than or equal to the threshold within a 4 clock cycle window, the PRBS checker will declare a synchronization error and attempt to resynchronize to the incoming PRBS pattern. Setting this to 0, disables the resynchronization
                        
  */
      unsigned int   testPatternSynchronizationThreshold : 5;    /* 04.D800.4:0  R/WPD      Provisionable Default = 0x0A */
                     /* PRBS synchronization threshold configuration. If the number of PRBS bit errors is greater than or equal to the threshold within a 4 clock cycle window, the PRBS checker will declare a synchronization error and attempt to resynchronize to the incoming PRBS pattern. Setting this to 0, disables the resynchronization
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Debug */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 04.D801.E:C R/W Test Pattern Insert Extra Idles [2:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u1.bits_1.testPatternInsertExtraIdles

                        Default = 0x0

                        Number of extra 4 Idle Octets to insert
                        

                 <B>Notes:</B>
                        Number of extra 4 idle octets to insert in CRPAT and CJPAT generation.  */
      unsigned int   testPatternInsertExtraIdles : 3;    /* 04.D801.E:C  R/W      Default = 0x0 */
                     /* Number of extra 4 Idle Octets to insert
                          */
                    /*! \brief 04.D801.B:8 R/W Test Pattern Check Select [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u1.bits_1.testPatternCheckSelect

                        Default = 0x0

                        1 = Enable PRBS checking on the corresponding XAUI Rx Lane
                        
  */
      unsigned int   testPatternCheckSelect : 4;    /* 04.D801.B:8  R/W      Default = 0x0 */
                     /* 1 = Enable PRBS checking on the corresponding XAUI Rx Lane
                          */
      unsigned int   reserved1 : 4;
                    /*! \brief 04.D801.3:0 R/W Test Pattern Channel Select [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD.u1.bits_1.testPatternChannelSelect

                        Default = 0x0

                        1 = Test Pattern enabled
                        

                 <B>Notes:</B>
                        Used to select which XAUI channel(s) the PRBS is inserted on.   */
      unsigned int   testPatternChannelSelect : 4;    /* 04.D801.3:0  R/W      Default = 0x0 */
                     /* 1 = Test Pattern enabled
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Transmit_xauiRx_VendorDebug_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Test Pattern Error Counter: 04.D810 */
/*                  PHY XS Transmit (XAUI Rx) Test Pattern Error Counter: 04.D810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D810.F:0 SCT Channel 0 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD.u0.bits_0.channel_0TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_0TestPatternErrorCounter : 16;    /* 04.D810.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D811.F:0 SCT Channel 1 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD.u1.bits_1.channel_1TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_1TestPatternErrorCounter : 16;    /* 04.D811.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D812.F:0 SCT Channel 2 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD.u2.bits_2.channel_2TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_2TestPatternErrorCounter : 16;    /* 04.D812.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D813.F:0 SCT Channel 3 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD.u3.bits_3.channel_3TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_3TestPatternErrorCounter : 16;    /* 04.D813.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D814.F:0 SCT Test Pattern Mode 7 Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD.u4.bits_4.testPatternMode_7ErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode #7
                        

                 <B>Notes:</B>
                        This is a saturating 16-bit counter which accumulates the number of test errors during pattern test as specified in test mode #7 Clause 55 test.  */
      unsigned int   testPatternMode_7ErrorCounter : 16;    /* 04.D814.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode #7
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning: 04.E410 */
/*                  PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning: 04.E410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E410.F:E R/WPD XAUI Tx Lane 3 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.xauiTxLane_3Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 3
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_3Serdes : 2;    /* 04.E410.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 3
                          */
                    /*! \brief 04.E410.D:C R/WPD XAUI Tx Lane 2 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.xauiTxLane_2Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 2
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_2Serdes : 2;    /* 04.E410.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 2
                          */
                    /*! \brief 04.E410.B:A R/WPD XAUI Tx Lane 1 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.xauiTxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 1
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_1Serdes : 2;    /* 04.E410.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 1
                          */
                    /*! \brief 04.E410.9:8 R/WPD XAUI Tx Lane 0 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.xauiTxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 0
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_0Serdes : 2;    /* 04.E410.9:8  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 0
                          */
                    /*! \brief 04.E410.7:4 R/WPD XAUI Tx Lane Invert [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.xauiTxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   xauiTxLaneInvert : 4;    /* 04.E410.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.E410.3:2 R/WPD System SGMII Tx SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.systemSgmiiTxSerdes

                        Provisionable Default = 0x0

                        This sets the lane to be used for System SGMII Tx (GbE Rx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                        

                 <B>Notes:</B>
                        This selection is independent of what rate / format the system 10G interface is running at, except if look-aside mode (Bits 4.C441.7:6). In this case, Lane 2 must be used as the SGMII interface. This field can only be changed via provisioning.
                          */
      unsigned int   systemSgmiiTxSerdes : 2;    /* 04.E410.3:2  R/WPD      Provisionable Default = 0x0 */
                     /* This sets the lane to be used for System SGMII Tx (GbE Rx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                          */
                    /*! \brief 04.E410.1 R/WPD System SGMII Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.systemSgmiiTxInvert

                        Provisionable Default = 0x0

                        1 = Invert System SGMII Tx Interface
                        

                 <B>Notes:</B>
                        This inverts the System SGMII Tx interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiTxInvert : 1;    /* 04.E410.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System SGMII Tx Interface
                          */
                    /*! \brief 04.E410.0 R/WPD Reserved Receive Provisioning 1
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u0.bits_0.reservedReceiveProvisioning_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_1 : 1;    /* 04.E410.0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E411.F:C R/WPD Reserved Receive Provisioning 2a [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u1.bits_1.reservedReceiveProvisioning_2a

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_2a : 4;    /* 04.E411.F:C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.E411.B R/WPD System KR Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u1.bits_1.systemKrTxInvert

                        Provisionable Default = 0x0

                        1 = Invert System KR Tx (SERDES2 = KR1)
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   systemKrTxInvert : 1;    /* 04.E411.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System KR Tx (SERDES2 = KR1)
                          */
                    /*! \brief 04.E411.A R/WPD Lookaside Port Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u1.bits_1.lookasidePortTxInvert

                        Provisionable Default = 0x0

                        1 = Invert SERDES0 = KR0 / SGMII0 Tx
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   lookasidePortTxInvert : 1;    /* 04.E411.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert SERDES0 = KR0 / SGMII0 Tx
                          */
                    /*! \brief 04.E411.9 R/WPD Apply SERDES Tx Settings
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u1.bits_1.applySerdesTxSettings

                        Provisionable Default = 0x0

                        1 = Apply SERDES transmit settings
                        

                 <B>Notes:</B>
                        When set to 1, the SERDES transmit settings in 4.E412 through 4.E419 will be propogated to the SERDES core registers. This bit will be cleared after the transfer is completed.  */
      unsigned int   applySerdesTxSettings : 1;    /* 04.E411.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Apply SERDES transmit settings
                          */
                    /*! \brief 04.E411.8:0 R/WPD Reserved Receive Provisioning 2 [8:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u1.bits_1.reservedReceiveProvisioning_2

                        Provisionable Default = 0x000

                        Reserved for future use
                        
                        
  */
      unsigned int   reservedReceiveProvisioning_2 : 9;    /* 04.E411.8:0  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                        
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E412.F:C R/WPD Reserved Rx Provisioning 3 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u2.bits_2.reservedRxProvisioning_3

                        Provisionable Default = 0x0
  */
      unsigned int   reservedRxProvisioning_3 : 4;    /* 04.E412.F:C  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E412.B:8 R/WPD SERDES Lane 0 Post Tap 1 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u2.bits_2.serdesLane_0PostTap_1

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_0PostTap_1 : 4;    /* 04.E412.B:8  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E412.7:5 R/WPD SERDES Lane 0 Pre Tap [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u2.bits_2.serdesLane_0PreTap

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_0PreTap : 3;    /* 04.E412.7:5  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E412.4:0 R/WPD SERDES Lane 0 Main Tap [4:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u2.bits_2.serdesLane_0MainTap

                        Provisionable Default = 0x00
  */
      unsigned int   serdesLane_0MainTap : 5;    /* 04.E412.4:0  R/WPD      Provisionable Default = 0x00 */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E413.F:3 R/WPD Reserved Rx Provisioning 4 [C:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u3.bits_3.reservedRxProvisioning_4

                        Provisionable Default = 0x0000
  */
      unsigned int   reservedRxProvisioning_4 : 13;    /* 04.E413.F:3  R/WPD      Provisionable Default = 0x0000 */
                    /*! \brief 04.E413.2:0 R/WPD SERDES Lane 0 Amplitude [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u3.bits_3.serdesLane_0Amplitude

                        Provisionable Default = 0x0

                        Reserved for internal use
                        
  */
      unsigned int   serdesLane_0Amplitude : 3;    /* 04.E413.2:0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for internal use
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E414.F:C R/WPD Reserved Rx Provisioning 5 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u4.bits_4.reservedRxProvisioning_5

                        Provisionable Default = 0x0
  */
      unsigned int   reservedRxProvisioning_5 : 4;    /* 04.E414.F:C  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E414.B:8 R/WPD SERDES Lane 1 Post Tap 1 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u4.bits_4.serdesLane_1PostTap_1

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_1PostTap_1 : 4;    /* 04.E414.B:8  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E414.7:5 R/WPD SERDES Lane 1 Pre Tap [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u4.bits_4.serdesLane_1PreTap

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_1PreTap : 3;    /* 04.E414.7:5  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E414.4:0 R/WPD SERDES Lane 1 Main Tap [4:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u4.bits_4.serdesLane_1MainTap

                        Provisionable Default = 0x00
  */
      unsigned int   serdesLane_1MainTap : 5;    /* 04.E414.4:0  R/WPD      Provisionable Default = 0x00 */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E415.F:3 R/WPD Reserved Rx Provisioning 6 [C:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u5.bits_5.reservedRxProvisioning_6

                        Provisionable Default = 0x0000
  */
      unsigned int   reservedRxProvisioning_6 : 13;    /* 04.E415.F:3  R/WPD      Provisionable Default = 0x0000 */
                    /*! \brief 04.E415.2:0 R/WPD SERDES Lane 1 Amplitude [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u5.bits_5.serdesLane_1Amplitude

                        Provisionable Default = 0x0

                        Reserved for internal use
                        
  */
      unsigned int   serdesLane_1Amplitude : 3;    /* 04.E415.2:0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for internal use
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E416.F:C R/WPD Reserved Rx Provisioning 7 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u6.bits_6.reservedRxProvisioning_7

                        Provisionable Default = 0x0
  */
      unsigned int   reservedRxProvisioning_7 : 4;    /* 04.E416.F:C  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E416.B:8 R/WPD SERDES Lane 2 Post Tap 1 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u6.bits_6.serdesLane_2PostTap_1

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_2PostTap_1 : 4;    /* 04.E416.B:8  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E416.7:5 R/WPD SERDES Lane 2 Pre Tap [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u6.bits_6.serdesLane_2PreTap

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_2PreTap : 3;    /* 04.E416.7:5  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E416.4:0 R/WPD SERDES Lane 2 Main Tap [4:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u6.bits_6.serdesLane_2MainTap

                        Provisionable Default = 0x00
  */
      unsigned int   serdesLane_2MainTap : 5;    /* 04.E416.4:0  R/WPD      Provisionable Default = 0x00 */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E417.F:3 R/WPD Reserved Rx Provisioning 8 [C:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u7.bits_7.reservedRxProvisioning_8

                        Provisionable Default = 0x0000
  */
      unsigned int   reservedRxProvisioning_8 : 13;    /* 04.E417.F:3  R/WPD      Provisionable Default = 0x0000 */
                    /*! \brief 04.E417.2:0 R/WPD SERDES Lane 2 Amplitude [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u7.bits_7.serdesLane_2Amplitude

                        Provisionable Default = 0x0

                        Reserved for internal use
                        
  */
      unsigned int   serdesLane_2Amplitude : 3;    /* 04.E417.2:0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for internal use
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E418.F:C R/WPD Reserved Rx Provisioning 9 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u8.bits_8.reservedRxProvisioning_9

                        Provisionable Default = 0x0
  */
      unsigned int   reservedRxProvisioning_9 : 4;    /* 04.E418.F:C  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E418.B:8 R/WPD SERDES Lane 3 Post Tap 1 [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u8.bits_8.serdesLane_3PostTap_1

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_3PostTap_1 : 4;    /* 04.E418.B:8  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E418.7:5 R/WPD SERDES Lane 3 Pre Tap [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u8.bits_8.serdesLane_3PreTap

                        Provisionable Default = 0x0
  */
      unsigned int   serdesLane_3PreTap : 3;    /* 04.E418.7:5  R/WPD      Provisionable Default = 0x0 */
                    /*! \brief 04.E418.4:0 R/WPD SERDES Lane 3 Main Tap [4:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u8.bits_8.serdesLane_3MainTap

                        Provisionable Default = 0x00
  */
      unsigned int   serdesLane_3MainTap : 5;    /* 04.E418.4:0  R/WPD      Provisionable Default = 0x00 */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E419.F:3 R/WPD Reserved Rx Provisioning 10 [C:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u9.bits_9.reservedRxProvisioning_10

                        Provisionable Default = 0x0000
  */
      unsigned int   reservedRxProvisioning_10 : 13;    /* 04.E419.F:3  R/WPD      Provisionable Default = 0x0000 */
                    /*! \brief 04.E419.2:0 R/WPD SERDES Lane 3 Amplitude [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD.u9.bits_9.serdesLane_3Amplitude

                        Provisionable Default = 0x0

                        Reserved for internal use
                        
  */
      unsigned int   serdesLane_3Amplitude : 3;    /* 04.E419.2:0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for internal use
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PIF Mailbox Extra: 04.E41D */
/*                  PIF Mailbox Extra: 04.E41D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PIF Mailbox Extra */
  union
  {
    struct
    {
                    /*! \brief 04.E41D.F:0 R/WPD PIF Mailbox Address Register 2 [F:0]
                        AQ_PifMailboxExtra_HHD.u0.bits_0.pifMailboxAddressRegister_2

                        Provisionable Default = 0x0000

                        The data to be written, or that has been read from, the target register.
                        

                 <B>Notes:</B>
                        Specifies the second target register.  */
      unsigned int   pifMailboxAddressRegister_2 : 16;    /* 04.E41D.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* The data to be written, or that has been read from, the target register.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PIF Mailbox Extra */
  union
  {
    struct
    {
                    /*! \brief 04.E41E.F:0 R/WPD PIF Mailbox Data Register 2 [F:0]
                        AQ_PifMailboxExtra_HHD.u1.bits_1.pifMailboxDataRegister_2

                        Provisionable Default = 0x0000

                        The data to be written, or that has been read from, the target register.
                        
  */
      unsigned int   pifMailboxDataRegister_2 : 16;    /* 04.E41E.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* The data to be written, or that has been read from, the target register.
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PIF Mailbox Extra */
  union
  {
    struct
    {
                    /*! \brief 04.E41F.F:8 R/WPD Reserved Rx Provisioning 16 [7:0]
                        AQ_PifMailboxExtra_HHD.u2.bits_2.reservedRxProvisioning_16

                        Provisionable Default = 0x00

                        Reserved for internal use
                        
  */
      unsigned int   reservedRxProvisioning_16 : 8;    /* 04.E41F.F:8  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for internal use
                          */
                    /*! \brief 04.E41F.7:0 R/WPD PIF Mailbox MMD Register 2 [7:0]
                        AQ_PifMailboxExtra_HHD.u2.bits_2.pifMailboxMMD_Register_2

                        Provisionable Default = 0x00

                        MMD (upper 8 bits) specifying the second target register to read or write.
                        

                 <B>Notes:</B>
                        Specifies the second target register.  */
      unsigned int   pifMailboxMMD_Register_2 : 8;    /* 04.E41F.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* MMD (upper 8 bits) specifying the second target register to read or write.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PifMailboxExtra_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) PCS Status: 04.E802 */
/*                  PHY XS Receive (XAUI Tx) PCS Status: 04.E802 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.E802.F:0 SCTL Rx Frame Counter LSW [F:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_HHD.u0.bits_0.rxFrameCounterLSW

                        Default = 0x0000

                        Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   rxFrameCounterLSW : 16;    /* 04.E802.F:0  SCTL      Default = 0x0000 */
                     /* Rx Good Frame Counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.E803.9:0 SCTM Rx Frame Counter MSW [9:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_HHD.u1.bits_1.rxFrameCounterMSW

                        Default = 0x000

                        Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   rxFrameCounterMSW : 10;    /* 04.E803.9:0  SCTM      Default = 0x000 */
                     /* Rx Good Frame Counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.E804.F:0 SCTL Rx Frame Error Counter LSW [F:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_HHD.u2.bits_2.rxFrameErrorCounterLSW

                        Default = 0x0000

                        Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   rxFrameErrorCounterLSW : 16;    /* 04.E804.F:0  SCTL      Default = 0x0000 */
                     /* Rx Bad Frame Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.E805.9:0 SCTM Rx Frame Error Counter MSW [9:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_HHD.u3.bits_3.rxFrameErrorCounterMSW

                        Default = 0x000

                        Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   rxFrameErrorCounterMSW : 10;    /* 04.E805.9:0  SCTM      Default = 0x000 */
                     /* Rx Bad Frame Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PhyXS_Receive_xauiTx_PcsStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Reserved Vendor State: 04.E810 */
/*                  PHY XS Receive (XAUI Tx) Reserved Vendor State: 04.E810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 04.E810.F:0 RO Number of USX Aneg Restarts [F:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorState_HHD.u0.bits_0.numberOfUsxAnegRestarts

                        

                        Number of USX autonegotiations since PHY reset.
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset  */
      unsigned int   numberOfUsxAnegRestarts : 16;    /* 04.E810.F:0  RO       */
                     /* Number of USX autonegotiations since PHY reset.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_Receive_xauiTx_ReservedVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS System Interface Connection Status: 04.E812 */
/*                  PHY XS System Interface Connection Status: 04.E812 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS System Interface Connection Status */
  union
  {
    struct
    {
                    /*! \brief 04.E812.F:E RO System Interface Autoneg Status [1:0]
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.systemInterfaceAutonegStatus

                        

                        0 = N/A
                        1 = Not Complete
                        2 = Complete
                        3 = Reserved
                        

                 <B>Notes:</B>
                        Indicates the completion progress of the system interface's autonegotation.  */
      unsigned int   systemInterfaceAutonegStatus : 2;    /* 04.E812.F:E  RO       */
                     /* 0 = N/A
                        1 = Not Complete
                        2 = Complete
                        3 = Reserved
                          */
                    /*! \brief 04.E812.D RO Rx Link Up
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.rxLinkUp

                        

                        0 = Link Not Up
                        1 = Link Up
                        

                 <B>Notes:</B>
                        Indicates that the system interface has linked and is ready to receive.  */
      unsigned int   rxLinkUp : 1;    /* 04.E812.D  RO       */
                     /* 0 = Link Not Up
                        1 = Link Up
                          */
                    /*! \brief 04.E812.C RO Tx Ready
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.txReady

                        

                        0 = Not Ready
                        1 = Ready
                        

                 <B>Notes:</B>
                        Indicates that the system interface is ready to transmit.  */
      unsigned int   txReady : 1;    /* 04.E812.C  RO       */
                     /* 0 = Not Ready
                        1 = Ready
                          */
                    /*! \brief 04.E812.B:8 RO System Interface Rate [3:0]
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.systemInterfaceRate

                        

                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        6 = Power Down
                        7 - 0xF = Reserved
                        

                 <B>Notes:</B>
                        Indicates the currently active data rate for the system interface.  */
      unsigned int   systemInterfaceRate : 4;    /* 04.E812.B:8  RO       */
                     /* 0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        6 = Power Down
                        7 - 0xF = Reserved
                          */
                    /*! \brief 04.E812.7:3 RO System Interface In Use [4:0]
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.systemInterfaceInUse

                        

                        0 = Backplane KR
                        1 = Backplane KX
                        2 = XFI
                        3 = USXGMII
                        4 = XAUI
                        5 = XAUI Pause Based
                        6 = SGMII
                        7 = RXAUI
                        8 = MAC
                        9 = OFF
                        10 = OCSGMII
                        0xA - 0x1F = Reserved
                        

                 <B>Notes:</B>
                        Indicates the currently active mode for the system interface.  */
      unsigned int   systemInterfaceInUse : 5;    /* 04.E812.7:3  RO       */
                     /* 0 = Backplane KR
                        1 = Backplane KX
                        2 = XFI
                        3 = USXGMII
                        4 = XAUI
                        5 = XAUI Pause Based
                        6 = SGMII
                        7 = RXAUI
                        8 = MAC
                        9 = OFF
                        10 = OCSGMII
                        0xA - 0x1F = Reserved
                          */
                    /*! \brief 04.E812.2:0 RO Reserved Receive State 3 [2:0]
                        AQ_PhyXS_SystemInterfaceConnectionStatus_HHD.u0.bits_0.reservedReceiveState_3

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveState_3 : 3;    /* 04.E812.2:0  RO       */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SystemInterfaceConnectionStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Alarms: 04.EC00 */
/*                  PHY XS Receive (XAUI Tx) Vendor Alarms: 04.EC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.EC00.F LH Reserved XGMII Character Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u0.bits_0.reservedXgmiiCharacterReceivedFromPcs

                        

                        1 = Reserved XGMII character was received from the PCS
                        
  */
      unsigned int   reservedXgmiiCharacterReceivedFromPcs : 1;    /* 04.EC00.F  LH       */
                     /* 1 = Reserved XGMII character was received from the PCS
                          */
                    /*! \brief 04.EC00.E LH Invalid XGMII Character Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u0.bits_0.invalidXgmiiCharacterReceivedFromPcs

                        

                        1 = Invalid XGMII character was received from the PCS
                        
  */
      unsigned int   invalidXgmiiCharacterReceivedFromPcs : 1;    /* 04.EC00.E  LH       */
                     /* 1 = Invalid XGMII character was received from the PCS
                          */
                    /*! \brief 04.EC00.D LH Link status Message Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u0.bits_0.linkStatusMessageReceivedFromPcs

                        

                        1 = Link status message was received from the PCS
                        
  */
      unsigned int   linkStatusMessageReceivedFromPcs : 1;    /* 04.EC00.D  LH       */
                     /* 1 = Link status message was received from the PCS
                          */
      unsigned int   reserved0 : 12;
                    /*! \brief 04.EC00.0 LH MACSEC Ingress Interrupt
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u0.bits_0.macsecIngressInterrupt

                        

                        1 = MACSEC Ingress Interrupt
                        
  */
      unsigned int   macsecIngressInterrupt : 1;    /* 04.EC00.0  LH       */
                     /* 1 = MACSEC Ingress Interrupt
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.EC01.F LH System Interface Rx Link Up
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u1.bits_1.systemInterfaceRxLinkUp

                        

                        1 = System Interface Rx has come up
                        

                 <B>Notes:</B>
                        This bit indicates that the SERDES receive link has come up. This is an alarm bit corresponding to a 1 value of the status bit: 4.E812.D  */
      unsigned int   systemInterfaceRxLinkUp : 1;    /* 04.EC01.F  LH       */
                     /* 1 = System Interface Rx has come up
                          */
                    /*! \brief 04.EC01.E LH System Interface Rx Link Down
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u1.bits_1.systemInterfaceRxLinkDown

                        

                        1 = System Interface Rx has gone down
                        

                 <B>Notes:</B>
                        This bit indicates that the SERDES receive link has gone down. This is an alarm bit corresponding to a 0 value of the status bit: 4.E812.D  */
      unsigned int   systemInterfaceRxLinkDown : 1;    /* 04.EC01.E  LH       */
                     /* 1 = System Interface Rx has gone down
                          */
                    /*! \brief 04.EC01.D LH System Interface Tx Ready
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u1.bits_1.systemInterfaceTxReady

                        

                        1 = System Interface Tx has become ready to transmit
                        

                 <B>Notes:</B>
                        This bit indicates that the SERDES transmit link has become ready to transmit. This is an alarm bit corresponding to a 1 value of the status bit: 4.E812.C  */
      unsigned int   systemInterfaceTxReady : 1;    /* 04.EC01.D  LH       */
                     /* 1 = System Interface Tx has become ready to transmit
                          */
                    /*! \brief 04.EC01.C LH System Interface Tx Not Ready
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u1.bits_1.systemInterfaceTxNotReady

                        

                        1 = System Interface Tx has become not-ready to transmit
                        

                 <B>Notes:</B>
                        This bit indicates that the SERDES transmit link has become not-ready to transmit. This is an alarm bit corresponding to a 0 value of the status bit: 4.E812.C  */
      unsigned int   systemInterfaceTxNotReady : 1;    /* 04.EC01.C  LH       */
                     /* 1 = System Interface Tx has become not-ready to transmit
                          */
                    /*! \brief 04.EC01.B:0 LH Reserved PHY XS Receive Alarms 2 [B:0]
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD.u1.bits_1.reservedPhyXsReceiveAlarms_2

                        

                        Reserved
                        
  */
      unsigned int   reservedPhyXsReceiveAlarms_2 : 12;    /* 04.EC01.B:0  LH       */
                     /* Reserved
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Receive_xauiTx_VendorAlarms_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Interrupt Mask: 04.F400 */
/*                  PHY XS Receive (XAUI Tx) Vendor Interrupt Mask: 04.F400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.F400.F R/WPD Reserved XGMII Character Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u0.bits_0.reservedXgmiiCharacterReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedXgmiiCharacterReceivedFromPcsMask : 1;    /* 04.F400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.F400.E R/WPD Invalid XGMII Character Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u0.bits_0.invalidXgmiiCharacterReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   invalidXgmiiCharacterReceivedFromPcsMask : 1;    /* 04.F400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.F400.D R/WPD Link status Message Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u0.bits_0.linkStatusMessageReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   linkStatusMessageReceivedFromPcsMask : 1;    /* 04.F400.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 12;
                    /*! \brief 04.F400.0 R/WPD MACSEC Ingress Interrupt Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u0.bits_0.macsecIngressInterruptMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   macsecIngressInterruptMask : 1;    /* 04.F400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.F401.F R/WPD System Interface Rx Link Up Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u1.bits_1.systemInterfaceRxLinkUpMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for alarm: 4.EC01.F  */
      unsigned int   systemInterfaceRxLinkUpMask : 1;    /* 04.F401.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.F401.E R/WPD System Interface Rx Link Down Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u1.bits_1.systemInterfaceRxLinkDownMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for alarm: 4.EC01.E  */
      unsigned int   systemInterfaceRxLinkDownMask : 1;    /* 04.F401.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.F401.D R/WPD System Interface Tx Ready Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u1.bits_1.systemInterfaceTxReadyMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for alarm: 4.EC01.D  */
      unsigned int   systemInterfaceTxReadyMask : 1;    /* 04.F401.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.F401.C R/WPD System Interface Tx Not Ready Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u1.bits_1.systemInterfaceTxNotReadyMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for alarm: 4.EC01.C  */
      unsigned int   systemInterfaceTxNotReadyMask : 1;    /* 04.F401.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.F401.B:0 R/WPD Reserved PHY XS Receive Alarms 2 Mask [B:0]
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD.u1.bits_1.reservedPhyXsReceiveAlarms_2Mask

                        Provisionable Default = 0x000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reservedPhyXsReceiveAlarms_2Mask : 12;    /* 04.F401.B:0  R/WPD      Provisionable Default = 0x000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Debug: 04.F800 */
/*                  PHY XS Receive (XAUI Tx) Vendor Debug: 04.F800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.F800.F:D R/W XAUI Tx Error Injection Lane Select [2:0]
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u0.bits_0.xauiTxErrorInjectionLaneSelect

                        Default = 0x0

                        [F:D]
                        0x0 = Lane 0
                        0x1 = Lane 1
                        0x2 = Lane 2
                        0x3 = Lane 3
                        0x4 = All four lanes
                        

                 <B>Notes:</B>
                        This controls which of the 4 Tx XAUI lanes debug error injection occurs on.  */
      unsigned int   xauiTxErrorInjectionLaneSelect : 3;    /* 04.F800.F:D  R/W      Default = 0x0 */
                     /* [F:D]
                        0x0 = Lane 0
                        0x1 = Lane 1
                        0x2 = Lane 2
                        0x3 = Lane 3
                        0x4 = All four lanes
                          */
                    /*! \brief 04.F800.C R/W XAUI Tx Inject Synchronization Error
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u0.bits_0.xauiTxInjectSynchronizationError

                        Default = 0x0

                        1 = Inject a synchronization error
                        

                 <B>Notes:</B>
                        This injects a synchronization error on the lanes selected in F:D  */
      unsigned int   xauiTxInjectSynchronizationError : 1;    /* 04.F800.C  R/W      Default = 0x0 */
                     /* 1 = Inject a synchronization error
                          */
                    /*! \brief 04.F800.B R/W XAUI Tx Inject Alignment Error
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u0.bits_0.xauiTxInjectAlignmentError

                        Default = 0x0

                        1 = Inject an alignment error
                        

                 <B>Notes:</B>
                        This injects an alignment error on the lanes selected in F:D  */
      unsigned int   xauiTxInjectAlignmentError : 1;    /* 04.F800.B  R/W      Default = 0x0 */
                     /* 1 = Inject an alignment error
                          */
                    /*! \brief 04.F800.A R/W XAUI Tx Inject Code Violation
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u0.bits_0.xauiTxInjectCodeViolation

                        Default = 0x0

                        1 = Inject code violation error
                        

                 <B>Notes:</B>
                        This injects the 10B codeword on the lanes selected in F:D  */
      unsigned int   xauiTxInjectCodeViolation : 1;    /* 04.F800.A  R/W      Default = 0x0 */
                     /* 1 = Inject code violation error
                          */
                    /*! \brief 04.F800.9:0 R/W XAUI Tx 10B Violation Codeword [9:0]
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u0.bits_0.xauiTx_10bViolationCodeword

                        Default = 0x000

                        [9:0] = 10B violation codeword to be injected by writing a 1 to Bit A
                        
  */
      unsigned int   xauiTx_10bViolationCodeword : 10;    /* 04.F800.9:0  R/W      Default = 0x000 */
                     /* [9:0] = 10B violation codeword to be injected by writing a 1 to Bit A
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.F802.F R/W PHY XS System Loopback Pass Through
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u2.bits_2.phyXS_SystemLoopbackPassThrough

                        Default = 0x0

                        When set to 1, this bit enables loopback traffic from the PHY XS System Loopback to pass-through towards the network UTP line.
                        When set to 0, the data sent towards the network UTP line will be all IDLEs when in PHY XS System Loopback
                        

                 <B>Notes:</B>
                        This enables traffic to pass through as well as loopback when the PHY XS System Loopback is enabled.  */
      unsigned int   phyXS_SystemLoopbackPassThrough : 1;    /* 04.F802.F  R/W      Default = 0x0 */
                     /* When set to 1, this bit enables loopback traffic from the PHY XS System Loopback to pass-through towards the network UTP line.
                        When set to 0, the data sent towards the network UTP line will be all IDLEs when in PHY XS System Loopback
                          */
                    /*! \brief 04.F802.E R/W PHY XS System Loopback Enable
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u2.bits_2.phyXS_SystemLoopbackEnable

                        Default = 0x0

                        1 = Enable PHY XS System Loopback mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        This bit enables the PHY XS System Loopback from the Tx XAUI Interface after lane alignment to the Rx XAUI interface.  */
      unsigned int   phyXS_SystemLoopbackEnable : 1;    /* 04.F802.E  R/W      Default = 0x0 */
                     /* 1 = Enable PHY XS System Loopback mode
                        0 = Normal operation
                          */
                    /*! \brief 04.F802.D R/W XAUI Tx Local Fault Injection
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u2.bits_2.xauiTxLocalFaultInjection

                        Default = 0x0

                        1 = Inject local fault towards XAUI system side
                        0 = Normal operation
                        
  */
      unsigned int   xauiTxLocalFaultInjection : 1;    /* 04.F802.D  R/W      Default = 0x0 */
                     /* 1 = Inject local fault towards XAUI system side
                        0 = Normal operation
                          */
                    /*! \brief 04.F802.C R/W Reserved 4
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD.u2.bits_2.reserved_4

                        Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_4 : 1;    /* 04.F802.C  R/W      Default = 0x0 */
                     /* Reserved for future use
                          */
      unsigned int   reserved0 : 12;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Receive_xauiTx_VendorDebug_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Vendor Global Interrupt Flags: 04.FC00 */
/*                  PHY XS Vendor Global Interrupt Flags: 04.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 04.FC00.F RO Standard Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.standardAlarms_1Interrupt

                        

                        1 = Interrupt in standard alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   standardAlarms_1Interrupt : 1;    /* 04.FC00.F  RO       */
                     /* 1 = Interrupt in standard alarms 1
                          */
                    /*! \brief 04.FC00.E RO Standard Alarms 2 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.standardAlarms_2Interrupt

                        

                        1 = Interrupt in standard alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   standardAlarms_2Interrupt : 1;    /* 04.FC00.E  RO       */
                     /* 1 = Interrupt in standard alarms 2
                          */
      unsigned int   reserved0 : 3;
                    /*! \brief 04.FC00.A RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 04.FC00.A  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 1
                          */
                    /*! \brief 04.FC00.9 RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 04.FC00.9  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 2
                          */
                    /*! \brief 04.FC00.8 RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 04.FC00.8  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 3
                          */
      unsigned int   reserved1 : 5;
                    /*! \brief 04.FC00.2 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 04.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
                    /*! \brief 04.FC00.1 RO Vendor Specific Rx Alarms 2 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificRxAlarms_2Interrupt : 1;    /* 04.FC00.1  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
      unsigned int   reserved2 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_VendorGlobalInterruptFlags_HHD;

#endif
/*@}*/
/*@}*/
