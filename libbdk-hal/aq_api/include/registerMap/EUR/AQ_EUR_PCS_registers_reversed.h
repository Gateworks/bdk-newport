/*! \file 
*   This file contains the data structures and doxygen comments
*   for the PCS Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup PCS_registers PCS Registers
*   This module contains the data structures and doxygen comments
*   for the PCS Registers block.
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
*   This file contains the c header structures for the registers contained in the PCS Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_PCS_REGS_HEADER
#define AQ_EUR_PCS_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Control 1: 03.0000 */
/*                  PCS Standard Control 1: 03.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 03.0000.F R/WSC Reset
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.reset

                        Default = 0x1

                        1 = PCS reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        Resets the entire PHY.
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PCS registers after this bit is set.  */
      unsigned int   reset : 1;    /* 03.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PCS reset
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.E R/WPD Loopback
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.loopback

                        Provisionable Default = 0x0

                        1 = Enable loopback mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        This enables the PCS DSQ System Loopback.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopback : 1;    /* 03.0000.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable loopback mode
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.D R/WPD Speed Selection LSB
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.speedSelectionLsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionLsb : 1;    /* 03.0000.D  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
                    /*! \brief 03.0000.C R/WPD Reserved_0a
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.reserved0a

                        Provisionable Default = 0x0

                        Reserved bit 12
  */
      unsigned int   reserved0a : 1;    /* 03.0000.C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 12  */
                    /*! \brief 03.0000.B R/WPD Low Power
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.lowPower

                        Provisionable Default = 0x0

                        1 = Low-power mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        A one written to this register causes the PCS to enter low-power mode. If a global chip low-power state is desired, use Bit B in  See PHY XS Standard Control 1 - Address 4.0 should be set.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   lowPower : 1;    /* 03.0000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Low-power mode
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.A R/WPD Clock Stop Enable
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.clockStopEnable

                        Provisionable Default = 0x0

                        1 = The PHY may stop the clock during LPI
                        0 = Clock not stoppable
  */
      unsigned int   clockStopEnable : 1;    /* 03.0000.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = The PHY may stop the clock during LPI
                        0 = Clock not stoppable  */
                    /*! \brief 03.0000.9:7 R/WPD Reserved_0b [9:7]
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.reserved0b

                        Provisionable Default = 0x0

                        Reserved bits [9:7]
  */
      unsigned int   reserved0b : 3;    /* 03.0000.9:7  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bits [9:7]  */
                    /*! \brief 03.0000.6 R/WPD Speed Selection MSB
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.speedSelectionMsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionMsb : 1;    /* 03.0000.6  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
                    /*! \brief 03.0000.5:2 R/WPD 10G Speed Selection [3:0]
                        AQ_PcsStandardControl_1_EUR.u0.bits_0._10gSpeedSelection

                        Provisionable Default = 0x0

                        1 1 x x = Reserved
                        1 0 1 x = Reserved
                        1 0 0 1 = Reserved
                        0 1 0 0 = 100 Gb/s
                        0 0 1 1 = 40 Gb/s
                        0 0 0 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s
                        1 0 0 0 = 5 Gb/s
                        0 1 1 1 = 2.5Gb/s
  */
      unsigned int   _10gSpeedSelection : 4;    /* 03.0000.5:2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 1 x x = Reserved
                        1 0 1 x = Reserved
                        1 0 0 1 = Reserved
                        0 1 0 0 = 100 Gb/s
                        0 0 1 1 = 40 Gb/s
                        0 0 0 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s
                        1 0 0 0 = 5 Gb/s
                        0 1 1 1 = 2.5Gb/s  */
                    /*! \brief 03.0000.1:0 R/WPD Reserved_0c [1:0]
                        AQ_PcsStandardControl_1_EUR.u0.bits_0.reserved0c

                        Provisionable Default = 0x0

                        Reserved bits [1:0]
  */
      unsigned int   reserved0c : 2;    /* 03.0000.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bits [1:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Status 1: 03.0001 */
/*                  PCS Standard Status 1: 03.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Status 1 */
  union
  {
    struct
    {
                    /*! \brief 03.0001.F:C R/W Reserved_01a [F:C]
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.reserved01a

                        Default = 0x0

                        Reserved bits [15:12]
  */
      unsigned int   reserved01a : 4;    /* 03.0001.F:C  R/W      Default = 0x0 */
                     /* Reserved bits [15:12]  */
                    /*! \brief 03.0001.B LH Tx LPI Received
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.txLpiReceived

                        

                        1 = Tx PCS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.4:0.  */
      unsigned int   txLpiReceived : 1;    /* 03.0001.B  LH       */
                     /* 1 = Tx PCS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 03.0001.A LH Rx LPI Received
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.rxLpiReceived

                        

                        1 = Rx PCS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A1.4:0.  */
      unsigned int   rxLpiReceived : 1;    /* 03.0001.A  LH       */
                     /* 1 = Rx PCS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 03.0001.9 RO Tx LPI Indication
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.txLpiIndication

                        

                        1 = Tx PCS is currently receiving LPI
                        0 = Tx PCS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.4:0.  */
      unsigned int   txLpiIndication : 1;    /* 03.0001.9  RO       */
                     /* 1 = Tx PCS is currently receiving LPI
                        0 = Tx PCS is not currently receiving LPI
                          */
                    /*! \brief 03.0001.8 RO Rx LPI Indication
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.rxLpiIndication

                        

                        1 = Rx PCS is currently receiving LPI
                        0 = Rx PCS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A1.4:0.  */
      unsigned int   rxLpiIndication : 1;    /* 03.0001.8  RO       */
                     /* 1 = Rx PCS is currently receiving LPI
                        0 = Rx PCS is not currently receiving LPI
                          */
                    /*! \brief 03.0001.7 RO Fault
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PCS block, This bit is set if either of the two bits 3.8.B or 3.8.A are set.  */
      unsigned int   fault : 1;    /* 03.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
                    /*! \brief 03.0001.6 ROS Clock Stop Capable
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.clockStopCapable

                        Default = 0x0

                        1 = The MAC may stop the clock during LPI
                        0 = Clock not stoppable
  */
      unsigned int   clockStopCapable : 1;    /* 03.0001.6  ROS      Default = 0x0 */
                     /* 1 = The MAC may stop the clock during LPI
                        0 = Clock not stoppable  */
                    /*! \brief 03.0001.5:3 R/W Reserved_01b [5:3]
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.reserved01b

                        Default = 0x0

                        Reserved bits [5:3]
  */
      unsigned int   reserved01b : 3;    /* 03.0001.5:3  R/W      Default = 0x0 */
                     /* Reserved bits [5:3]  */
                    /*! \brief 03.0001.2 LL PCS Receive Link Status
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.pcsReceiveLinkStatus

                        

                        Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                        

                 <B>Notes:</B>
                        This indicates the status of the PCS receive link. This is a latching low version of Bit 3.20.C.  */
      unsigned int   pcsReceiveLinkStatus : 1;    /* 03.0001.2  LL       */
                     /* Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                          */
                    /*! \brief 03.0001.1 ROS Low Power Ability
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PCS supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the XAUI interface supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 03.0001.1  ROS      Default = 0x1 */
                     /* 1 = PCS supports low-power mode
                        0 = no low-power mode supported  */
                    /*! \brief 03.0001.0 R/W Reserved_01c
                        AQ_PcsStandardStatus_1_EUR.u0.bits_0.reserved01c

                        Default = 0x0

                        Reserved bit 0
  */
      unsigned int   reserved01c : 1;    /* 03.0001.0  R/W      Default = 0x0 */
                     /* Reserved bit 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Device Identifier: 03.0002 */
/*                  PCS Standard Device Identifier: 03.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_PcsStandardDeviceIdentifier_EUR.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 03.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.0003.F:0 RO Device ID LSW [F:0]
                        AQ_PcsStandardDeviceIdentifier_EUR.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 03.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDeviceIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Speed Ability: 03.0004 */
/*                  PCS Standard Speed Ability: 03.0004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Speed Ability */
  union
  {
    struct
    {
                    /*! \brief 03.0004.F:8 ROS Reserved_4a [F:8]
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0.reserved4a

                        Default = 0x00

                        Reserved bits [15:8]
  */
      unsigned int   reserved4a : 8;    /* 03.0004.F:8  ROS      Default = 0x00 */
                     /* Reserved bits [15:8]  */
                    /*! \brief 03.0004.7 ROS 5G Capable
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0._5gCapable

                        Default = 0x1

                        1 = PCS is 5 Gb/s capable
                        0 = PCS is not 5 Gb/s capable
  */
      unsigned int   _5gCapable : 1;    /* 03.0004.7  ROS      Default = 0x1 */
                     /* 1 = PCS is 5 Gb/s capable
                        0 = PCS is not 5 Gb/s capable  */
                    /*! \brief 03.0004.6 ROS 2.5G Capable
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0._2_5gCapable

                        Default = 0x1

                        1 = PCS is 2.5 Gb/s capable
                        0 = PCS is not 2.5 Gb/s capable
  */
      unsigned int   _2_5gCapable : 1;    /* 03.0004.6  ROS      Default = 0x1 */
                     /* 1 = PCS is 2.5 Gb/s capable
                        0 = PCS is not 2.5 Gb/s capable  */
                    /*! \brief 03.0004.5:2 ROS Reserved_4b [5:2]
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0.reserved4b

                        Default = 0x0

                        Reserved bits [5:2]
  */
      unsigned int   reserved4b : 4;    /* 03.0004.5:2  ROS      Default = 0x0 */
                     /* Reserved bits [5:2]  */
                    /*! \brief 03.0004.1 ROS 10PASS-TS / 2BASE-TL Capable
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0._10pass_ts__2base_tlCapable

                        Default = 0x0

                        1 = PCS is 10PASS-TS / 2BASE-TL capable
                        0 = PCS is not 10PASS-TS / 2BASE-TL capable
  */
      unsigned int   _10pass_ts__2base_tlCapable : 1;    /* 03.0004.1  ROS      Default = 0x0 */
                     /* 1 = PCS is 10PASS-TS / 2BASE-TL capable
                        0 = PCS is not 10PASS-TS / 2BASE-TL capable  */
                    /*! \brief 03.0004.0 ROS 10G Capable
                        AQ_PcsStandardSpeedAbility_EUR.u0.bits_0._10gCapable

                        Default = 0x1

                        1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable
  */
      unsigned int   _10gCapable : 1;    /* 03.0004.0  ROS      Default = 0x1 */
                     /* 1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardSpeedAbility_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Devices in Package: 03.0005 */
/*                  PCS Standard Devices in Package: 03.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.0005.7 ROS Autonegotiation Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 03.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 03.0005.6 ROS TC Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 03.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 03.0005.5 ROS DTE XS Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                        

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 03.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                          */
                    /*! \brief 03.0005.4 ROS PHY XS Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 03.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 03.0005.3 ROS PCS Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 03.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 03.0005.2 ROS WIS Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 03.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 03.0005.1 ROS PMA Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 03.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 03.0005.0 ROS Clause 22 Registers Present
                        AQ_PcsStandardDevicesInPackage_EUR.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 03.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 03.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PcsStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 03.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 03.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PcsStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 03.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 03.0006.D ROS Clause 22 Extension Present
                        AQ_PcsStandardDevicesInPackage_EUR.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 03.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDevicesInPackage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Control 2: 03.0007 */
/*                  PCS Standard Control 2: 03.0007 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Control 2 */
  union
  {
    struct
    {
                    /*! \brief 03.0007.F:2 R/WPD Reserved_7 [F:2]
                        AQ_PcsStandardControl_2_EUR.u0.bits_0.reserved7

                        Provisionable Default = 0x0000

                        Reserved bits [15:2]
  */
      unsigned int   reserved7 : 14;    /* 03.0007.F:2  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved bits [15:2]  */
                    /*! \brief 03.0007.1:0 R/WPD PCS Device Type [1:0]
                        AQ_PcsStandardControl_2_EUR.u0.bits_0.pcsDeviceType

                        Provisionable Default = 0x3

                        0xC to 0xF = Reserved
                        0xB = 5GBASE-T
                        0xA = 2.5GBASE-T
                        0x4 to 0x9 = Reserved
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R

                 <B>Notes:</B>
                        This defaults to 10GBASE-T  */
      unsigned int   pcsDeviceType : 2;    /* 03.0007.1:0  R/WPD      Provisionable Default = 0x3 */
                     /* 0xC to 0xF = Reserved
                        0xB = 5GBASE-T
                        0xA = 2.5GBASE-T
                        0x4 to 0x9 = Reserved
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Status 2: 03.0008 */
/*                  PCS Standard Status 2: 03.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 03.0008.F:E ROS Device Present [1:0]
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 0x2, as the PCS registers reside here in the PHY.  */
      unsigned int   devicePresent : 2;    /* 03.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
                    /*! \brief 03.0008.D ROS 5GBASE-T capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._5gbase_tCapable

                        Default = 0x1

                        1 = PCS supports 5GBASE-T PCS type
                        0 = PCS does not support 5GBASE-T

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 5GBASE-T
                          */
      unsigned int   _5gbase_tCapable : 1;    /* 03.0008.D  ROS      Default = 0x1 */
                     /* 1 = PCS supports 5GBASE-T PCS type
                        0 = PCS does not support 5GBASE-T  */
                    /*! \brief 03.0008.C ROS 2.5GBASE-T capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._2_5gbase_tCapable

                        Default = 0x1

                        1 = PCS supports 2.5GBASE-T PCS type
                        0 = PCS does not support 2.5GBASE-T

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 2.5GBASE-T
                          */
      unsigned int   _2_5gbase_tCapable : 1;    /* 03.0008.C  ROS      Default = 0x1 */
                     /* 1 = PCS supports 2.5GBASE-T PCS type
                        0 = PCS does not support 2.5GBASE-T  */
                    /*! \brief 03.0008.B LH Transmit Fault
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. This bit is duplicated at 3.CC01.0.   */
      unsigned int   transmitFault : 1;    /* 03.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
                    /*! \brief 03.0008.A LH Receive Fault
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path. This bit is duplicated at 3.EC04.2.  */
      unsigned int   receiveFault : 1;    /* 03.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
                    /*! \brief 03.0008.9:4 R/WPD Reserved_8 [9:4]
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0.reserved8

                        Provisionable Default = 0x00

                        Reserved bits [9:4]
  */
      unsigned int   reserved8 : 6;    /* 03.0008.9:4  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved bits [9:4]  */
                    /*! \brief 03.0008.3 ROS 10GBASE-T capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._10gbase_tCapable

                        Default = 0x1

                        1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_tCapable : 1;    /* 03.0008.3  ROS      Default = 0x1 */
                     /* 1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T  */
                    /*! \brief 03.0008.2 ROS 10GBASE-W capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._10gbase_wCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_wCapable : 1;    /* 03.0008.2  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W  */
                    /*! \brief 03.0008.1 ROS 10GBASE-X capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._10gbase_xCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_xCapable : 1;    /* 03.0008.1  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X  */
                    /*! \brief 03.0008.0 ROS 10GBASE-R capable
                        AQ_PcsStandardStatus_2_EUR.u0.bits_0._10gbase_rCapable

                        Default = 0x1

                        1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R
                        

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_rCapable : 1;    /* 03.0008.0  ROS      Default = 0x1 */
                     /* 1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Package Identifier: 03.000E */
/*                  PCS Standard Package Identifier: 03.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_PcsStandardPackageIdentifier_EUR.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 03.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.000F.F:0 RO Package ID LSW [F:0]
                        AQ_PcsStandardPackageIdentifier_EUR.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 03.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardPackageIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS EEE Capability Register: 03.0014 */
/*                  PCS EEE Capability Register: 03.0014 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS EEE Capability Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.0014.6 ROS 10GBASE-KR EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._10gbase_krEee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability
  */
      unsigned int   _10gbase_krEee : 1;    /* 03.0014.6  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability  */
                    /*! \brief 03.0014.5 ROS 10GBASE-KX4 EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._10gbase_kx4Eee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability
  */
      unsigned int   _10gbase_kx4Eee : 1;    /* 03.0014.5  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability  */
                    /*! \brief 03.0014.4 ROS 1000BASE-KX EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._1000base_kxEee

                        Default = 0x1

                        1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability
  */
      unsigned int   _1000base_kxEee : 1;    /* 03.0014.4  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability  */
                    /*! \brief 03.0014.3 ROS 10GBASE-T EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._10gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability
  */
      unsigned int   _10gbase_tEee : 1;    /* 03.0014.3  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability  */
                    /*! \brief 03.0014.2 ROS 1000BASE-T EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._1000base_tEee

                        Default = 0x1

                        1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability
  */
      unsigned int   _1000base_tEee : 1;    /* 03.0014.2  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability  */
                    /*! \brief 03.0014.1 ROS 100BASE-TX EEE
                        AQ_PcsEeeCapabilityRegister_EUR.u0.bits_0._100base_txEee

                        Default = 0x0

                        1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability
  */
      unsigned int   _100base_txEee : 1;    /* 03.0014.1  ROS      Default = 0x0 */
                     /* 1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability  */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsEeeCapabilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS EEE Capability 2 Register: 03.0015 */
/*                  PCS EEE Capability 2 Register: 03.0015 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS EEE Capability 2 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0015.F:2 R/WPD Reserved_15 [F:2]
                        AQ_PcsEeeCapability_2Register_EUR.u0.bits_0.reserved15

                        Provisionable Default = 0x0000

                        Reserved bits [15:2]
  */
      unsigned int   reserved15 : 14;    /* 03.0015.F:2  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved bits [15:2]  */
                    /*! \brief 03.0015.1 ROS 5GBASE-T EEE
                        AQ_PcsEeeCapability_2Register_EUR.u0.bits_0._5gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 5GBASE-T has EEE capability
                        0 = Do not advertise that the 5GBASE-T has EEE capability
  */
      unsigned int   _5gbase_tEee : 1;    /* 03.0015.1  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 5GBASE-T has EEE capability
                        0 = Do not advertise that the 5GBASE-T has EEE capability  */
                    /*! \brief 03.0015.0 ROS 2.5GBASE-T EEE
                        AQ_PcsEeeCapability_2Register_EUR.u0.bits_0._2_5gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 2.5GBASE-T has EEE capability
                        0 = Do not advertise that the 2.5GBASE-T has EEE capability
  */
      unsigned int   _2_5gbase_tEee : 1;    /* 03.0015.0  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 2.5GBASE-T has EEE capability
                        0 = Do not advertise that the 2.5GBASE-T has EEE capability  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsEeeCapability_2Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS EEE Wake Error Counter: 03.0016 */
/*                  PCS EEE Wake Error Counter: 03.0016 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS EEE Wake Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.0016.F:0 SCT EEE Wake Error Counter [F:0]
                        AQ_PcsEeeWakeErrorCounter_EUR.u0.bits_0.eeeWakeErrorCounter

                        Default = 0x0000

                        EEE wake error counter
                        

                 <B>Notes:</B>
                        This register is a 16-bit saturating clear on read counter. The wake error source is configured with 1E.C4A3.2:0. The default wake error source is from the RPL.  */
      unsigned int   eeeWakeErrorCounter : 16;    /* 03.0016.F:0  SCT      Default = 0x0000 */
                     /* EEE wake error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsEeeWakeErrorCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 17 Register: 03.0017 */
/*                  PCS Reserved 17 Register: 03.0017 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 17 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0017.F:0 R/W Reserved_17 [F:0]
                        AQ_PcsReserved_17Register_EUR.u0.bits_0.reserved17

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved17 : 16;    /* 03.0017.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_17Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 18 Register: 03.0018 */
/*                  PCS Reserved 18 Register: 03.0018 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 18 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0018.F:0 R/W Reserved_18 [F:0]
                        AQ_PcsReserved_18Register_EUR.u0.bits_0.reserved18

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved18 : 16;    /* 03.0018.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_18Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 19 Register: 03.0019 */
/*                  PCS Reserved 19 Register: 03.0019 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 19 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0019.F:0 R/W Reserved_19 [F:0]
                        AQ_PcsReserved_19Register_EUR.u0.bits_0.reserved19

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved19 : 16;    /* 03.0019.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_19Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 1A Register: 03.001A */
/*                  PCS Reserved 1A Register: 03.001A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 1A Register */
  union
  {
    struct
    {
                    /*! \brief 03.001A.F:0 R/W Reserved_1A [F:0]
                        AQ_PcsReserved_1aRegister_EUR.u0.bits_0.reserved1a

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved1a : 16;    /* 03.001A.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_1aRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10G Status: 03.0020 */
/*                  PCS 10G Status: 03.0020 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10G Status */
  union
  {
    struct
    {
                    /*! \brief 03.0020.F:D ROS Reserved_20a [F:D]
                        AQ_Pcs10G_Status_EUR.u0.bits_0.reserved20a

                        Default = 0x0

                        Reserved bits [15:13]
  */
      unsigned int   reserved20a : 3;    /* 03.0020.F:D  ROS      Default = 0x0 */
                     /* Reserved bits [15:13]  */
                    /*! \brief 03.0020.C RO 10G Receive Link Status
                        AQ_Pcs10G_Status_EUR.u0.bits_0._10gReceiveLinkStatus

                        

                        1 = 10G Receive Link Up
                        0 = 10G Receive Link Down
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the 10G Receive Link is functioning properly. This is a non-latching version of bit 3.1.2.  See PHY XS Standard Status 1 - Address 4.1  The Receive Link is up when the Block Lock status is asserted and the High BER is deasserted.)  */
      unsigned int   _10gReceiveLinkStatus : 1;    /* 03.0020.C  RO       */
                     /* 1 = 10G Receive Link Up
                        0 = 10G Receive Link Down
                          */
                    /*! \brief 03.0020.B:4 ROS Reserved_20b [B:4]
                        AQ_Pcs10G_Status_EUR.u0.bits_0.reserved20b

                        Default = 0x00

                        Reserved bits [11:4]
  */
      unsigned int   reserved20b : 8;    /* 03.0020.B:4  ROS      Default = 0x00 */
                     /* Reserved bits [11:4]  */
                    /*! \brief 03.0020.3 ROS 10GBASE-R PRBS9 Pattern Testing Ability
                        AQ_Pcs10G_Status_EUR.u0.bits_0._10gbase_rPrbs9PatternTestingAbility

                        Default = 0x1

                        1 = PCS is able to support PRBS9 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS9 pattern testing on KR Interface
  */
      unsigned int   _10gbase_rPrbs9PatternTestingAbility : 1;    /* 03.0020.3  ROS      Default = 0x1 */
                     /* 1 = PCS is able to support PRBS9 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS9 pattern testing on KR Interface  */
                    /*! \brief 03.0020.2 ROS 10GBASE-R PRBS31 Pattern Testing Ability
                        AQ_Pcs10G_Status_EUR.u0.bits_0._10gbase_rPrbs31PatternTestingAbility

                        Default = 0x1

                        1 = PCS is able to support PRBS31 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS31 pattern testing on KR Interface
  */
      unsigned int   _10gbase_rPrbs31PatternTestingAbility : 1;    /* 03.0020.2  ROS      Default = 0x1 */
                     /* 1 = PCS is able to support PRBS31 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS31 pattern testing on KR Interface  */
                    /*! \brief 03.0020.1 RO 10G High BER
                        AQ_Pcs10G_Status_EUR.u0.bits_0._10gHighBer

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. The interrupt for this bit is at 3.21.E. The status bit for medium BER is found in  See Global Alarms 2: Address 1E.CC01 .  */
      unsigned int   _10gHighBer : 1;    /* 03.0020.1  RO       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
                    /*! \brief 03.0020.0 RO 10G PCS Block Lock
                        AQ_Pcs10G_Status_EUR.u0.bits_0._10gPcsBlockLock

                        

                        1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                        
                        
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10G PCS Framer has acquired frame synchronization and is locked. The interrupt for this bit is at 3.21.F.  */
      unsigned int   _10gPcsBlockLock : 1;    /* 03.0020.0  RO       */
                     /* 1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                        
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10G Status */
  union
  {
    struct
    {
                    /*! \brief 03.0021.F LL PCS Block Lock Latched
                        AQ_Pcs10G_Status_EUR.u1.bits_1.pcsBlockLockLatched

                        

                        1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10G PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.20.0.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   pcsBlockLockLatched : 1;    /* 03.0021.F  LL       */
                     /* 1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                          */
                    /*! \brief 03.0021.E LH High BER Latched
                        AQ_Pcs10G_Status_EUR.u1.bits_1.highBerLatched

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.20.1.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   highBerLatched : 1;    /* 03.0021.E  LH       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
                    /*! \brief 03.0021.D:8 SCT Errored Frame Counter [5:0]
                        AQ_Pcs10G_Status_EUR.u1.bits_1.erroredFrameCounter

                        Default = 0x00

                        A saturating count of the number of times a bad LDPC frame is received.
                        
                        

                 <B>Notes:</B>
                        Clear on read. In 10GBASE-T mode, this is taken from the state machine in Figure 55.14 in the 10GBASE-T specification. In 10GBASE-R mode, this is calculated using controls in   */
      unsigned int   erroredFrameCounter : 6;    /* 03.0021.D:8  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad LDPC frame is received.
                        
                          */
                    /*! \brief 03.0021.7:0 SCT Errored Block Counter [7:0]
                        AQ_Pcs10G_Status_EUR.u1.bits_1.erroredBlockCounter

                        Default = 0x00

                        A saturating count of the number of times a bad 65B block is received.
                        

                 <B>Notes:</B>
                        Clear on read. In 10GBASE-T mode, this is taken from the state machine in Figure 55.16 in the 10GBASE-T specification.  */
      unsigned int   erroredBlockCounter : 8;    /* 03.0021.7:0  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad 65B block is received.
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_Pcs10G_Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R Test Pattern Seed A: 03.0022 */
/*                  PCS 10GBASE-R Test Pattern Seed A: 03.0022 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0022.F:0 R/WPD Test Pattern Seed A Bits 15:0 [F:0]
                        AQ_Pcs10G_base_rTestPatternSeedA_EUR.u0.bits_0.testPatternSeedABits_15_0

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 15:0
  */
      unsigned int   testPatternSeedABits_15_0 : 16;    /* 03.0022.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 15:0  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0023.F:0 R/WPD Test Pattern Seed A Bits 31:16 [1F:10]
                        AQ_Pcs10G_base_rTestPatternSeedA_EUR.u1.bits_1.testPatternSeedABits_31_16

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 31:16
  */
      unsigned int   testPatternSeedABits_31_16 : 16;    /* 03.0023.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 31:16  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0024.F:0 R/WPD Test Pattern Seed A Bits 47:32 [2F:20]
                        AQ_Pcs10G_base_rTestPatternSeedA_EUR.u2.bits_2.testPatternSeedABits_47_32

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 47:32
  */
      unsigned int   testPatternSeedABits_47_32 : 16;    /* 03.0024.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 47:32  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.0025.9:0 R/WPD Test Pattern Seed A Bits 57:48 [39:30]
                        AQ_Pcs10G_base_rTestPatternSeedA_EUR.u3.bits_3.testPatternSeedABits_57_48

                        Provisionable Default = 0x000

                        Test pattern seed A bits 57:48
  */
      unsigned int   testPatternSeedABits_57_48 : 10;    /* 03.0025.9:0  R/WPD      Provisionable Default = 0x000 */
                     /* Test pattern seed A bits 57:48  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_Pcs10G_base_rTestPatternSeedA_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R Test Pattern Seed B: 03.0026 */
/*                  PCS 10GBASE-R Test Pattern Seed B: 03.0026 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0026.F:0 R/WPD Test Pattern Seed B Bits 15:0 [F:0]
                        AQ_Pcs10G_base_rTestPatternSeedB_EUR.u0.bits_0.testPatternSeedBBits_15_0

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 15:0
  */
      unsigned int   testPatternSeedBBits_15_0 : 16;    /* 03.0026.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 15:0  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0027.F:0 R/WPD Test Pattern Seed B Bits 31:16 [1F:10]
                        AQ_Pcs10G_base_rTestPatternSeedB_EUR.u1.bits_1.testPatternSeedBBits_31_16

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 31:16
  */
      unsigned int   testPatternSeedBBits_31_16 : 16;    /* 03.0027.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 31:16  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0028.F:0 R/WPD Test Pattern Seed B Bits 47:32 [2F:20]
                        AQ_Pcs10G_base_rTestPatternSeedB_EUR.u2.bits_2.testPatternSeedBBits_47_32

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 47:32
  */
      unsigned int   testPatternSeedBBits_47_32 : 16;    /* 03.0028.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 47:32  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.0029.9:0 R/WPD Test Pattern Seed B Bits 57:48 [39:30]
                        AQ_Pcs10G_base_rTestPatternSeedB_EUR.u3.bits_3.testPatternSeedBBits_57_48

                        Provisionable Default = 0x000

                        Test pattern seed B bits 57:48
  */
      unsigned int   testPatternSeedBBits_57_48 : 10;    /* 03.0029.9:0  R/WPD      Provisionable Default = 0x000 */
                     /* Test pattern seed B bits 57:48  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_Pcs10G_base_rTestPatternSeedB_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R PCS Test-Pattern Control: 03.002A */
/*                  PCS 10GBASE-R PCS Test-Pattern Control: 03.002A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R PCS Test-Pattern Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.002A.6 R/WPD PRBS9 Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.prbs9TransmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS9 test-pattern mode on the transmit path
                        0 = Disable PRBS9 test-pattern mode on the transmit path
  */
      unsigned int   prbs9TransmitTest_patternEnable : 1;    /* 03.002A.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS9 test-pattern mode on the transmit path
                        0 = Disable PRBS9 test-pattern mode on the transmit path  */
                    /*! \brief 03.002A.5 R/WPD PRBS31 Receive Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.prbs31ReceiveTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS31 test-pattern mode on the receive path
                        0 = Enable PRBS31 test-pattern mode on the receive path
  */
      unsigned int   prbs31ReceiveTest_patternEnable : 1;    /* 03.002A.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS31 test-pattern mode on the receive path
                        0 = Enable PRBS31 test-pattern mode on the receive path  */
                    /*! \brief 03.002A.4 R/WPD PRBS31 Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.prbs31TransmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS31 test-pattern mode on the transmit path
                        0 = Enable PRBS31 test-pattern mode on the transmit path
  */
      unsigned int   prbs31TransmitTest_patternEnable : 1;    /* 03.002A.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS31 test-pattern mode on the transmit path
                        0 = Enable PRBS31 test-pattern mode on the transmit path  */
                    /*! \brief 03.002A.3 R/WPD Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.transmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable transmit test pattern
                        0 = Disable transmit test pattern
  */
      unsigned int   transmitTest_patternEnable : 1;    /* 03.002A.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable transmit test pattern
                        0 = Disable transmit test pattern  */
                    /*! \brief 03.002A.2 R/WPD Receive Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.receiveTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable receive test-pattern testing
                        0 = Disable receive test-pattern testing
  */
      unsigned int   receiveTest_patternEnable : 1;    /* 03.002A.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable receive test-pattern testing
                        0 = Disable receive test-pattern testing  */
                    /*! \brief 03.002A.1 R/WPD Test-Pattern Select
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.test_patternSelect

                        Provisionable Default = 0x0

                        1 = Square wave test pattern
                        0 = Pseudo random test pattern
  */
      unsigned int   test_patternSelect : 1;    /* 03.002A.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Square wave test pattern
                        0 = Pseudo random test pattern  */
                    /*! \brief 03.002A.0 R/WPD Data Pattern Select
                        AQ_Pcs10G_base_rPcsTest_patternControl_EUR.u0.bits_0.dataPatternSelect

                        Provisionable Default = 0x0

                        1 = Zeros data pattern
                        0 = LF data pattern
  */
      unsigned int   dataPatternSelect : 1;    /* 03.002A.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Zeros data pattern
                        0 = LF data pattern  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pcs10G_base_rPcsTest_patternControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R PCS Test-Pattern Error Counter: 03.002B */
/*                  PCS 10GBASE-R PCS Test-Pattern Error Counter: 03.002B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R PCS Test-Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.002B.F:0 R/WPD Test-Pattern Error Counter [F:0]
                        AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR.u0.bits_0.test_patternErrorCounter

                        Provisionable Default = 0x0000

                        Error Counter
  */
      unsigned int   test_patternErrorCounter : 16;    /* 03.002B.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Error Counter  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 2E Register: 03.002E */
/*                  PCS Reserved 2E Register: 03.002E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 2E Register */
  union
  {
    struct
    {
                    /*! \brief 03.002E.F:0 R/W Reserved_2E [F:0]
                        AQ_PcsReserved_2eRegister_EUR.u0.bits_0.reserved2e

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved2e : 16;    /* 03.002E.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_2eRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 2F Register: 03.002F */
/*                  PCS Reserved 2F Register: 03.002F */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 2F Register */
  union
  {
    struct
    {
                    /*! \brief 03.002F.F:0 R/W Reserved_2F [F:0]
                        AQ_PcsReserved_2fRegister_EUR.u0.bits_0.reserved2f

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved2f : 16;    /* 03.002F.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_2fRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 30 Register: 03.0030 */
/*                  PCS Reserved 30 Register: 03.0030 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 30 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0030.F:0 R/W Reserved_30 [F:0]
                        AQ_PcsReserved_30Register_EUR.u0.bits_0.reserved30

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved30 : 16;    /* 03.0030.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_30Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Reserved 31 Register: 03.0031 */
/*                  PCS Reserved 31 Register: 03.0031 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Reserved 31 Register */
  union
  {
    struct
    {
                    /*! \brief 03.0031.F:0 R/W Reserved_31 [F:0]
                        AQ_PcsReserved_31Register_EUR.u0.bits_0.reserved31

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved31 : 16;    /* 03.0031.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReserved_31Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Capability: 03.0708 */
/*                  TimeSync PCS Capability: 03.0708 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.0708.1 RO TimeSync Transmit Path Data Delay
                        AQ_TimesyncPcsCapability_EUR.u0.bits_0.timesyncTransmitPathDataDelay

                        

                        1 = PCS provides information on transmit path data delay in registers 3.1801 through 3.1804
                        0 = PCS does not provide information on transmit path data delay
  */
      unsigned int   timesyncTransmitPathDataDelay : 1;    /* 03.0708.1  RO       */
                     /* 1 = PCS provides information on transmit path data delay in registers 3.1801 through 3.1804
                        0 = PCS does not provide information on transmit path data delay  */
                    /*! \brief 03.0708.0 RO TimeSync Receive Path Data Delay
                        AQ_TimesyncPcsCapability_EUR.u0.bits_0.timesyncReceivePathDataDelay

                        

                        1 = PCS provides information on receive path data delay in registers 3.1805 through 3.1808
                        0 = PCS does not provide information on receive path data delay
  */
      unsigned int   timesyncReceivePathDataDelay : 1;    /* 03.0708.0  RO       */
                     /* 1 = PCS provides information on receive path data delay in registers 3.1805 through 3.1808
                        0 = PCS does not provide information on receive path data delay  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_TimesyncPcsCapability_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Transmit Path Data Delay: 03.0709 */
/*                  TimeSync PCS Transmit Path Data Delay: 03.0709 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.0709.F:0 RO Maximum PCS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_EUR.u0.bits_0.maximumPcsTransmitPathDataDelayLSW

                        

                        LSW of maximum PCS transmit delay in nanoseconds
  */
      unsigned int   maximumPcsTransmitPathDataDelayLSW : 16;    /* 03.0709.F:0  RO       */
                     /* LSW of maximum PCS transmit delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070A.F:0 RO Maximum PCS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_EUR.u1.bits_1.maximumPcsTransmitPathDataDelayMSW

                        

                        MSW of maximum PCS transmit delay in nanoseconds
  */
      unsigned int   maximumPcsTransmitPathDataDelayMSW : 16;    /* 03.070A.F:0  RO       */
                     /* MSW of maximum PCS transmit delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070B.F:0 RO Minimum PCS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_EUR.u2.bits_2.minimumPcsTransmitPathDataDelayLSW

                        

                        LSW of minimum PCS transmit delay in nanoseconds
  */
      unsigned int   minimumPcsTransmitPathDataDelayLSW : 16;    /* 03.070B.F:0  RO       */
                     /* LSW of minimum PCS transmit delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070C.F:0 RO Minimum PCS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_EUR.u3.bits_3.minimumPcsTransmitPathDataDelayMSW

                        

                        MSW of minimum PCS transmit delay in nanoseconds
  */
      unsigned int   minimumPcsTransmitPathDataDelayMSW : 16;    /* 03.070C.F:0  RO       */
                     /* MSW of minimum PCS transmit delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPcsTransmitPathDataDelay_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Receive Path Data Delay: 03.070D */
/*                  TimeSync PCS Receive Path Data Delay: 03.070D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070D.F:0 RO Maximum PCS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_EUR.u0.bits_0.maximumPcsReceivePathDataDelayLSW

                        

                        LSW of maximum PCS receive delay in nanoseconds
  */
      unsigned int   maximumPcsReceivePathDataDelayLSW : 16;    /* 03.070D.F:0  RO       */
                     /* LSW of maximum PCS receive delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070E.F:0 RO Maximum PCS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_EUR.u1.bits_1.maximumPcsReceivePathDataDelayMSW

                        

                        MSW of maximum PCS receive delay in nanoseconds
  */
      unsigned int   maximumPcsReceivePathDataDelayMSW : 16;    /* 03.070E.F:0  RO       */
                     /* MSW of maximum PCS receive delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.070F.F:0 RO Minimum PCS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_EUR.u2.bits_2.minimumPcsReceivePathDataDelayLSW

                        

                        LSW of minimum PCS receive delay in nanoseconds
  */
      unsigned int   minimumPcsReceivePathDataDelayLSW : 16;    /* 03.070F.F:0  RO       */
                     /* LSW of minimum PCS receive delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.0710.F:0 RO Minimum PCS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_EUR.u3.bits_3.minimumPcsReceivePathDataDelayMSW

                        

                        MSW of minimum PCS receive delay in nanoseconds
  */
      unsigned int   minimumPcsReceivePathDataDelayMSW : 16;    /* 03.0710.F:0  RO       */
                     /* MSW of minimum PCS receive delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPcsReceivePathDataDelay_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Provisioning: 03.C400 */
/*                  PCS Transmit Vendor Provisioning: 03.C400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.C400.0 R/WPD PCS Tx Auxilliary Bit Value
                        AQ_PcsTransmitVendorProvisioning_EUR.u0.bits_0.pcsTxAuxilliaryBitValue

                        Provisionable Default = 0x0

                        The value that will be set in the auxilliary bit of the PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is currently undefined in the 802.3an standard.  */
      unsigned int   pcsTxAuxilliaryBitValue : 1;    /* 03.C400.0  R/WPD      Provisionable Default = 0x0 */
                     /* The value that will be set in the auxilliary bit of the PCS transmission frame
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Reserved Vendor Provisioning: 03.C410 */
/*                  PCS Transmit Reserved Vendor Provisioning: 03.C410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C410.F:1 R/WPD Reserved Transmit Provisioning 1 [F:1]
                        AQ_PcsTransmitReservedVendorProvisioning_EUR.u0.bits_0.reservedTransmitProvisioning_1

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_1 : 15;    /* 03.C410.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
                    /*! \brief 03.C410.0 R/WPD PCS IEEE Loopback Passthrough Disable
                        AQ_PcsTransmitReservedVendorProvisioning_EUR.u0.bits_0.pcsIEEE_LoopbackPassthroughDisable

                        Provisionable Default = 0x0

                        1 = Disable data passthrough on IEEE loopback
                        

                 <B>Notes:</B>
                        When set, this bit disables the output of the PHY when IEEE loopback is set.  */
      unsigned int   pcsIEEE_LoopbackPassthroughDisable : 1;    /* 03.C410.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable data passthrough on IEEE loopback
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitReservedVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI Vendor Provisioning: 03.C455 */
/*                  PCS Transmit XFI Vendor Provisioning: 03.C455 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C455.F:0 R/W XFI Test Pattern Seed A Word 0 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u0.bits_0.xfiTestPatternSeedAWord_0

                        Default = 0x0000

                        XFI test pattern seed A bits 15:0
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_0 : 16;    /* 03.C455.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C456.F:0 R/W XFI Test Pattern Seed A Word 1 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u1.bits_1.xfiTestPatternSeedAWord_1

                        Default = 0x0000

                        XFI test pattern seed A bits 31:16
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_1 : 16;    /* 03.C456.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 31:16
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C457.F:0 R/W XFI Test Pattern Seed A Word 2 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u2.bits_2.xfiTestPatternSeedAWord_2

                        Default = 0x0000

                        XFI test pattern seed A bits 47:32
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_2 : 16;    /* 03.C457.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 47:32
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C458.9:0 R/W XFI Test Pattern Seed A Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u3.bits_3.xfiTestPatternSeedAWord_3

                        Default = 0x000

                        XFI test pattern seed A bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_3 : 10;    /* 03.C458.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed A bits 57:48
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C459.F:0 R/W XFI Test Pattern Seed B Word 0 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u4.bits_4.xfiTestPatternSeedBWord_0

                        Default = 0x0000

                        XFI test pattern seed B bits 15:0
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_0 : 16;    /* 03.C459.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 15:0
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C45A.F:0 R/W XFI Test Pattern Seed B Word 1 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u5.bits_5.xfiTestPatternSeedBWord_1

                        Default = 0x0000

                        XFI test pattern seed B bits 31:16
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_1 : 16;    /* 03.C45A.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 31:16
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C45B.F:0 R/W XFI Test Pattern Seed B Word 2 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u6.bits_6.xfiTestPatternSeedBWord_2

                        Default = 0x0000

                        XFI test pattern seed B bits 47:32
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_2 : 16;    /* 03.C45B.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 47:32
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C45C.9:0 R/W XFI Test Pattern Seed B Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_EUR.u7.bits_7.xfiTestPatternSeedBWord_3

                        Default = 0x000

                        XFI test pattern seed B bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_3 : 10;    /* 03.C45C.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed B bits 57:48
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
} AQ_PcsTransmitXfiVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI0 Vendor Provisioning: 03.C460 */
/*                  PCS Transmit XFI0 Vendor Provisioning: 03.C460 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI0 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.C460.1 R/WPD XFI0 PCS Scrambler Disable
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u0.bits_0.xfi0PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi0PcsScramblerDisable : 1;    /* 03.C460.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI0 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C461.9 R/W XFI0 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestSqaureWaveTestDuration

                        Default = 0x0

                        0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                        

                 <B>Notes:</B>
                        10GBASE-R Square Wave Test Duration. Repeating pattern of n ones, followed by n zeros, where n = 6 or 11 (0:n= 6, 1:n=11, default:0)
                          */
      unsigned int   xfi0TestSqaureWaveTestDuration : 1;    /* 03.C461.9  R/W      Default = 0x0 */
                     /* 0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                          */
                    /*! \brief 03.C461.8 R/W XFI0 Test Data Select
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi0TestDataSelect : 1;    /* 03.C461.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C461.7 R/W XFI0 Test Mode Select
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi0TestModeSelect : 1;    /* 03.C461.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C461.6 R/W XFI0 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_9Enable : 1;    /* 03.C461.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C461.5 R/W XFI0 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_31Enable : 1;    /* 03.C461.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C461.4 R/W XFI0 Test Pattern Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPatternEnable : 1;    /* 03.C461.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.C461.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C461.2 R/W XFI0 Inject Single Error
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi0InjectSingleError : 1;    /* 03.C461.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C461.1 R/W XFI0 PCS High BER Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi0PcsHighBerInject : 1;    /* 03.C461.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C461.0 R/W XFI0 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_EUR.u1.bits_1.xfi0PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi0PcsLossOfLockInject : 1;    /* 03.C461.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi0VendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI1 Vendor Provisioning: 03.C470 */
/*                  PCS Transmit XFI1 Vendor Provisioning: 03.C470 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI1 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.C470.1 R/WPD XFI1 PCS Scrambler Disable
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u0.bits_0.xfi1PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi1PcsScramblerDisable : 1;    /* 03.C470.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI1 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C471.9 R/W XFI1 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestSqaureWaveTestDuration

                        Default = 0x0

                        0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                        

                 <B>Notes:</B>
                        10GBASE-R Square Wave Test Duration. Repeating pattern of n ones, followed by n zeros, where n = 6 or 11 (0:n= 6, 1:n=11, default:0)
                          */
      unsigned int   xfi1TestSqaureWaveTestDuration : 1;    /* 03.C471.9  R/W      Default = 0x0 */
                     /* 0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                          */
                    /*! \brief 03.C471.8 R/W XFI1 Test Data Select
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi1TestDataSelect : 1;    /* 03.C471.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C471.7 R/W XFI1 Test Mode Select
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi1TestModeSelect : 1;    /* 03.C471.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C471.6 R/W XFI1 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_9Enable : 1;    /* 03.C471.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C471.5 R/W XFI1 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_31Enable : 1;    /* 03.C471.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C471.4 R/W XFI1 Test Pattern Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi1TestPatternEnable : 1;    /* 03.C471.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.C471.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C471.2 R/W XFI1 Inject Single Error
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi1InjectSingleError : 1;    /* 03.C471.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C471.1 R/W XFI1 PCS High BER Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi1PcsHighBerInject : 1;    /* 03.C471.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C471.0 R/W XFI1 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_EUR.u1.bits_1.xfi1PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi1PcsLossOfLockInject : 1;    /* 03.C471.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi1VendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS SERDES MUX Swap TXRX Register: 03.C4F0 */
/*                  PCS SERDES MUX Swap TXRX Register: 03.C4F0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS SERDES MUX Swap TXRX Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4F0.F:E R/W Serdes Mux Swap TX Lane 3 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapTxLane_3

                        Default = 0x0

                        The lane swap setting for Lane 3, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 3, 1=lane 0, 2=lane 1, 3=lane 2  */
      unsigned int   serdesMuxSwapTxLane_3 : 2;    /* 03.C4F0.F:E  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 3, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.D:C R/W Serdes Mux Swap TX Lane 2 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapTxLane_2

                        Default = 0x0

                        The lane swap setting for Lane 2, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 2, 1=lane 3, 2=lane 0, 3=lane 1  */
      unsigned int   serdesMuxSwapTxLane_2 : 2;    /* 03.C4F0.D:C  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 2, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.B:A R/W Serdes Mux Swap TX Lane 1 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapTxLane_1

                        Default = 0x0

                        The lane swap setting for Lane 1, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 1, 1=lane 2, 2=lane 3, 3=lane 0  */
      unsigned int   serdesMuxSwapTxLane_1 : 2;    /* 03.C4F0.B:A  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 1, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.9:8 R/W Serdes Mux Swap TX Lane 0 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapTxLane_0

                        Default = 0x0

                        The lane swap setting for Lane 0, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 0, 1=lane 1, 2=lane 2, 3=lane 3  */
      unsigned int   serdesMuxSwapTxLane_0 : 2;    /* 03.C4F0.9:8  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 0, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.7:6 R/W Serdes Mux Swap RX Lane 3 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapRxLane_3

                        Default = 0x0

                        The lane swap setting for Lane 3, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 3, 1=lane 0, 2=lane 1, 3=lane 2  */
      unsigned int   serdesMuxSwapRxLane_3 : 2;    /* 03.C4F0.7:6  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 3, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.5:4 R/W Serdes Mux Swap RX Lane 2 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapRxLane_2

                        Default = 0x0

                        The lane swap setting for Lane 2, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 2, 1=lane 3, 2=lane 0, 3=lane 1  */
      unsigned int   serdesMuxSwapRxLane_2 : 2;    /* 03.C4F0.5:4  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 2, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.3:2 R/W Serdes Mux Swap RX Lane 1 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapRxLane_1

                        Default = 0x0

                        The lane swap setting for Lane 1, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 1, 1=lane 2, 2=lane 3, 3=lane 0  */
      unsigned int   serdesMuxSwapRxLane_1 : 2;    /* 03.C4F0.3:2  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 1, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.1:0 R/W Serdes Mux Swap RX Lane 0 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_EUR.u0.bits_0.serdesMuxSwapRxLane_0

                        Default = 0x0

                        The lane swap setting for Lane 0, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 0, 1=lane 1, 2=lane 2, 3=lane 3  */
      unsigned int   serdesMuxSwapRxLane_0 : 2;    /* 03.C4F0.1:0  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 0, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsSerdesMuxSwapTxrxRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit TPL Timestamp Counter: 03.C548 */
/*                  PCS Transmit TPL Timestamp Counter: 03.C548 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit TPL Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C548.F:0 RO TPL Egress Average Timestamp Counter [F:0]
                        AQ_PcsTransmitTplTimestampCounter_EUR.u0.bits_0.tplEgressAverageTimestampCounter

                        

                        TPL Egress Average or Current Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        When configured to perform averaging, it returns the averaging value of the timestamp difference between the insertion and removal points. Otherwise, it returns the current value of the timestamp difference.  */
      unsigned int   tplEgressAverageTimestampCounter : 16;    /* 03.C548.F:0  RO       */
                     /* TPL Egress Average or Current Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit TPL Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C549.F:0 RO TPL Egress Max Timestamp Counter [F:0]
                        AQ_PcsTransmitTplTimestampCounter_EUR.u1.bits_1.tplEgressMaxTimestampCounter

                        

                        TPL Egress Max Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        It returns the maximum value of the timestamp difference between the insertion and removal points.  */
      unsigned int   tplEgressMaxTimestampCounter : 16;    /* 03.C549.F:0  RO       */
                     /* TPL Egress Max Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit TPL Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C54A.F:0 RO TPL Egress Min Timestamp Counter [F:0]
                        AQ_PcsTransmitTplTimestampCounter_EUR.u2.bits_2.tplEgressMinTimestampCounter

                        

                        TPL Egress Min Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        It returns the minimum value of the timestamp difference between the insertion and removal points.  */
      unsigned int   tplEgressMinTimestampCounter : 16;    /* 03.C54A.F:0  RO       */
                     /* TPL Egress Min Timestamp counter
                        VLID="tpl_pif_ts_diff_vld_o"  */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsTransmitTplTimestampCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit TGE Vendor Timestamp Counter: 03.C568 */
/*                  PCS Transmit TGE Vendor Timestamp Counter: 03.C568 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit TGE Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C568.F:0 RO TGE Egress Average Timestamp Counter [F:0]
                        AQ_PcsTransmitTgeVendorTimestampCounter_EUR.u0.bits_0.tgeEgressAverageTimestampCounter

                        

                        TGE Egress Average or Current Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        When configured to perform averaging, it returns the averaging value of the timestamp difference between the insertion and removal points. Otherwise, it returns the current value of the timestamp difference.  */
      unsigned int   tgeEgressAverageTimestampCounter : 16;    /* 03.C568.F:0  RO       */
                     /* TGE Egress Average or Current Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit TGE Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C569.F:0 RO TGE Egress Max Timestamp Counter [F:0]
                        AQ_PcsTransmitTgeVendorTimestampCounter_EUR.u1.bits_1.tgeEgressMaxTimestampCounter

                        

                        TGE Egress Max Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        It returns the maximum value of the timestamp difference between the insertion and removal points.  */
      unsigned int   tgeEgressMaxTimestampCounter : 16;    /* 03.C569.F:0  RO       */
                     /* TGE Egress Max Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit TGE Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C56A.F:0 RO TGE Egress Min Timestamp Counter [F:0]
                        AQ_PcsTransmitTgeVendorTimestampCounter_EUR.u2.bits_2.tgeEgressMinTimestampCounter

                        

                        TGE Egress Min Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"

                 <B>Notes:</B>
                        It returns the minimum value of the timestamp difference between the insertion and removal points.  */
      unsigned int   tgeEgressMinTimestampCounter : 16;    /* 03.C56A.F:0  RO       */
                     /* TGE Egress Min Timestamp counter
                        VLID="tge_pif_ts_diff_vld_o"  */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsTransmitTgeVendorTimestampCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor FCS No Error Frame Counter: 03.C820 */
/*                  PCS Transmit Vendor FCS No Error Frame Counter: 03.C820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C820.F:0 SCTL 10GBASE-T Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR.u0.bits_0._10gbase_tGoodFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterLSW : 16;    /* 03.C820.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C821.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.C821.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor FCS Error Frame Counter: 03.C822 */
/*                  PCS Transmit Vendor FCS Error Frame Counter: 03.C822 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C822.F:0 SCTL 10GBASE-T Error Frame Counter LSW [F:0]
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR.u0.bits_0._10gbase_tErrorFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterLSW : 16;    /* 03.C822.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Bad Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C823.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.C823.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI0 Vendor State: 03.C860 */
/*                  PCS Transmit XFI0 Vendor State: 03.C860 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C860.F:0 SCTL XFI0 Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi0VendorState_EUR.u0.bits_0.xfi0GoodFrameCounterLSW

                        Default = 0x0000

                        XFI0 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterLSW : 16;    /* 03.C860.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_EUR.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.C861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi0VendorState_EUR.u2.bits_2.xfi0BadFrameCounterLSW

                        Default = 0x0000

                        XFI0 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterLSW : 16;    /* 03.C862.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_EUR.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.C863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi0VendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI1 Vendor State: 03.C870 */
/*                  PCS Transmit XFI1 Vendor State: 03.C870 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C870.F:0 SCTL XFI1 Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi1VendorState_EUR.u0.bits_0.xfi1GoodFrameCounterLSW

                        Default = 0x0000

                        XFI1 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterLSW : 16;    /* 03.C870.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_EUR.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.C871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi1VendorState_EUR.u2.bits_2.xfi1BadFrameCounterLSW

                        Default = 0x0000

                        XFI1 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterLSW : 16;    /* 03.C872.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_EUR.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.C873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi1VendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XGS Vendor State: 03.C880 */
/*                  PCS Transmit XGS Vendor State: 03.C880 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C880.7:0 SCT XGS Collision Events Counter 0 [7:0]
                        AQ_PcsTransmitXgsVendorState_EUR.u0.bits_0.xgsCollisionEventsCounter_0

                        Default = 0x00

                        XGS collision events: Byte location from 1 to 64 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 1 to 64 counter  */
      unsigned int   xgsCollisionEventsCounter_0 : 8;    /* 03.C880.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 1 to 64 bytes counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C881.7:0 SCT XGS Collision Events Counter 1 [7:0]
                        AQ_PcsTransmitXgsVendorState_EUR.u1.bits_1.xgsCollisionEventsCounter_1

                        Default = 0x00

                        XGS collision events: Byte location from 65 to 96 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 65 to 96 counter  */
      unsigned int   xgsCollisionEventsCounter_1 : 8;    /* 03.C881.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 65 to 96 bytes counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C882.7:0 SCT XGS Collision Events Counter 2 [7:0]
                        AQ_PcsTransmitXgsVendorState_EUR.u2.bits_2.xgsCollisionEventsCounter_2

                        Default = 0x00

                        XGS collision events: Byte location from 97 to 128 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 97 to 128 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_2 : 8;    /* 03.C882.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 97 to 128 counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C883.7:0 SCT XGS Collision Events Counter 3 [7:0]
                        AQ_PcsTransmitXgsVendorState_EUR.u3.bits_3.xgsCollisionEventsCounter_3

                        Default = 0x00

                        XGS collision events: Byte location from 129 to 192 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 129 to 192 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_3 : 8;    /* 03.C883.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 129 to 192 counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C884.7:0 SCT XGS Collision Events Counter 4 [7:0]
                        AQ_PcsTransmitXgsVendorState_EUR.u4.bits_4.xgsCollisionEventsCounter_4

                        Default = 0x00

                        XGS collision events: Byte location from 193 to 320 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 193 to 320 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_4 : 8;    /* 03.C884.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 193 to 320 counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PcsTransmitXgsVendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit SEC Vendor Timestamp Counter: 03.C980 */
/*                  PCS Transmit SEC Vendor Timestamp Counter: 03.C980 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit SEC Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C980.F:0 RO SEC Ingress Average Timestamp Counter [F:0]
                        AQ_PcsTransmitSecVendorTimestampCounter_EUR.u0.bits_0.secIngressAverageTimestampCounter

                        

                        SEC Ingress Average or Current Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"

                 <B>Notes:</B>
                        When configured to perform averaging, it returns averaging value of timestamp difference between insertion and removal points. Otherwise, it returns current value of the timestamp difference.  */
      unsigned int   secIngressAverageTimestampCounter : 16;    /* 03.C980.F:0  RO       */
                     /* SEC Ingress Average or Current Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit SEC Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C981.F:0 RO SEC Ingress Max Timestamp Counter [F:0]
                        AQ_PcsTransmitSecVendorTimestampCounter_EUR.u1.bits_1.secIngressMaxTimestampCounter

                        

                        SEC Ingress Max Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"

                 <B>Notes:</B>
                        it returns the maximum value of timestamp difference between insertion and removal points.  */
      unsigned int   secIngressMaxTimestampCounter : 16;    /* 03.C981.F:0  RO       */
                     /* SEC Ingress Max Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit SEC Vendor Timestamp Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C982.F:0 RO SEC Ingress Min Timestamp Counter [F:0]
                        AQ_PcsTransmitSecVendorTimestampCounter_EUR.u2.bits_2.secIngressMinTimestampCounter

                        

                        SEC Ingress Min Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"

                 <B>Notes:</B>
                        it returns the minimum value of timestamp difference between insertion and removal points.  */
      unsigned int   secIngressMinTimestampCounter : 16;    /* 03.C982.F:0  RO       */
                     /* SEC Ingress Min Timestamp counter
                        VLID="sec_pif_ing_ts_diff_vld_o"  */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsTransmitSecVendorTimestampCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Ingress SEC L2 Counter: 03.C9A4 */
/*                  PCS Ingress SEC L2 Counter: 03.C9A4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Ingress SEC L2 Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C9A4.F:0 RO SEC Ingress L2 Counter LSW [F:0]
                        AQ_PcsIngressSecL2Counter_EUR.u0.bits_0.secIngressL2CounterLSW

                        

                        SEC Ingress L2 Packet counter LSW
                        VLID="sec_pif_ing_l2_cnt_vlid_i"
                        RDVLIDOUT="sec_ing_l2_cnt_rd_vlid_q"
  */
      unsigned int   secIngressL2CounterLSW : 16;    /* 03.C9A4.F:0  RO       */
                     /* SEC Ingress L2 Packet counter LSW
                        VLID="sec_pif_ing_l2_cnt_vlid_i"
                        RDVLIDOUT="sec_ing_l2_cnt_rd_vlid_q"  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Ingress SEC L2 Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C9A5.F:0 RO SEC Ingress L2 Counter MSW [F:0]
                        AQ_PcsIngressSecL2Counter_EUR.u1.bits_1.secIngressL2CounterMSW

                        

                        SEC Ingress L2 Packet counter MSW
                        NOSYNC="sec_ing_l2_cnt_rd_vlid_q"
                        VLID="sec_ing_l2_cnt_rd_vlid_q"
  */
      unsigned int   secIngressL2CounterMSW : 16;    /* 03.C9A5.F:0  RO       */
                     /* SEC Ingress L2 Packet counter MSW
                        NOSYNC="sec_ing_l2_cnt_rd_vlid_q"
                        VLID="sec_ing_l2_cnt_rd_vlid_q"  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsIngressSecL2Counter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Egress SEC L2 Counter: 03.C9B0 */
/*                  PCS Egress SEC L2 Counter: 03.C9B0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Egress SEC L2 Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C9B0.F:0 RO SEC Egress L2 Counter LSW [F:0]
                        AQ_PcsEgressSecL2Counter_EUR.u0.bits_0.secEgressL2CounterLSW

                        

                        SEC Egress L2 Packet counter LSW
                        VLID="sec_pif_egr_l2_cnt_vlid_i"
                        RDVLIDOUT="sec_egr_l2_cnt_rd_vlid_q"
  */
      unsigned int   secEgressL2CounterLSW : 16;    /* 03.C9B0.F:0  RO       */
                     /* SEC Egress L2 Packet counter LSW
                        VLID="sec_pif_egr_l2_cnt_vlid_i"
                        RDVLIDOUT="sec_egr_l2_cnt_rd_vlid_q"  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Egress SEC L2 Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C9B1.F:0 RO SEC Egress L2 Counter MSW [F:0]
                        AQ_PcsEgressSecL2Counter_EUR.u1.bits_1.secEgressL2CounterMSW

                        

                        SEC Egress L2 Packet counter MSW
                        NOSYNC="sec_egr_l2_cnt_rd_vlid_q"
                        VLID="sec_egr_l2_cnt_rd_vlid_q"
  */
      unsigned int   secEgressL2CounterMSW : 16;    /* 03.C9B1.F:0  RO       */
                     /* SEC Egress L2 Packet counter MSW
                        NOSYNC="sec_egr_l2_cnt_rd_vlid_q"
                        VLID="sec_egr_l2_cnt_rd_vlid_q"  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsEgressSecL2Counter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Alarms: 03.CC00 */
/*                  PCS Transmit Vendor Alarms: 03.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC00.F:4 LH Reserved PCS Transmit Vendor Alarms 1 [F:4]
                        AQ_PcsTransmitVendorAlarms_EUR.u0.bits_0.reservedPcsTransmitVendorAlarms_1

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1 : 12;    /* 03.CC00.F:4  LH       */
                     /* Reserved for future use  */
                    /*! \brief 03.CC00.3 LH TDE Lane Mux FIFO Parity Error
                        AQ_PcsTransmitVendorAlarms_EUR.u0.bits_0.tdeLaneMuxFifoParityError

                        

                        TDE Lane Mux FIFO Parity Error
                        SIGNAL="tde_mux_fifo_par_err"
  */
      unsigned int   tdeLaneMuxFifoParityError : 1;    /* 03.CC00.3  LH       */
                     /* TDE Lane Mux FIFO Parity Error
                        SIGNAL="tde_mux_fifo_par_err"  */
                    /*! \brief 03.CC00.2 LH TDE Lane Mux FIFO Sync Error
                        AQ_PcsTransmitVendorAlarms_EUR.u0.bits_0.tdeLaneMuxFifoSyncError

                        

                        TDE Lane Mux FIFO Sync Error
                        SIGNAL="tde_mux_fifo_syn_err"
  */
      unsigned int   tdeLaneMuxFifoSyncError : 1;    /* 03.CC00.2  LH       */
                     /* TDE Lane Mux FIFO Sync Error
                        SIGNAL="tde_mux_fifo_syn_err"  */
                    /*! \brief 03.CC00.1 LH XAUI Transmit Invalid 512B Block Detected
                        AQ_PcsTransmitVendorAlarms_EUR.u0.bits_0.xauiTransmitInvalid_512bBlockDetected

                        

                        1 = Bad 512B block detected
                        
  */
      unsigned int   xauiTransmitInvalid_512bBlockDetected : 1;    /* 03.CC00.1  LH       */
                     /* 1 = Bad 512B block detected
                          */
                    /*! \brief 03.CC00.0 LH XAUI Transmit Invalid 64B Block Detected
                        AQ_PcsTransmitVendorAlarms_EUR.u0.bits_0.xauiTransmitInvalid_64bBlockDetected

                        

                        1 = Bad 64B block detected
                        
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetected : 1;    /* 03.CC00.0  LH       */
                     /* 1 = Bad 64B block detected
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC01.F:0 LH Reserved PCS Transmit Vendor Alarms 2 [F:0]
                        AQ_PcsTransmitVendorAlarms_EUR.u1.bits_1.reservedPcsTransmitVendorAlarms_2

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_2 : 16;    /* 03.CC01.F:0  LH       */
                     /* Reserved for future use  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC02.F:0 LH Reserved PCS Transmit Vendor Alarms 3 [F:0]
                        AQ_PcsTransmitVendorAlarms_EUR.u2.bits_2.reservedPcsTransmitVendorAlarms_3

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_3 : 16;    /* 03.CC02.F:0  LH       */
                     /* Reserved for future use  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.CC03.D LH XFI1 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.D  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
                    /*! \brief 03.CC03.C LH XFI1 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi1TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.C  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.B LH XFI1 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi1Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi1Transmit_64bEncodeError : 1;    /* 03.CC03.B  LH       */
                     /* 1 = 64B Encode Error
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.CC03.8 LH XFI1 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi1TransmitLofDetected

                        

                        1 = Loss of Frame detected
                        
  */
      unsigned int   xfi1TransmitLofDetected : 1;    /* 03.CC03.8  LH       */
                     /* 1 = Loss of Frame detected
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.CC03.5 LH XFI0 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.5  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
                    /*! \brief 03.CC03.4 LH XFI0 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi0TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.4  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.3 LH XFI0 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi0Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi0Transmit_64bEncodeError : 1;    /* 03.CC03.3  LH       */
                     /* 1 = 64B Encode Error
                          */
      unsigned int   reserved3 : 2;
                    /*! \brief 03.CC03.0 LH XFI0 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_EUR.u3.bits_3.xfi0TransmitLofDetected

                        

                        1 = Loss of frame detected
                        
  */
      unsigned int   xfi0TransmitLofDetected : 1;    /* 03.CC03.0  LH       */
                     /* 1 = Loss of frame detected
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitVendorAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Interrupt Mask: 03.D000 */
/*                  PCS Standard Interrupt Mask: 03.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.D000.B R/WPD Tx LPI Received Mask
                        AQ_PcsStandardInterruptMask_EUR.u0.bits_0.txLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 3.1.B.  */
      unsigned int   txLpiReceivedMask : 1;    /* 03.D000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D000.A R/WPD Rx LPI Received Mask
                        AQ_PcsStandardInterruptMask_EUR.u0.bits_0.rxLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 3.1.A.  */
      unsigned int   rxLpiReceivedMask : 1;    /* 03.D000.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.D000.2 R/WPD PCS Receive Link Status Mask
                        AQ_PcsStandardInterruptMask_EUR.u0.bits_0.pcsReceiveLinkStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 3.1.2. Note this bit also shows up as Bit 3.20.C, but only as a status bit.  */
      unsigned int   pcsReceiveLinkStatusMask : 1;    /* 03.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.D001.B R/WPD Transmit Fault Mask
                        AQ_PcsStandardInterruptMask_EUR.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 03.D001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D001.A R/WPD Receive Fault Mask
                        AQ_PcsStandardInterruptMask_EUR.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 03.D001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D002.F R/WPD 10GBASE-T PCS Block Lock Latched Mask
                        AQ_PcsStandardInterruptMask_EUR.u2.bits_2._10gbase_tPcsBlockLockLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        When set, this bit indicates that 10GBASE-T PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.21.F  */
      unsigned int   _10gbase_tPcsBlockLockLatchedMask : 1;    /* 03.D002.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D002.E R/WPD 10GBASE-T High BER Latched Mask
                        AQ_PcsStandardInterruptMask_EUR.u2.bits_2._10gbase_tHighBerLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.21.E  */
      unsigned int   _10gbase_tHighBerLatchedMask : 1;    /* 03.D002.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 14;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsStandardInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Interrupt Mask: 03.D400 */
/*                  PCS Transmit Vendor Interrupt Mask: 03.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D400.F:4 R/WPD Reserved PCS Transmit Vendor Alarms 1 Mask [F:4]
                        AQ_PcsTransmitVendorInterruptMask_EUR.u0.bits_0.reservedPcsTransmitVendorAlarms_1Mask

                        Provisionable Default = 0x000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1Mask : 12;    /* 03.D400.F:4  R/WPD      Provisionable Default = 0x000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D400.3 R/WPD TDE Lane Mux FIFO Parity Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u0.bits_0.tdeLaneMuxFifoParityErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   tdeLaneMuxFifoParityErrorMask : 1;    /* 03.D400.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D400.2 R/WPD TDE Lane Mux FIFO Sync Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u0.bits_0.tdeLaneMuxFifoSyncErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   tdeLaneMuxFifoSyncErrorMask : 1;    /* 03.D400.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D400.1 R/WPD XAUI Transmit Invalid 512B Block Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u0.bits_0.xauiTransmitInvalid_512bBlockDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiTransmitInvalid_512bBlockDetectedMask : 1;    /* 03.D400.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D400.0 R/WPD XAUI Transmit Invalid 64B Block Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u0.bits_0.xauiTransmitInvalid_64bBlockDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetectedMask : 1;    /* 03.D400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D401.F:0 R/WPD Reserved PCS Transmit Vendor Alarms 2 Mask [F:0]
                        AQ_PcsTransmitVendorInterruptMask_EUR.u1.bits_1.reservedPcsTransmitVendorAlarms_2Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_2Mask : 16;    /* 03.D401.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D402.F:0 R/WPD Reserved PCS Transmit Vendor Alarms 3 Mask [F:0]
                        AQ_PcsTransmitVendorInterruptMask_EUR.u2.bits_2.reservedPcsTransmitVendorAlarms_3Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_3Mask : 16;    /* 03.D402.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.D403.D R/WPD XFI1 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.C R/WPD XFI1 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi1TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.B R/WPD XFI1 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi1TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitEncode_64bErrorMask : 1;    /* 03.D403.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 5;
                    /*! \brief 03.D403.5 R/WPD XFI0 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.4 R/WPD XFI0 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi0TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.3 R/WPD XFI0 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_EUR.u3.bits_3.xfi0TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitEncode_64bErrorMask : 1;    /* 03.D403.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 3;
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitVendorInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Debug: 03.D800 */
/*                  PCS Transmit Vendor Debug: 03.D800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 03.D800.F R/WPD PCS Tx Scrambler Disable
                        AQ_PcsTransmitVendorDebug_EUR.u0.bits_0.pcsTxScramblerDisable

                        Provisionable Default = 0x0

                        1 = Tx Scrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Tx scrambler during regular data transmission (i.e. scrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsTxScramblerDisable : 1;    /* 03.D800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Tx Scrambler Disabled
                        0 = Normal Operation
                          */
                    /*! \brief 03.D800.E R/W PCS Tx Inject CRC Error
                        AQ_PcsTransmitVendorDebug_EUR.u0.bits_0.pcsTxInjectCrcError

                        Default = 0x0

                        1 = Inject CRC Error
                        

                 <B>Notes:</B>
                        Setting this bit injects a CRC error in a single frame.  */
      unsigned int   pcsTxInjectCrcError : 1;    /* 03.D800.E  R/W      Default = 0x0 */
                     /* 1 = Inject CRC Error
                          */
                    /*! \brief 03.D800.D R/W PCS Tx Inject Frame Error
                        AQ_PcsTransmitVendorDebug_EUR.u0.bits_0.pcsTxInjectFrameError

                        Default = 0x0

                        1 = Inject frame error
                        

                 <B>Notes:</B>
                        Setting this bit injects an error at the location contained in Bits C:0 in the next PCS transmission frame.  */
      unsigned int   pcsTxInjectFrameError : 1;    /* 03.D800.D  R/W      Default = 0x0 */
                     /* 1 = Inject frame error
                          */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitVendorDebug_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Provisioning: 03.E400 */
/*                  PCS Receive Vendor Provisioning: 03.E400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.E400.0 R/WPD PCS Rx Error LDPC Frame Enable
                        AQ_PcsReceiveVendorProvisioning_EUR.u0.bits_0.pcsRxErrorLdpcFrameEnable

                        Provisionable Default = 0x1

                        1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                        

                 <B>Notes:</B>
                        Error the entire LDPC frame payload upon uncorrectable LDPC parity or CRC error.  */
      unsigned int   pcsRxErrorLdpcFrameEnable : 1;    /* 03.E400.0  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI0 Provisioning: 03.E460 */
/*                  PCS Receive XFI0 Provisioning: 03.E460 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI0 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E460.1 R/W XFI0 Rx Descrambler Disable
                        AQ_PcsReceiveXfi0Provisioning_EUR.u0.bits_0.xfi0RxDescramblerDisable

                        Default = 0x0

                        1 = XFI0 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi0RxDescramblerDisable : 1;    /* 03.E460.1  R/W      Default = 0x0 */
                     /* 1 = XFI0 Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI0 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E461.8 R/W XFI0 Test Data Source
                        AQ_PcsReceiveXfi0Provisioning_EUR.u1.bits_1.xfi0TestDataSource

                        Default = 0x0

                        XFI0 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                        

                 <B>Notes:</B>
                        This bit determines the source of the data for the pseudo-random test (selected by Bit 7).  */
      unsigned int   xfi0TestDataSource : 1;    /* 03.E461.8  R/W      Default = 0x0 */
                     /* XFI0 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                          */
                    /*! \brief 03.E461.7:5 R/W XFI0 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi0Provisioning_EUR.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random

                 <B>Notes:</B>
                        Note that the source for the pseudo-random test is determined by Bit 8.  */
      unsigned int   xfi0TestModeSelect : 3;    /* 03.E461.7:5  R/W      Default = 0x0 */
                     /* Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random  */
                    /*! \brief 03.E461.4 R/W XFI0 Test Pattern Enable
                        AQ_PcsReceiveXfi0Provisioning_EUR.u1.bits_1.xfi0TestPatternEnable

                        Default = 0x0

                        1 = XFI0 Enable test pattern
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   xfi0TestPatternEnable : 1;    /* 03.E461.4  R/W      Default = 0x0 */
                     /* 1 = XFI0 Enable test pattern
                          */
                    /*! \brief 03.E461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsReceiveXfi0Provisioning_EUR.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = XFI0 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.E461.3  R/W      Default = 0x0 */
                     /* 1 = XFI0 Inject local fault
                          */
      unsigned int   reserved1 : 3;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi0Provisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI1 Provisioning: 03.E470 */
/*                  PCS Receive XFI1 Provisioning: 03.E470 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI1 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E470.1 R/W XFI1 Rx Descrambler Disable
                        AQ_PcsReceiveXfi1Provisioning_EUR.u0.bits_0.xfi1RxDescramblerDisable

                        Default = 0x0

                        1 = XFI1 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi1RxDescramblerDisable : 1;    /* 03.E470.1  R/W      Default = 0x0 */
                     /* 1 = XFI1 Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI1 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E471.8 R/W XFI1 Test Data Source
                        AQ_PcsReceiveXfi1Provisioning_EUR.u1.bits_1.xfi1TestDataSource

                        Default = 0x0

                        XFI1 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                        

                 <B>Notes:</B>
                        This bit determines the source of the data for the pseudo-random test (selected by Bit 7).  */
      unsigned int   xfi1TestDataSource : 1;    /* 03.E471.8  R/W      Default = 0x0 */
                     /* XFI1 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                          */
                    /*! \brief 03.E471.7:5 R/W XFI0 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi1Provisioning_EUR.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random

                 <B>Notes:</B>
                        Note that the source for the pseudo-random test is determined by Bit 8.  */
      unsigned int   xfi0TestModeSelect : 3;    /* 03.E471.7:5  R/W      Default = 0x0 */
                     /* Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random  */
                    /*! \brief 03.E471.4 R/W XFI1 Test Pattern Enable
                        AQ_PcsReceiveXfi1Provisioning_EUR.u1.bits_1.xfi1TestPatternEnable

                        Default = 0x0

                        1 = XFI1 Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   xfi1TestPatternEnable : 1;    /* 03.E471.4  R/W      Default = 0x0 */
                     /* 1 = XFI1 Test pattern enabled
                          */
                    /*! \brief 03.E471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsReceiveXfi1Provisioning_EUR.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = XFI1 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.E471.3  R/W      Default = 0x0 */
                     /* 1 = XFI1 Inject local fault
                          */
      unsigned int   reserved1 : 3;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi1Provisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor State: 03.E800 */
/*                  PCS Receive Vendor State: 03.E800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.E800.0 RO PCS Rx Current Value of Auxilliary Bit
                        AQ_PcsReceiveVendorState_EUR.u0.bits_0.pcsRxCurrentValueOfAuxilliaryBit

                        

                        The current value of the PCS Rx auxilliary bit
                        

                 <B>Notes:</B>
                        This value has a maskable interrupt associated with it in 3.EC00.0.  */
      unsigned int   pcsRxCurrentValueOfAuxilliaryBit : 1;    /* 03.E800.0  RO       */
                     /* The current value of the PCS Rx auxilliary bit
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor CRC-8 Error Counter: 03.E810 */
/*                  PCS Receive Vendor CRC-8 Error Counter: 03.E810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor CRC-8 Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E810.F:0 SCTL CRC-8 Error Counter LSW [F:0]
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR.u0.bits_0.crc_8ErrorCounterLSW

                        Default = 0x0000

                        Lower 16 bits of CRC-8 error counter
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of CRC-8 or RS uncorrectable errors (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   crc_8ErrorCounterLSW : 16;    /* 03.E810.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of CRC-8 error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor CRC-8 Error Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E811.5:0 SCTM CRC-8 Error Counter MSW [15:10]
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR.u1.bits_1.crc_8ErrorCounterMSW

                        Default = 0x00

                        Upper 6 bits of CRC-8 error counter
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of CRC-8 or RS uncorrectable errors (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   crc_8ErrorCounterMSW : 6;    /* 03.E811.5:0  SCTM      Default = 0x00 */
                     /* Upper 6 bits of CRC-8 error counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor FCS No Error Frame Counter: 03.E812 */
/*                  PCS Receive Vendor FCS No Error Frame Counter: 03.E812 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E812.F:0 SCTL 10GBASE-T Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR.u0.bits_0._10gbase_tGoodFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterLSW : 16;    /* 03.E812.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E813.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.E813.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor FCS Error Frame Counter: 03.E814 */
/*                  PCS Receive Vendor FCS Error Frame Counter: 03.E814 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E814.F:0 SCTL 10GBASE-T Error Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR.u0.bits_0._10gbase_tErrorFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterLSW : 16;    /* 03.E814.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Bad Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E815.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.E815.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor RS Corrected Error Frame Counter: 03.E816 */
/*                  PCS Receive Vendor RS Corrected Error Frame Counter: 03.E816 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor RS Corrected Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E816.F:0 SCTL RS Corrected Error Counter LSW [F:0]
                        AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR.u0.bits_0.rsCorrectedErrorCounterLSW

                        Default = 0x0000

                        Lower 16 bits of RS Corrected Frames
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of LDPC frames corrected by RS code.  */
      unsigned int   rsCorrectedErrorCounterLSW : 16;    /* 03.E816.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of RS Corrected Frames
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor RS Corrected Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E817.F:0 SCTM RS Corrected Error Counter MSW [1F:10]
                        AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR.u1.bits_1.rsCorrectedErrorCounterMSW

                        Default = 0x0000

                        Upper 16 bits of RS Corrected Frames

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of LDPC frames corrected by RS code.  */
      unsigned int   rsCorrectedErrorCounterMSW : 16;    /* 03.E817.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of RS Corrected Frames  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Uncorrected Frame Counter: 03.E820 */
/*                  PCS Receive Vendor Uncorrected Frame Counter: 03.E820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Uncorrected Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E820.F:0 SCTL Uncorrected Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR.u0.bits_0.uncorrectedFrameCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC uncorrected frames which the decoder abandoned.
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of uncorrected frames.  */
      unsigned int   uncorrectedFrameCounterLSW : 16;    /* 03.E820.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC uncorrected frames which the decoder abandoned.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Uncorrected Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E821.F:0 SCTM Uncorrected Frame Counter MSW [1F:10]
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR.u1.bits_1.uncorrectedFrameCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC uncorrected frames which the decoder abandoned
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of uncorrected frames.  */
      unsigned int   uncorrectedFrameCounterMSW : 16;    /* 03.E821.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC uncorrected frames which the decoder abandoned
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 1 Iteration Counter: 03.E840 */
/*                  PCS Receive Vendor Corrected Frame 1 Iteration Counter: 03.E840 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 1 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E840.F:0 SCTL Corrected Frames 1 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR.u0.bits_0.correctedFrames_1IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 1 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 1 iteration.  */
      unsigned int   correctedFrames_1IterationCounterLSW : 16;    /* 03.E840.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 1 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 1 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E841.F:0 SCTM Corrected Frames 1 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR.u1.bits_1.correctedFrames_1IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 1 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 1 iteration.  */
      unsigned int   correctedFrames_1IterationCounterMSW : 16;    /* 03.E841.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 1 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 2 Iteration Counter: 03.E842 */
/*                  PCS Receive Vendor Corrected Frame 2 Iteration Counter: 03.E842 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 2 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E842.F:0 SCTL Corrected Frames 2 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR.u0.bits_0.correctedFrames_2IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 2 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 2 iteration.  */
      unsigned int   correctedFrames_2IterationCounterLSW : 16;    /* 03.E842.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 2 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 2 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E843.F:0 SCTM Corrected Frames 2 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR.u1.bits_1.correctedFrames_2IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 2 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 2 iteration.  */
      unsigned int   correctedFrames_2IterationCounterMSW : 16;    /* 03.E843.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 2 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 3 Iteration Counter: 03.E844 */
/*                  PCS Receive Vendor Corrected Frame 3 Iteration Counter: 03.E844 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 3 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E844.F:0 SCTL Corrected Frames 3 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR.u0.bits_0.correctedFrames_3IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 3 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 3 iteration.  */
      unsigned int   correctedFrames_3IterationCounterLSW : 16;    /* 03.E844.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 3 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 3 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E845.F:0 SCTM Corrected Frames 3 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR.u1.bits_1.correctedFrames_3IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 3 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 3 iteration.  */
      unsigned int   correctedFrames_3IterationCounterMSW : 16;    /* 03.E845.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 3 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 4 Iteration Counter: 03.E846 */
/*                  PCS Receive Vendor Corrected Frame 4 Iteration Counter: 03.E846 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 4 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E846.F:0 SCTL Corrected Frames 4 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR.u0.bits_0.correctedFrames_4IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 4 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 4 iteration.  */
      unsigned int   correctedFrames_4IterationCounterLSW : 16;    /* 03.E846.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 4 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 4 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E847.F:0 SCTM Corrected Frames 4 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR.u1.bits_1.correctedFrames_4IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 4 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 4 iteration.  */
      unsigned int   correctedFrames_4IterationCounterMSW : 16;    /* 03.E847.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 4 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 5 Iteration Counter: 03.E848 */
/*                  PCS Receive Vendor Corrected Frame 5 Iteration Counter: 03.E848 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 5 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E848.F:0 SCTL Corrected Frames 5 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR.u0.bits_0.correctedFrames_5IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 5 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 5 iteration.  */
      unsigned int   correctedFrames_5IterationCounterLSW : 16;    /* 03.E848.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 5 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 5 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E849.F:0 SCTM Corrected Frames 5 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR.u1.bits_1.correctedFrames_5IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 5 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 5 iteration.  */
      unsigned int   correctedFrames_5IterationCounterMSW : 16;    /* 03.E849.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 5 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 6 Iteration Counter: 03.E84A */
/*                  PCS Receive Vendor Corrected Frame 6 Iteration Counter: 03.E84A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 6 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E84A.F:0 SCT Corrected Frames 6 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR.u0.bits_0.correctedFrames_6IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 6 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 6 iteration.  */
      unsigned int   correctedFrames_6IterationCounter : 16;    /* 03.E84A.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 6 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 7 Iteration Counter: 03.E84B */
/*                  PCS Receive Vendor Corrected Frame 7 Iteration Counter: 03.E84B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 7 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E84B.F:0 SCT Corrected Frames 7 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR.u0.bits_0.correctedFrames_7IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 7 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 7 iteration.  */
      unsigned int   correctedFrames_7IterationCounter : 16;    /* 03.E84B.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 7 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 8 Iteration Counter: 03.E84C */
/*                  PCS Receive Vendor Corrected Frame 8 Iteration Counter: 03.E84C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 8 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E84C.F:0 SCT Corrected Frames 8 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR.u0.bits_0.correctedFrames_8IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 8 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 8 iteration.  */
      unsigned int   correctedFrames_8IterationCounter : 16;    /* 03.E84C.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 8 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 9 Iteration Counter: 03.E84D */
/*                  PCS Receive Vendor Corrected Frame 9 Iteration Counter: 03.E84D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 9 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E84D.F:0 SCT Corrected Frames 9 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR.u0.bits_0.correctedFrames_9IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 9 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 9 iteration.  */
      unsigned int   correctedFrames_9IterationCounter : 16;    /* 03.E84D.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 9 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 10 Iteration Counter: 03.E84E */
/*                  PCS Receive Vendor Corrected Frame 10 Iteration Counter: 03.E84E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 10 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E84E.F:0 SCT Corrected Frames 10 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR.u0.bits_0.correctedFrames_10IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 10 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 10 iteration.  */
      unsigned int   correctedFrames_10IterationCounter : 16;    /* 03.E84E.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 10 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI0 Vendor State: 03.E860 */
/*                  PCS Receive XFI0 Vendor State: 03.E860 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E860.F:0 SCTL XFI0 Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u0.bits_0.xfi0GoodFrameCounterLSW

                        Default = 0x0000

                        XFI0 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterLSW : 16;    /* 03.E860.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.E861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u2.bits_2.xfi0BadFrameCounterLSW

                        Default = 0x0000

                        XFI0 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterLSW : 16;    /* 03.E862.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.E863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E864.5:0 SCT XFI0 BER Counter [5:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u4.bits_4.xfi0BerCounter

                        Default = 0x00

                        XFI0 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi0BerCounter : 6;    /* 03.E864.5:0  SCT      Default = 0x00 */
                     /* XFI0 BER counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E865.7:0 SCT XFI0 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u5.bits_5.xfi0ErroredBlockCounter

                        Default = 0x00

                        XFI0 errored block counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi0ErroredBlockCounter : 8;    /* 03.E865.7:0  SCT      Default = 0x00 */
                     /* XFI0 errored block counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E866.F:0 SCT XFI0 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi0VendorState_EUR.u6.bits_6.xfi0TestPatternErrorCounter

                        Default = 0x0000

                        XFI0 test pattern error counter
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Error Counter[15:0] saturating clear on read  */
      unsigned int   xfi0TestPatternErrorCounter : 16;    /* 03.E866.F:0  SCT      Default = 0x0000 */
                     /* XFI0 test pattern error counter
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveXfi0VendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI1 Vendor State: 03.E870 */
/*                  PCS Receive XFI1 Vendor State: 03.E870 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E870.F:0 SCTL XFI1 Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u0.bits_0.xfi1GoodFrameCounterLSW

                        Default = 0x0000

                        XFI1 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterLSW : 16;    /* 03.E870.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.E871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u2.bits_2.xfi1BadFrameCounterLSW

                        Default = 0x0000

                        XFI1 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterLSW : 16;    /* 03.E872.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.E873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E874.5:0 SCT XFI1 BER Counter [5:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u4.bits_4.xfi1BerCounter

                        Default = 0x00

                        XFI1 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi1BerCounter : 6;    /* 03.E874.5:0  SCT      Default = 0x00 */
                     /* XFI1 BER counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E875.7:0 SCT XFI1 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u5.bits_5.xfi1ErroredBlockCounter

                        Default = 0x00

                        XFI1 errored block counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi1ErroredBlockCounter : 8;    /* 03.E875.7:0  SCT      Default = 0x00 */
                     /* XFI1 errored block counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E876.F:0 SCT XFI1 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi1VendorState_EUR.u6.bits_6.xfi1TestPatternErrorCounter

                        Default = 0x0000

                        XFI1 test pattern error counter
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Error Counter[15:0] saturating clear on read  */
      unsigned int   xfi1TestPatternErrorCounter : 16;    /* 03.E876.F:0  SCT      Default = 0x0000 */
                     /* XFI1 test pattern error counter
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveXfi1VendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Alarms: 03.EC00 */
/*                  PCS Receive Vendor Alarms: 03.EC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC00.F LH CRC Error
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.crcError

                        

                        1 = Rx CRC or RS Frame error
                        

                 <B>Notes:</B>
                        This bit is set when a CRC-8 or RS uncorrectable error is detected on the receive PCS frame.  */
      unsigned int   crcError : 1;    /* 03.EC00.F  LH       */
                     /* 1 = Rx CRC or RS Frame error
                          */
                    /*! \brief 03.EC00.E LH LDPC Decode Failure
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.ldpcDecodeFailure

                        

                        1 = LDPC decode failure
                        

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailure : 1;    /* 03.EC00.E  LH       */
                     /* 1 = LDPC decode failure
                          */
                    /*! \brief 03.EC00.D LH RPL Link Failure
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.rplLinkFailure

                        

                        1 = RPL Link Failure
                        
                        

                 <B>Notes:</B>
                        This bit is set when a link failure is detected in the RPL.  */
      unsigned int   rplLinkFailure : 1;    /* 03.EC00.D  LH       */
                     /* 1 = RPL Link Failure
                        
                          */
                    /*! \brief 03.EC00.C LH 40G BIP Lock
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0._40gBipLock

                        

                        1 = RPL 40G BIP lock
                        

                 <B>Notes:</B>
                        Indicates the 40G BIP checker has achieved lock to the alignment marker  */
      unsigned int   _40gBipLock : 1;    /* 03.EC00.C  LH       */
                     /* 1 = RPL 40G BIP lock
                          */
                    /*! \brief 03.EC00.B LH Local Fault Detect
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.localFaultDetect

                        

                        1 = RPL local fault detect
                        

                 <B>Notes:</B>
                        Local_Fault Interrupt  */
      unsigned int   localFaultDetect : 1;    /* 03.EC00.B  LH       */
                     /* 1 = RPL local fault detect
                          */
                    /*! \brief 03.EC00.A LH LOF Detect
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.lofDetect

                        

                        1 = RPL LOF detect
                        

                 <B>Notes:</B>
                        LOF Detection Interrupt  */
      unsigned int   lofDetect : 1;    /* 03.EC00.A  LH       */
                     /* 1 = RPL LOF detect
                          */
                    /*! \brief 03.EC00.9 LH Invalid 513B Block
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.invalid_513bBlock

                        

                        1 = Invalid Rx 513B block received in PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is set when an invalid 513B block (but without LDPC frame parity error) has been detected on the received LDPC frame. This is only used in enhanced DSQ128 mode.  */
      unsigned int   invalid_513bBlock : 1;    /* 03.EC00.9  LH       */
                     /* 1 = Invalid Rx 513B block received in PCS transmission frame
                          */
                    /*! \brief 03.EC00.8 LH Invalid 65B Block
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.invalid_65bBlock

                        

                        1 = Invalid Rx 65B block received in PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlock : 1;    /* 03.EC00.8  LH       */
                     /* 1 = Invalid Rx 65B block received in PCS transmission frame
                          */
                    /*! \brief 03.EC00.7 LL EEE Rx LPI Active Off
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.eeeRxLpiActiveOff

                        

                        1 = EEE Rx LPI Active Off
                        
  */
      unsigned int   eeeRxLpiActiveOff : 1;    /* 03.EC00.7  LL       */
                     /* 1 = EEE Rx LPI Active Off
                          */
                    /*! \brief 03.EC00.6 LH EEE Rx LPI Active On
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.eeeRxLpiActiveOn

                        

                        1 = EEE Rx LPI Active On
                        
  */
      unsigned int   eeeRxLpiActiveOn : 1;    /* 03.EC00.6  LH       */
                     /* 1 = EEE Rx LPI Active On
                          */
                    /*! \brief 03.EC00.5 LH LDPC Consecutive Errored Frame Exceeded
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.ldpcConsecutiveErroredFrameExceeded

                        

                        1 = Rx PCS LDPC consecutive errored frame threshold exceeded
                        
                        

                 <B>Notes:</B>
                        Indicates the consecutive LDPC errored frame has exceeded the threshold.
                          */
      unsigned int   ldpcConsecutiveErroredFrameExceeded : 1;    /* 03.EC00.5  LH       */
                     /* 1 = Rx PCS LDPC consecutive errored frame threshold exceeded
                        
                          */
                    /*! \brief 03.EC00.4 LH EEE Rx LPI Alert
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.eeeRxLpiAlert

                        

                        1 = Rx PCS received alert indication
                        
                        

                 <B>Notes:</B>
                        Indicate Rx PCS received alert indication  */
      unsigned int   eeeRxLpiAlert : 1;    /* 03.EC00.4  LH       */
                     /* 1 = Rx PCS received alert indication
                        
                          */
                    /*! \brief 03.EC00.3 LL EEE Rx LPI Received Latched Low
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.eeeRxLpiReceivedLatchedLow

                        

                        1 = Rx LPI has been detected
                        
                        

                 <B>Notes:</B>
                        Indicate LPI ordered-set is detected  */
      unsigned int   eeeRxLpiReceivedLatchedLow : 1;    /* 03.EC00.3  LL       */
                     /* 1 = Rx LPI has been detected
                        
                          */
                    /*! \brief 03.EC00.2 LH EEE Rx LPI Received Latched High
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.eeeRxLpiReceivedLatchedHigh

                        

                        1 = Rx LPI has been detected
                        
                        

                 <B>Notes:</B>
                        Indicate LPI ordered-set is detected  */
      unsigned int   eeeRxLpiReceivedLatchedHigh : 1;    /* 03.EC00.2  LH       */
                     /* 1 = Rx LPI has been detected
                        
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.EC00.0 LRF Change in Auxilliary Bit
                        AQ_PcsReceiveVendorAlarms_EUR.u0.bits_0.changeInAuxilliaryBit

                        

                        1 = Indicates a change in the value of the auxilliary bit
                        

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBit : 1;    /* 03.EC00.0  LRF       */
                     /* 1 = Indicates a change in the value of the auxilliary bit
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.EC04.D LH RDD Lane Mux FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u4.bits_4.rddLaneMuxFifoParityError

                        

                        RDD Lane Mux FIFO Parity Error
                        
  */
      unsigned int   rddLaneMuxFifoParityError : 1;    /* 03.EC04.D  LH       */
                     /* RDD Lane Mux FIFO Parity Error
                          */
                    /*! \brief 03.EC04.C LH RDD Lane Mux FIFO Sync Error
                        AQ_PcsReceiveVendorAlarms_EUR.u4.bits_4.rddLaneMuxFifoSyncError

                        

                        RDD Lane Mux FIFO Sync Error
                        
  */
      unsigned int   rddLaneMuxFifoSyncError : 1;    /* 03.EC04.C  LH       */
                     /* RDD Lane Mux FIFO Sync Error
                          */
      unsigned int   reserved1 : 12;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.EC05.B LH XFI1 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_EUR.u5.bits_5.xfi1Invalid_66bCharacterReceived

                        

                        1 = XFI1 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi1Invalid_66bCharacterReceived : 1;    /* 03.EC05.B  LH       */
                     /* 1 = XFI1 Receive invalid 66B character received
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.EC05.3 LH XFI0 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_EUR.u5.bits_5.xfi0Invalid_66bCharacterReceived

                        

                        1 = XFI0 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi0Invalid_66bCharacterReceived : 1;    /* 03.EC05.3  LH       */
                     /* 1 = XFI0 Receive invalid 66B character received
                          */
      unsigned int   reserved2 : 3;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.EC06.7 LH XFI1 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi1ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI1 receive link
                        

                 <B>Notes:</B>
                        This indicates the status of the XFI1 receive link.  */
      unsigned int   xfi1ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.7  LH       */
                     /* Status of the XFI1 receive link
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.EC06.5 LH XFI1 High BER Status
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi1HighBerStatus

                        

                        1 = XFI1 High BER condition
                        
  */
      unsigned int   xfi1HighBerStatus : 1;    /* 03.EC06.5  LH       */
                     /* 1 = XFI1 High BER condition
                          */
                    /*! \brief 03.EC06.4 LL XFI1 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi1BlockLockStatus

                        

                        1 = XFI1 Block Lock condition
                        
  */
      unsigned int   xfi1BlockLockStatus : 1;    /* 03.EC06.4  LL       */
                     /* 1 = XFI1 Block Lock condition
                          */
                    /*! \brief 03.EC06.3 LH XFI0 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi0ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI0 receive link
                        

                 <B>Notes:</B>
                        This indicates the status of the XFI0 receive link.  */
      unsigned int   xfi0ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.3  LH       */
                     /* Status of the XFI0 receive link
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.EC06.1 LH XFI0 High BER Status
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi0HighBerStatus

                        

                        1 = XFI0 High BER condition
                        
  */
      unsigned int   xfi0HighBerStatus : 1;    /* 03.EC06.1  LH       */
                     /* 1 = XFI0 High BER condition
                          */
                    /*! \brief 03.EC06.0 LL XFI0 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_EUR.u6.bits_6.xfi0BlockLockStatus

                        

                        1 = XFI0 Block Lock condition
                        
  */
      unsigned int   xfi0BlockLockStatus : 1;    /* 03.EC06.0  LL       */
                     /* 1 = XFI0 Block Lock condition
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.EC09.D LH PTP Ingress Packet Gap FIFO Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketGapFifoError

                        

                        1 = PTP Ingress packet gap FIFO error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet gap FIFO has detected FIFO error  */
      unsigned int   ptpIngressPacketGapFifoError : 1;    /* 03.EC09.D  LH       */
                     /* 1 = PTP Ingress packet gap FIFO error
                          */
                    /*! \brief 03.EC09.C LH PTP Ingress Packet Gap FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketGapFifoParityError

                        

                        1 = PTP Ingress packet gap FIFO parity error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet gap FIFO has detected parity error  */
      unsigned int   ptpIngressPacketGapFifoParityError : 1;    /* 03.EC09.C  LH       */
                     /* 1 = PTP Ingress packet gap FIFO parity error
                          */
                    /*! \brief 03.EC09.B LH PTP Ingress Packet Ready FIFO Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketReadyFifoError

                        

                        1 = PTP Ingress packet ready FIFO error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet ready FIFO has detected FIFO error  */
      unsigned int   ptpIngressPacketReadyFifoError : 1;    /* 03.EC09.B  LH       */
                     /* 1 = PTP Ingress packet ready FIFO error
                          */
                    /*! \brief 03.EC09.A LH PTP Ingress Packet Ready FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketReadyFifoParityError

                        

                        1 = PTP Ingress packet ready FIFO parity error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet ready FIFO has detected parity error  */
      unsigned int   ptpIngressPacketReadyFifoParityError : 1;    /* 03.EC09.A  LH       */
                     /* 1 = PTP Ingress packet ready FIFO parity error
                          */
                    /*! \brief 03.EC09.9 LH PTP Ingress Packet Remove Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketRemoveError

                        

                        1 = PTP Ingress packet remove error
                        

                 <B>Notes:</B>
                        Asserted when the packet length is too long for the UDP checksum to be updated during removal of the timestamp appended at the end of packet. When this happens, the UDP checksum will be set to all-zeroes.  */
      unsigned int   ptpIngressPacketRemoveError : 1;    /* 03.EC09.9  LH       */
                     /* 1 = PTP Ingress packet remove error
                          */
                    /*! \brief 03.EC09.8 LH PTP Ingress Packet Received
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketReceived

                        

                        1 = PTP Ingress packet received
                        

                 <B>Notes:</B>
                        Asserted when a valid PTP packet has been received. This can be used as the valid signal for the received PTP packet information.  */
      unsigned int   ptpIngressPacketReceived : 1;    /* 03.EC09.8  LH       */
                     /* 1 = PTP Ingress packet received
                          */
                    /*! \brief 03.EC09.7 LH PTP Ingress Packet Pipeline FIFO Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketPipelineFifoError

                        

                        1 = PTP Ingress packet pipeline FIFO error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet buffer has detected parity error  */
      unsigned int   ptpIngressPacketPipelineFifoError : 1;    /* 03.EC09.7  LH       */
                     /* 1 = PTP Ingress packet pipeline FIFO error detected
                          */
                    /*! \brief 03.EC09.6 LH PTP Ingress Packet Pipeline Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketPipelineParityError

                        

                        1 = PTP Ingress packet pipeline parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP timestamp buffer has detected parity error  */
      unsigned int   ptpIngressPacketPipelineParityError : 1;    /* 03.EC09.6  LH       */
                     /* 1 = PTP Ingress packet pipeline parity error detected
                          */
                    /*! \brief 03.EC09.5 LH PTP Ingress Time Stamp Buffer Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressTimeStampBufferParityError

                        

                        1 = PTP Ingress time stamp buffer parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet pipeline has detected parity error  */
      unsigned int   ptpIngressTimeStampBufferParityError : 1;    /* 03.EC09.5  LH       */
                     /* 1 = PTP Ingress time stamp buffer parity error detected
                          */
                    /*! \brief 03.EC09.4 LH PTP Ingress Packet Buffer Parity Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketBufferParityError

                        

                        1 = PTP Ingress packet buffer parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet pipeline has detected FIFO error  */
      unsigned int   ptpIngressPacketBufferParityError : 1;    /* 03.EC09.4  LH       */
                     /* 1 = PTP Ingress packet buffer parity error detected
                          */
                    /*! \brief 03.EC09.3 LH PTP Ingress Packet Correction Field Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketCorrectionFieldError

                        

                        1 = PTP Ingress packet correction field error
                        

                 <B>Notes:</B>
                        Asserted when the packet length is too long for the Correction field to be updated due to the ingress timestamp appended at the end of packet. This shall not happen for IEEE1588v2 compliant packets. But when this happens, the Correction field will not be changed.  */
      unsigned int   ptpIngressPacketCorrectionFieldError : 1;    /* 03.EC09.3  LH       */
                     /* 1 = PTP Ingress packet correction field error
                          */
                    /*! \brief 03.EC09.2 LH PTP Ingress Packet Buffer Overflow Error
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketBufferOverflowError

                        

                        1 = PTP Ingress packet buffer overflow error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet has not been captured because the buffer was full  */
      unsigned int   ptpIngressPacketBufferOverflowError : 1;    /* 03.EC09.2  LH       */
                     /* 1 = PTP Ingress packet buffer overflow error detected
                          */
                    /*! \brief 03.EC09.1 RO PTP Ingress Time Stamp Ready
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressTimeStampReady

                        

                        1 = PTP Ingress packet time stamp ready
                        

                 <B>Notes:</B>
                        Asserted when PTP packet timestamp has captured. It will be cleared when the timestamp buffer is empty
                          */
      unsigned int   ptpIngressTimeStampReady : 1;    /* 03.EC09.1  RO       */
                     /* 1 = PTP Ingress packet time stamp ready
                          */
                    /*! \brief 03.EC09.0 RO PTP Ingress Packet Ready
                        AQ_PcsReceiveVendorAlarms_EUR.u9.bits_9.ptpIngressPacketReady

                        

                        1 = PTP Ingress packet ready
                        

                 <B>Notes:</B>
                        Asserted when PTP packet has captured. It will be cleared when the buffer is empty  */
      unsigned int   ptpIngressPacketReady : 1;    /* 03.EC09.0  RO       */
                     /* 1 = PTP Ingress packet ready
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_PcsReceiveVendorAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Interrupt Mask: 03.F400 */
/*                  PCS Receive Vendor Interrupt Mask: 03.F400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F400.F R/WPD CRC Error Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.crcErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a CRC-8 or RS uncorrectable error is detected on the receive PCS frame.  */
      unsigned int   crcErrorMask : 1;    /* 03.F400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.E R/WPD LDPC Decode Failure Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.ldpcDecodeFailureMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailureMask : 1;    /* 03.F400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.D R/WPD RPL Link Failure Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.rplLinkFailureMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   rplLinkFailureMask : 1;    /* 03.F400.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.C R/WPD 40G BIP Lock Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0._40gBipLockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   _40gBipLockMask : 1;    /* 03.F400.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.B R/WPD Local Fault Detect Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.localFaultDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   localFaultDetectMask : 1;    /* 03.F400.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.A R/WPD LOF Detect Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.lofDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   lofDetectMask : 1;    /* 03.F400.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.9 R/WPD Invalid 513B Block Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.invalid_513bBlockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when an invalid 513B block (but without LDPC frame parity error) has been detected on the received LDPC frame. This is only used in enhanced DSQ128 mode.  */
      unsigned int   invalid_513bBlockMask : 1;    /* 03.F400.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.8 R/WPD Invalid 65B Block Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.invalid_65bBlockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlockMask : 1;    /* 03.F400.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.7 R/WPD EEE Rx LPI Active Off Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.eeeRxLpiActiveOffMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiActiveOffMask : 1;    /* 03.F400.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.6 R/WPD EEE Rx LPI Active On Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.eeeRxLpiActiveOnMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiActiveOnMask : 1;    /* 03.F400.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.5 R/WPD LDPC Consecutive Errored Frame Exceeded Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.ldpcConsecutiveErroredFrameExceededMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   ldpcConsecutiveErroredFrameExceededMask : 1;    /* 03.F400.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.4 R/WPD EEE Rx LPI Alert Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.eeeRxLpiAlertMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiAlertMask : 1;    /* 03.F400.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.3 R/WPD EEE Rx LPI Received Latched Low Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.eeeRxLpiReceivedLatchedLowMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiReceivedLatchedLowMask : 1;    /* 03.F400.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.2 R/WPD EEE Rx LPI Received Latched High Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.eeeRxLpiReceivedLatchedHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiReceivedLatchedHighMask : 1;    /* 03.F400.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.F400.0 R/WPD Change in Auxilliary Bit Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u0.bits_0.changeInAuxilliaryBitMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBitMask : 1;    /* 03.F400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.F404.D R/WPD RDD Lane Mux FIFO Parity Error
                        AQ_PcsReceiveVendorInterruptMask_EUR.u4.bits_4.rddLaneMuxFifoParityError

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   rddLaneMuxFifoParityError : 1;    /* 03.F404.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F404.C R/WPD RDD Lane Mux FIFO Sync Error
                        AQ_PcsReceiveVendorInterruptMask_EUR.u4.bits_4.rddLaneMuxFifoSyncError

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   rddLaneMuxFifoSyncError : 1;    /* 03.F404.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 12;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.F405.B R/WPD XFI1 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u5.bits_5.xfi1Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.F405.3 R/WPD XFI0 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u5.bits_5.xfi0Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 3;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.F406.7 R/WPD XFI1 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi1ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.F406.5 R/WPD XFI1 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi1HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1HighBerStatusMask : 1;    /* 03.F406.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.4 R/WPD XFI1 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi1BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1BlockLockStatusMask : 1;    /* 03.F406.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.3 R/WPD XFI0 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi0ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.F406.1 R/WPD XFI0 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi0HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0HighBerStatusMask : 1;    /* 03.F406.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.0 R/WPD XFI0 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_EUR.u6.bits_6.xfi0BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0BlockLockStatusMask : 1;    /* 03.F406.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveVendorInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Debug: 03.F800 */
/*                  PCS Receive Vendor Debug: 03.F800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 03.F800.F R/WPD PCS Rx Descrambler Disable
                        AQ_PcsReceiveVendorDebug_EUR.u0.bits_0.pcsRxDescramblerDisable

                        Provisionable Default = 0x0

                        1 = Rx Descrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Rx descrambler during regular data transmission (i.e. descrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsRxDescramblerDisable : 1;    /* 03.F800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Rx Descrambler Disabled
                        0 = Normal Operation
                          */
      unsigned int   reserved0 : 12;
                    /*! \brief 03.F800.2 R/WPD PCS Network Loopback Merge
                        AQ_PcsReceiveVendorDebug_EUR.u0.bits_0.pcsNetworkLoopbackMerge

                        Provisionable Default = 0x1

                        When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged.
                        

                 <B>Notes:</B>
                        If the MAC sends data, it will take priority over the PCS Network Loopback data. The loopback data will be dropped.  */
      unsigned int   pcsNetworkLoopbackMerge : 1;    /* 03.F800.2  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged.
                          */
                    /*! \brief 03.F800.1 R/WPD PCS Network Loopback Pass Through
                        AQ_PcsReceiveVendorDebug_EUR.u0.bits_0.pcsNetworkLoopbackPassThrough

                        Provisionable Default = 0x1

                        When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                        

                 <B>Notes:</B>
                        This enables traffic to pass through as well as loopback when the PCS Network Loopback is enabled.  */
      unsigned int   pcsNetworkLoopbackPassThrough : 1;    /* 03.F800.1  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                          */
                    /*! \brief 03.F800.0 R/WPD PCS Network Loopback
                        AQ_PcsReceiveVendorDebug_EUR.u0.bits_0.pcsNetworkLoopback

                        Provisionable Default = 0x0

                        When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line.
                        
  */
      unsigned int   pcsNetworkLoopback : 1;    /* 03.F800.0  R/WPD      Provisionable Default = 0x0 */
                     /* When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorDebug_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Vendor Global Interrupt Flags: 03.FC00 */
/*                  PCS Vendor Global Interrupt Flags: 03.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 03.FC00.F RO Standard Alarm 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarm_1Interrupt

                        

                        1 = Interrupt in standard alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Status 1 - Address 4.1 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 2 - Address 4.A001 ).  */
      unsigned int   standardAlarm_1Interrupt : 1;    /* 03.FC00.F  RO       */
                     /* 1 = Interrupt in standard alarms 1
                          */
                    /*! \brief 03.FC00.E RO Standard Alarm 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarm_2Interrupt

                        

                        1 = Interrupt in standard alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Vendor Devices in Package - Address 4.8 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 8 - Address 4.A008 ).  */
      unsigned int   standardAlarm_2Interrupt : 1;    /* 03.FC00.E  RO       */
                     /* 1 = Interrupt in standard alarms 2
                          */
                    /*! \brief 03.FC00.D RO Standard Alarm 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarm_3Interrupt

                        

                        1 = Interrupt in standard alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS 10GBASE-T Status 2 - Address 3.21 ) and the corresponding mask register ( See PCS Standard Interrupt Mask 1 - Address 3.E021 ).  */
      unsigned int   standardAlarm_3Interrupt : 1;    /* 03.FC00.D  RO       */
                     /* 1 = Interrupt in standard alarms 3
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.FC00.B RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Vendor Alarms 3: Address 1E.CC02 ) and the corresponding mask register ( See PHY XS Transmit (XAUI Rx) Vendor LASI Interrupt Mask 3: Address 4.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 03.FC00.B  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 1
                          */
                    /*! \brief 03.FC00.A RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor XAUI Receive Alarms 1 - Address 4.B000 ) and the corresponding mask register ( See PCS Vendor Transmit PCS Interrupt Mask 1 - Address 3.A800 ).  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 03.FC00.A  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 2
                          */
                    /*! \brief 03.FC00.9 RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 3: Address 3.CC02 ) and the corresponding mask register ( See PCS Transmit Vendor LASI Interrupt Mask 3: Address 3.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 03.FC00.9  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 3
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.FC00.6 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor Receive XAUI Tx Alarms 1- Address 4.D800 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 1: Address 3.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 03.FC00.6  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
                    /*! \brief 03.FC00.5 RO Vendor Specific Rx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 2: Address 3.CC00 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 1: Address 3.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_2Interrupt : 1;    /* 03.FC00.5  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 2
                          */
                    /*! \brief 03.FC00.4 RO Vendor Specific Rx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 2 - Address 3.EC01 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 2 - Address 3.EC01 ).  */
      unsigned int   vendorSpecificRxAlarms_3Interrupt : 1;    /* 03.FC00.4  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 3
                          */
                    /*! \brief 03.FC00.3 RO Vendor Specific Rx Alarms 4 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_4Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 4
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 3 - Address 3.EC02 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 3 - Address 3.F402 ).  */
      unsigned int   vendorSpecificRxAlarms_4Interrupt : 1;    /* 03.FC00.3  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 4
                          */
                    /*! \brief 03.FC00.2 RO Vendor Specific Rx Alarms 5 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_5Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 5
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 4: Address 3.EC03 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 4: Address 3.F403 ).  */
      unsigned int   vendorSpecificRxAlarms_5Interrupt : 1;    /* 03.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 5
                          */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Dummy union to fill space in the structure PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.FC02.7 RO Vendor Specific Rx Alarms 6 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u2.bits_2.vendorSpecificRxAlarms_6Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 6
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_6Interrupt : 1;    /* 03.FC02.7  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 6
                          */
                    /*! \brief 03.FC02.6 RO Vendor Specific Rx Alarms 7 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_EUR.u2.bits_2.vendorSpecificRxAlarms_7Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 7
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_7Interrupt : 1;    /* 03.FC02.6  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 7
                          */
      unsigned int   reserved1 : 6;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsVendorGlobalInterruptFlags_EUR;

#endif
/*@}*/
/*@}*/
