/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file contains functions global register definitions for the
registers in the X5123 and EC808
********************************************************************/
#ifndef APIREGS_H
#define APIREGS_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define MCD_LINE_SIDE  3
#define MCD_HOST_SIDE  4
#define MCD_BOTH_SIDE  5
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
#define RUNIT_RFU_MPP_Control_0_1_REGISTER 0xC0018000
#define RUNIT_RFU_GPIO_Data_0_1_REGISTER 0xC0018104

#define RUNIT_SOC_MISC_INTERRUPT_OUT_CONTROL                0xC0018208
#define RUNIT_SOC_MISC_CLOCK_GATING_REGISTER                0xC0018218
#define RUNIT_SOC_MISC_MACSEC_CONFIGURATION                 0xC0018224
#define RUNIT_SOC_MISC_LED0_DISPLAY_REGISTER                0xC0018230
#define RUNIT_SOC_MISC_LED1_DISPLAY_REGISTER                0xC0018234
#define RUNIT_SOC_MISC_LED_PULSE_STRETCH_AND_BLINK_REGISTER 0xC0018238
#define RUNIT_SOC_MISC_LED_MIX_REGISTER                     0xC001823C
#define RUNIT_SOC_MISC_DEBUG_PORT_CONFIGURATION             0xC00182C0
#else
#define RUNIT_RFU_MPP_Control_0_1_REGISTER 0x0018000
#define RUNIT_RFU_GPIO_Data_0_1_REGISTER 0x00018104

#define RUNIT_SOC_MISC_INTERRUPT_OUT_CONTROL                0x00018208
#define RUNIT_SOC_MISC_CLOCK_GATING_REGISTER                0x00018218
#define RUNIT_SOC_MISC_MACSEC_CONFIGURATION                 0x00018224
#define RUNIT_SOC_MISC_LED0_DISPLAY_REGISTER                0x00018230
#define RUNIT_SOC_MISC_LED1_DISPLAY_REGISTER                0x00018234
#define RUNIT_SOC_MISC_LED_PULSE_STRETCH_AND_BLINK_REGISTER 0x00018238
#define RUNIT_SOC_MISC_LED_MIX_REGISTER                     0x0001823C
#define RUNIT_SOC_MISC_DEBUG_PORT_CONFIGURATION             0x000182C0
#define MCD_RCLK_CNTRL_REGISTER_MAC(_slice)    ((_slice)? (0x311811A0):(0x311801A0))
#endif
/* UMAC registers */
/* GLOBAL REGISTERS*/
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
#define UMAC_BASE(_slice) (0xC0000000 +0x20000*((_slice) + 1))
#else
#define UMAC_BASE(_slice) (0x20000*((_slice) + 1))
#endif
#define UMAC_GLBL_IP Version(_slice)                                     (UMAC_BASE(_slice) + 0x0000) /* 0x0000  */
#define UMAC_GLBL_Global_Mode(_slice)                                    (UMAC_BASE(_slice) + 0x0004) /* 0x0001  */
#define UMAC_GLBL_Channel_Mode(_slice)                                   (UMAC_BASE(_slice) + 0x000c) /* 0x0003  */
#define UMAC_GLBL_Channel_Enable(_slice)                                 (UMAC_BASE(_slice) + 0x0010) /* 0x0004  */
#define UMAC_GLBL_Software_Reset(_slice)                                 (UMAC_BASE(_slice) + 0x0014) /* 0x0005  */
#define UMAC_GLBL_Revision(_slice)                                       (UMAC_BASE(_slice) + 0x0018) /* 0x0006  */
#define UMAC_GLBL_PCS_Link_Status_Override(_slice)                       (UMAC_BASE(_slice) + 0x0020) /* 0x0008  */
#define UMAC_GLBL_Live_Link_Status0(_slice)                              (UMAC_BASE(_slice) + 0x0024) /* 0x0009  */
#define UMAC_GLBL_Live_Link_Status1(_slice)                              (UMAC_BASE(_slice) + 0x0028) /* 0x000A  */
#define UMAC_GLBL_Spare0(_slice)                                         (UMAC_BASE(_slice) + 0x002c) /* 0x000B  */
#define UMAC_GLBL_Spare2(_slice)                                         (UMAC_BASE(_slice) + 0x0034) /* 0x000D  */
#define UMAC_GLBL_Bypass(_slice)                                         (UMAC_BASE(_slice) + 0x0098) /* 0x0026  */
#define UMAC_GLBL_B2B_FIFO_Config_CH0(_slice)                            (UMAC_BASE(_slice) + 0x009c) /* 0x0027  */
#define UMAC_GLBL_B2B_FIFO_Config_CH1(_slice)                            (UMAC_BASE(_slice) + 0x00a0) /* 0x0028  */
#define UMAC_GLBL_B2B_FIFO_Config_CH2(_slice)                            (UMAC_BASE(_slice) + 0x00a4) /* 0x0029  */
#define UMAC_GLBL_B2B_FIFO_Config_CH3(_slice)                            (UMAC_BASE(_slice) + 0x00a8) /* 0x002a  */
#define UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(_slice)             (UMAC_BASE(_slice) + 0x00ac) /* 0x002b  */
#define UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH1(_slice)             (UMAC_BASE(_slice) + 0x00b0) /* 0x002c  */
#define UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH2(_slice)             (UMAC_BASE(_slice) + 0x00b8) /* 0x002e  */
#define UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH3(_slice)             (UMAC_BASE(_slice) + 0x00bc) /* 0x002f  */
#define UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(_slice)             (UMAC_BASE(_slice) + 0x00c0) /* 0x0030  */
#define UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH1(_slice)             (UMAC_BASE(_slice) + 0x00c4) /* 0x0031  */
#define UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH2(_slice)             (UMAC_BASE(_slice) + 0x00c8) /* 0x0032  */
#define UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH3(_slice)             (UMAC_BASE(_slice) + 0x00cc) /* 0x0033  */
#define UMAC_GLBL_ForceInterrupt0(_slice)                                (UMAC_BASE(_slice) + 0x01c0) /* 0x0070  */
#define UMAC_GLBL_ForceInterrupt1(_slice)                                (UMAC_BASE(_slice) + 0x01c4) /* 0x0071  */
#define UMAC_GLBL_DefineIndication(_slice)                               (UMAC_BASE(_slice) + 0x03f8) /* 0x00FE  */
#define UMAC_GLBL_Product_ID(_slice)                                     (UMAC_BASE(_slice) + 0x03fc) /* 0x00FF  */

/*Statistics Registers*/
#define UMAC_Statistics_Registers_Base(_slice,_mac)  (UMAC_BASE(_slice) + (_mac)*0x5c00)

#define UMAC_Statistics_Software_Reset(_slice,_mac)          (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0800) /*0x0200*/
#define UMAC_Statistics_Read_Control(_slice,_mac)            (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0804) /*0x0201*/
#define UMAC_Statistics_Read_Data0(_slice,_mac)              (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0808) /*0x0202*/
#define UMAC_Statistics_Read_Data1(_slice,_mac)              (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x080c) /*0x0203*/
#define UMAC_Statistics_Read_Data2(_slice,_mac)              (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0810) /*0x0204*/
#define UMAC_Statistics_Read_Data3(_slice,_mac)              (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0814) /*0x0205*/
#define UMAC_Statistics_Reset_Counter(_slice,_mac)           (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0818) /*0x0206*/
#define UMAC_Statistics_Channel0_LED_Info(_slice,_mac)       (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0820) /*0x0208*/
#define UMAC_Statistics_Channel1_LED_Info(_slice,_mac)       (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0824) /*0x0209*/
#define UMAC_Statistics_Channel2_LED_Info(_slice,_mac)       (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0828) /*0x020A*/
#define UMAC_Statistics_Channel3_LED_Info(_slice,_mac)       (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x082c) /*0x020B*/
#define UMAC_Statistics_Status(_slice,_mac)                  (UMAC_Statistics_Registers_Base(_slice,_mac) + 0x0830) /*0x020C*/

/*Channel MAC Registers */

#define UMAC_Channel_MAC_BASE(_slice,_chan) ((((_chan)<4)? 0x400*(_chan) : (0x4C00+ 0x400*(_chan))) + UMAC_BASE(_slice))

/* to convert host side of PCS register address to line side of PCS register address  */
/* added difference of addresses of subunits mcmac4 and mcmac0 (0x26800 - 0x20C00)*/
#define UMAC_MAC_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_Channel_MAC_Control(_slice,_chan)                                          (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C00) /*x0300 */
#define UMAC_Channel_MAC_Transmit_Configuration(_slice,_chan)                           (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C04) /*x0301 */
#define UMAC_Channel_MAC_Receive_Configuration(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C08) /*x0302 */
#define UMAC_Channel_MAC_Max_Frame_Size(_slice,_chan)                                   (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C0C) /*x0303 */
#define UMAC_Channel_MAC_Transmit_Jabber_Size(_slice,_chan)                             (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C10) /*x0304 */
#define UMAC_Channel_MAC_Receive_Jabber_Size(_slice,_chan)                              (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C14) /*x0305 */
#define UMAC_Channel_MAC_Transmit_Priority_Pause_Vector(_slice,_chan)                   (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C18) /*x0306 */
#define UMAC_Channel_MAC_VLAN_Tag1(_slice,_chan)                                        (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C1C) /*x0307 */
#define UMAC_Channel_MAC_VLAN_Tag2(_slice,_chan)                                        (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C20) /*x0308 */
#define UMAC_Channel_MAC_VLAN_Tag3(_slice,_chan)                                        (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C24) /*x0309 */
#define UMAC_Channel_MAC_Address_Low(_slice,_chan)                                      (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C28) /*x030A */
#define UMAC_Channel_MAC_Address_Mid(_slice,_chan)                                      (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C2C) /*x030B */
#define UMAC_Channel_MAC_Address_High(_slice,_chan)                                     (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C30) /*x030C */
#define UMAC_Channel_MAC_Multicast_Hash_Table1(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C34) /*x030D */
#define UMAC_Channel_MAC_Multicast_Hash_Table2(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C38) /*x030E */
#define UMAC_Channel_MAC_Multicast_Hash_Table3(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C3C) /*x030F */
#define UMAC_Channel_MAC_Multicast_Hash_Table4(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C40) /*x0310 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Generate_Control(_slice,_chan)              (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C44) /*x0311 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Destination_Address_Low(_slice,_chan)       (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C48) /*x0312 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Destination_Address_Mid(_slice,_chan)       (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C4C) /*x0313 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Destination_Address_High(_slice,_chan)      (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C50) /*x0314 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Source_Address_Low(_slice,_chan)            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C54) /*x0315 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Source_Address_Mid(_slice,_chan)            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C58) /*x0316 */
#define UMAC_Channel_MAC_Flow_Control_Frame_Source_Address_High(_slice,_chan)           (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C5C) /*x0317 */
#define UMAC_Channel_MAC_Flow_Control_PAUSE_Time_Value(_slice,_chan)                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C60) /*x0318 */
#define UMAC_Channel_MAC_XOFF_PAUSE_Time_Value(_slice,_chan)                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C64) /*x0319 */
#define UMAC_Channel_MAC_XON_PAUSE_Time_Value(_slice,_chan)                             (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C68) /*x031A */
#define UMAC_Channel_MAC_Min_Frame_Size(_slice,_chan)                                   (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C8C) /*x0323 */
#define UMAC_Channel_MAC_TX_VLAN_tag(_slice,_chan)                                      (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C90) /*x0324 */
#define UMAC_Channel_MAC_RX_Error_Mask(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0C94) /*x0325 */
#define UMAC_Channel_MAC_ForceInterrupt0(_slice,_chan)                                  (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0DC0) /*x0370 */
#define UMAC_Channel_MAC_ForceInterrupt1(_slice,_chan)                                  (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0DC4) /*x0371 */
#define UMAC_Channel_MAC_ForceInterrupt2(_slice,_chan)                                  (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0DC8) /*x0372 */
#define UMAC_Channel_MAC_IETH_Header_control(_slice,_chan)                              (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E00) /*x0380 */
#define UMAC_Channel_MAC_IETH_Header_0(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E04) /*x0381 */
#define UMAC_Channel_MAC_IETH_Header_1(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E08) /*x0382 */
#define UMAC_Channel_MAC_IETH_Header_2(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E0C) /*x0383 */
#define UMAC_Channel_MAC_IETH_Header_3(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E10) /*x0384 */
#define UMAC_Channel_MAC_IETH_Header_4(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E14) /*x0385 */
#define UMAC_Channel_MAC_IETH_Header_5(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E18) /*x0386 */
#define UMAC_Channel_MAC_IETH_Header_6(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E1C) /*x0387 */
#define UMAC_Channel_MAC_IETH_Header_7(_slice,_chan)                                    (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E20) /*x0388 */
#define UMAC_Channel_MAC_Pause_Slot_Clock_Count(_slice,_chan)                           (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E28) /*x038A */
#define UMAC_Channel_MAC_Inband_Flow_Control_Fsig_Insertion_Frequency(_slice,_chan)     (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E2C) /*x038B */
#define UMAC_Channel_MAC_Inband_Flow_Control_Fsig_Control(_slice,_chan)                 (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E30) /*x038C */
#define UMAC_Channel_MAC_Inband_Flow_Control_Fsig_CFG_Field(_slice,_chan)               (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E40) /*x0390 */
#define UMAC_Channel_MAC_Debug(_slice,_chan)                                            (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0E44) /*x0391 */
#define UMAC_Channel_MAC_spare0(_slice,_chan)                                           (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0FF8) /*x03fe */
#define UMAC_Channel_MAC_Pause_uSec_Counter(_slice,_chan)                               (UMAC_Channel_MAC_BASE(_slice,_chan) + 0x0FFC) /*x03FF */

/*Channel#0 10/40/100G PCS0 Registers Map
0x00020C00 CPU mcmac0 / UMAC/Slice %m/umac3gbsx4/mcmac0
0x00040C00 CPU mcmac0 / UMAC/Slice %m/umac3gbsx4/mcmac0*/

/* MAC and MCPSC per channel units have same offset formula */
/* this macro related to host side of PCS register address */
#define UMAC_MCPCS_BASE(_slice,_chan) UMAC_Channel_MAC_BASE(_slice,_chan)

/* to convert host side of PCS register address to line side of PCS register address  */
/* added difference of addresses of subunits hsmcpcs4 and hsmcpcs0 (0x27800 - 0x21C00)*/
#define UMAC_MCPCS_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_MCPCS_PCS_Control1(_slice,_chan)                               (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C00)                /* 0x0700*/
#define UMAC_MCPCS_PCS_Status1(_slice,_chan)                                (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C04)                /* 0x0701*/
#define UMAC_MCPCS_Fibre_Channel_SwReset(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C28)                /* 0x070A*/
#define UMAC_MCPCS_Fibre_Channel_Rate_Match_Enable(_slice,_chan)            (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C30)                /* 0x070C*/
#define UMAC_MCPCS_Ch_Mode(_slice,_chan)                                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C40)                /* 0x0710*/
#define UMAC_MCPCS_Fibre_Channel_FIFO_Threshold(_slice,_chan)               (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C48)                /* 0x0712*/
#define UMAC_MCPCS_UXGMII_Faults_Control(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C4C)                /* 0x0713*/
#define UMAC_MCPCS_Fibre_Channel_FIFO_Start_Read(_slice,_chan)              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C54)                /* 0x0715*/
#define UMAC_MCPCS_BASE_R_and_10GBASE_T_PCS_Status1(_slice,_chan)           (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C80)                /* 0x0720*/
#define UMAC_MCPCS_BASE_R_and_10GBASE_T_PCS_Status2(_slice,_chan)           (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C84)                /* 0x0721*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_A1(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C88)                /* 0x0722*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_A2(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C8C)                /* 0x0723*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_A3(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C90)                /* 0x0724*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_A4(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C94)                /* 0x0725*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_B1(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C98)                /* 0x0726*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_B2(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1C9C)                /* 0x0727*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_B3(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CA0)                /* 0x0728*/
#define UMAC_MCPCS_10GBASE_R_PCS_Test_pattern_Seed_B4(_slice,_chan)         (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CA4)                /* 0x0729*/
#define UMAC_MCPCS_BASE_R_PCS_Test_pattern_Control(_slice,_chan)            (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CA8)                /* 0x072A*/
#define UMAC_MCPCS_BASE_R_PCS_Test_pattern_error_counter(_slice,_chan)      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CAC)                /* 0x072B*/
#define UMAC_MCPCS_BER_High_order_Counter(_slice,_chan)                     (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CB0)                /* 0x072C*/
#define UMAC_MCPCS_Errored_Blocks_High_Order_Counter(_slice,_chan)          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CB4)                /* 0x072D*/
#define UMAC_MCPCS_Counters0(_slice,_chan)                                  (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CB8)                /* 0x072E*/
#define UMAC_MCPCS_Counters1(_slice,_chan)                                  (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CBC)                /* 0x072F*/
#define UMAC_MCPCS_Counters2(_slice,_chan)                                  (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CC0)                /* 0x0730*/
#define UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status1(_slice,_chan)    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CC8)                /* 0x0732*/
#define UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status2(_slice,_chan)    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CCC)                /* 0x0733*/
#define UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status3(_slice,_chan)    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CD0)                /* 0x0734*/
#define UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status4(_slice,_chan)    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1CD4)                /* 0x0735*/
#define UMAC_MCPCS_Programmable_AM_ctrl(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D40)                /* 0x0750*/
#define UMAC_MCPCS_Programmable_AM0_low(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D70)                /* 0x075C*/
#define UMAC_MCPCS_Programmable_AM0_high(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D74)                /* 0x075D*/
#define UMAC_MCPCS_Programmable_AM1_low(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D78)                /* 0x075E*/
#define UMAC_MCPCS_Programmable_AM1_high(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D7C)                /* 0x075F*/
#define UMAC_MCPCS_Programmable_AM2_low(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D80)                /* 0x0760*/
#define UMAC_MCPCS_Programmable_AM2_high(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D84)                /* 0x0761*/
#define UMAC_MCPCS_Programmable_AM3_low(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D88)                /* 0x0762*/
#define UMAC_MCPCS_Programmable_AM3_high(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1D8C)                /* 0x0763*/
#define UMAC_MCPCS_ForceInterrupt0(_slice,_chan)                            (UMAC_MCPCS_BASE(_slice,_chan) + 0x1DC0)                /* 0x0770*/
#define UMAC_MCPCS_Lane0_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E40)                /* 0x0790*/
#define UMAC_MCPCS_Lane1_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E44)                /* 0x0791*/
#define UMAC_MCPCS_Lane2_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E48)                /* 0x0792*/
#define UMAC_MCPCS_Lane3_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E4C)                /* 0x0793*/
#define UMAC_MCPCS_Lane4_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E50)                /* 0x0794*/
#define UMAC_MCPCS_Lane5_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E54)                /* 0x0795*/
#define UMAC_MCPCS_Lane6_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E58)                /* 0x0796*/
#define UMAC_MCPCS_Lane7_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E5C)                /* 0x0797*/
#define UMAC_MCPCS_Lane8_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E60)                /* 0x0798*/
#define UMAC_MCPCS_Lane9_Mapping(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E64)                /* 0x0799*/
#define UMAC_MCPCS_Lane10_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E68)                /* 0x079A*/
#define UMAC_MCPCS_Lane11_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E6C)                /* 0x079B*/
#define UMAC_MCPCS_Lane12_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E70)                /* 0x079C*/
#define UMAC_MCPCS_Lane13_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E74)                /* 0x079D*/
#define UMAC_MCPCS_Lane14_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E78)                /* 0x079E*/
#define UMAC_MCPCS_Lane15_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E7C)                /* 0x079F*/
#define UMAC_MCPCS_Lane16_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E80)                /* 0x07A0*/
#define UMAC_MCPCS_Lane17_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E84)                /* 0x07A1*/
#define UMAC_MCPCS_Lane18_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E88)                /* 0x07A2*/
#define UMAC_MCPCS_Lane19_Mapping(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1E8C)                /* 0x07A3*/
#define UMAC_MCPCS_BIP_error_counter_lane0(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F20)                /* 0x07C8*/
#define UMAC_MCPCS_BIP_error_counter_lane1(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F24)                /* 0x07C9*/
#define UMAC_MCPCS_BIP_error_counter_lane2(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F28)                /* 0x07CA*/
#define UMAC_MCPCS_BIP_error_counter_lane3(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F2C)                /* 0x07CB*/
#define UMAC_MCPCS_BIP_error_counter_lane4(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F30)                /* 0x07CC*/
#define UMAC_MCPCS_BIP_error_counter_lane5(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F34)                /* 0x07CD*/
#define UMAC_MCPCS_BIP_error_counter_lane6(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F38)                /* 0x07CE*/
#define UMAC_MCPCS_BIP_error_counter_lane7(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F3C)                /* 0x07CF*/
#define UMAC_MCPCS_BIP_error_counter_lane8(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F40)                /* 0x07D0*/
#define UMAC_MCPCS_BIP_error_counter_lane9(_slice,_chan)                    (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F44)                /* 0x07D1*/
#define UMAC_MCPCS_BIP_error_counter_lane10(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F48)                /* 0x07D2*/
#define UMAC_MCPCS_BIP_error_counter_lane11(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F4C)                /* 0x07D3*/
#define UMAC_MCPCS_BIP_error_counter_lane12(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F50)                /* 0x07D4*/
#define UMAC_MCPCS_BIP_error_counter_lane13(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F54)                /* 0x07D5*/
#define UMAC_MCPCS_BIP_error_counter_lane14(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F58)                /* 0x07D6*/
#define UMAC_MCPCS_BIP_error_counter_lane15(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F5C)                /* 0x07D7*/
#define UMAC_MCPCS_BIP_error_counter_lane16(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F60)                /* 0x07D8*/
#define UMAC_MCPCS_BIP_error_counter_lane17(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F64)                /* 0x07D9*/
#define UMAC_MCPCS_BIP_error_counter_lane18(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F68)                /* 0x07DA*/
#define UMAC_MCPCS_BIP_error_counter_lane19(_slice,_chan)                   (UMAC_MCPCS_BASE(_slice,_chan) + 0x1F6C)                /* 0x07DB*/
#define UMAC_MCPCS_Debug_Bit_Error_Gap(_slice,_chan)                        (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FC4)                /* 0x07F1*/
#define UMAC_MCPCS_Debug_Sync_Header_Gap(_slice,_chan)                      (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FC8)                /* 0x07F2*/
#define UMAC_MCPCS_Debug_Code_Group0(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FCC)                /* 0x07F3*/
#define UMAC_MCPCS_Debug_Code_Group1(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FD0)                /* 0x07F4*/
#define UMAC_MCPCS_Debug_Code_Group2(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FD4)                /* 0x07F5*/
#define UMAC_MCPCS_Debug_Code_Group3(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FD8)                /* 0x07F6*/
#define UMAC_MCPCS_Debug_Code_Group4(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FDC)                /* 0x07F7*/
#define UMAC_MCPCS_Debug_Control2(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FE0)                /* 0x07F8*/
#define UMAC_MCPCS_BER_State_Machine_Override(_slice,_chan)                 (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FEC)                /* 0x07FB*/
#define UMAC_MCPCS_spare0(_slice,_chan)                                     (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FF0)                /* 0x07FC*/
#define UMAC_MCPCS_Debug_Status2_Global(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FF4)                /* 0x07FD*/
#define UMAC_MCPCS_Debug_Status1_Global(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FF8)                /* 0x07FE*/
#define UMAC_MCPCS_Debug_Control1(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x1FFC)                /* 0x07FF*/

/* Global mode definitions */
#define UMAC_GLOBAL_MODE_100G        0     /* 100G - Channel #0 */
#define UMAC_GLOBAL_MODE_2x25G_50G   2     /*(Channel #0, #1), 1x50G (Channel#2) */
#define UMAC_GLOBAL_MODE_1x40G       4     /*(Channel #0) */
#define UMAC_GLOBAL_MODE_2x40G       6     /*(Channel #0, #2)*/
#define UMAC_GLOBAL_MODE_50G_2x25G   7     /*Channel #0, 2x25G (Channel#2/3) */
#define UMAC_GLOBAL_MODE_4x25G       8     /*(Channel #0, #1, #2, #3)*/

#define UMAC_CHANNEL_MODE_10G        0     /*Channel 10G Mode*/
#define UMAC_CHANNEL_MODE_1G         1     /*Channel 1Gbps Mode*/
#define UMAC_CHANNEL_MODE_25G        2     /*Channel 25G Mode*/

/* Low Speed MCMPCS                                        */
/* to convert host side of PCS register address to line side of PCS register address  */
/* added difference of addresses of subunits lsmcpcs4 and lsmcpcs0 (0x28800 - 0x22C00)*/
#define UMAC_LSMCPCS_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_LSMCPCS_ctrl(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C00)                /* 0x0B00*/
#define UMAC_LSMCPCS_mradvability(_slice,_chan)                     (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C04)                /* 0x0B01*/
#define UMAC_LSMCPCS_rxconfig(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C08)                /* 0x0B02*/
#define UMAC_LSMCPCS_lnktimer(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C0C)                /* 0x0B03*/
#define UMAC_LSMCPCS_disperrcnt(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C10)                /* 0x0B04*/
#define UMAC_LSMCPCS_invcodecnt(_slice,_chan)                       (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C14)                /* 0x0B05*/
#define UMAC_LSMCPCS_sts(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C18)                /* 0x0B06*/
#define UMAC_LSMCPCS_lnktimer2(_slice,_chan)                        (UMAC_MCPCS_BASE(_slice,_chan) + 0x2C4C)                /* 0x0B13*/
#define UMAC_LSMCPCS_fibrechancnt(_slice,_chan)                     (UMAC_MCPCS_BASE(_slice,_chan) + 0x2D0C)                /* 0x0B43*/
#define UMAC_LSMCPCS_fibrechangmiierrswitch(_slice,_chan)           (UMAC_MCPCS_BASE(_slice,_chan) + 0x2D10)                /* 0x0B44*/
#define UMAC_LSMCPCS_fint0(_slice,_chan)                            (UMAC_MCPCS_BASE(_slice,_chan) + 0x2DC0)                /* 0x0B70*/
#define UMAC_LSMCPCS_spare1(_slice,_chan)                           (UMAC_MCPCS_BASE(_slice,_chan) + 0x2FF8)                /* 0x0BFE*/


#define UMAC_SERDESMUX_laneremaprx(_slice)                           (UMAC_BASE(_slice) + 0x05C08)
#define UMAC_SERDESMUX_laneremaptx(_slice)                           (UMAC_BASE(_slice) + 0x05E08)

/* Bit definition for BASE-X advertisement (mradvability) register */
#define MCD_BASEX_AD_ASYM_PAUSE         0x0100      /* Bit-8, Asymmetric Pause bit */
#define MCD_BASEX_AD_PAUSE              0x0080      /* Bit-7, Pause */
#define MCD_BASEX_AD_1000HDX            0x0040      /* Bit-6, 1000X Half Duplex */
#define MCD_BASEX_AD_1000FDX            0x0020      /* Bit-5, 1000X Full Duplex */
#define MCD_BASEX_AD_MASK               (MCD_BASEX_AD_ASYM_PAUSE | \
                                         MCD_BASEX_AD_PAUSE      | \
                                         MCD_BASEX_AD_1000HDX    | \
                                         MCD_BASEX_AD_1000FDX)

/* SERDES wrapper pipe registers */
/*Offset Formula:   0x32000000 + 0x1000 * a + 0x80000 * t: where a (0-7) represents SERDES_Num, where t (0-1) represents CHAIN_Num */
#define MAX_SERDES_NUM_IN_SLICE 8
#define FIRST_LINE_SERDES_NUM_IN_SLICE 4
#define MCD_SD_IP_SIDE(_serdes)              (_serdes/MAX_SERDES_NUM_IN_SLICE)
#define MCD_SD_IP_SERDES_ON_SIDE_NUM(_serdes)    (_serdes & 0x7)

#define MCD_SD_IP_SIDE_OFFSET(_serdes)           (MCD_SD_IP_SIDE(_serdes)*0x80000)
#define MCD_SD_IP_SERDES_ON_SIDE_OFFSET(_serdes) (MCD_SD_IP_SERDES_ON_SIDE_NUM(_serdes)*0x1000)
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
#define MCD_SD_IP_BASE(_serdes)  (0x62000000 + MCD_SD_IP_SIDE_OFFSET(_serdes) + MCD_SD_IP_SERDES_ON_SIDE_OFFSET(_serdes))
#else
#define MCD_SD_IP_BASE(_serdes)  (0x32000000 + MCD_SD_IP_SIDE_OFFSET(_serdes) + MCD_SD_IP_SERDES_ON_SIDE_OFFSET(_serdes))
#endif
#define MCD_SERDES_EXTERNAL_CONFIGURATION_0(_serdes)                    (MCD_SD_IP_BASE(_serdes) + 0x00)
#define MCD_SERDES_EXTERNAL_CONFIGURATION_1(_serdes)                    (MCD_SD_IP_BASE(_serdes) + 0x04)
#define MCD_SERDES_Miscellaneous(_serdes)                               (MCD_SD_IP_BASE(_serdes) + 0x08)
#define MCD_SERDES_External_Status(_serdes)                             (MCD_SD_IP_BASE(_serdes) + 0x0C)
#define MCD_SERDES_Core_2_Control(_serdes)                              (MCD_SD_IP_BASE(_serdes) + 0x10)
#define MCD_SERDES_Core_Status(_serdes)                                 (MCD_SD_IP_BASE(_serdes) + 0x14)
#define MCD_SERDES_Analog_2_Core(_serdes)                               (MCD_SD_IP_BASE(_serdes) + 0x18)
#define MCD_SERDES_Core_Interrupt_Data(_serdes)                         (MCD_SD_IP_BASE(_serdes) + 0x1C)
#define MCD_SERDES_Core_Interrupt_Code(_serdes)                         (MCD_SD_IP_BASE(_serdes) + 0x20)
#define MCD_SERDES_Core_Interrupt_Result(_serdes)                       (MCD_SD_IP_BASE(_serdes) + 0x24)
#define MCD_SERDES_Interrupt0_cause(_serdes)                            (MCD_SD_IP_BASE(_serdes) + 0x28)
#define MCD_SERDES_Interrupt0_mask(_serdes)                             (MCD_SD_IP_BASE(_serdes) + 0x2C)
#define MCD_SERDES_Interrupt1_cause(_serdes)                            (MCD_SD_IP_BASE(_serdes) + 0x30)
#define MCD_SERDES_Interrupt1_mask(_serdes)                             (MCD_SD_IP_BASE(_serdes) + 0x34)
#define MCD_SERDES_Interrupt2_cause(_serdes)                            (MCD_SD_IP_BASE(_serdes) + 0x38)
#define MCD_SERDES_Interrupt2_mask(_serdes)                             (MCD_SD_IP_BASE(_serdes) + 0x3C)
#define MCD_SERDES_Interrupt_summary_cause(_serdes)                     (MCD_SD_IP_BASE(_serdes) + 0x40)
#define MCD_SERDES_Interrupt_summary_mask(_serdes)                      (MCD_SD_IP_BASE(_serdes) + 0x44)

#define MCD_SERDES_TSEN_IP_BASE         0x33044400

#define MCD_SERDES_TSEN_IP_control                                      MCD_SERDES_TSEN_IP_BASE + 0x0000
#define MCD_SERDES_TSEN_IP_clock_divider                                MCD_SERDES_TSEN_IP_BASE + 0x0004
#define MCD_SERDES_TSEN_IP_sensor_enable                                MCD_SERDES_TSEN_IP_BASE + 0x000C
#define MCD_SERDES_TSEN_IP_spare                                        MCD_SERDES_TSEN_IP_BASE + 0x0010
#define MCD_SERDES_TSEN_IP_THERM_STATE                                  MCD_SERDES_TSEN_IP_BASE + 0x0014
#define MCD_SERDES_TSEN_IP_TEMP_GAIN_OVRD_VAL                           MCD_SERDES_TSEN_IP_BASE + 0x0018
#define MCD_SERDES_TSEN_IP_TEMP_OFFSET_OVRD_VA                          MCD_SERDES_TSEN_IP_BASE + 0x001C
#define MCD_SERDES_TSEN_IP_TEMP_C_RES_OVRD_VAL                          MCD_SERDES_TSEN_IP_BASE + 0x0020
#define MCD_SERDES_TSEN_IP_TEMP_GAIN_TRIM_OVRD_VAL                      MCD_SERDES_TSEN_IP_BASE + 0x0024
#define MCD_SERDES_TSEN_IP_TEMP_OFFSET_TRIM_OVRD_VAL                    MCD_SERDES_TSEN_IP_BASE + 0x0028
#define MCD_SERDES_TSEN_IP_OVRD_EN                                      MCD_SERDES_TSEN_IP_BASE + 0x002C
#define MCD_SERDES_TSEN_IP_VOLTAGE_GAIN_OVRD_VAL                        MCD_SERDES_TSEN_IP_BASE + 0x0030
#define MCD_SERDES_TSEN_IP_VOLTAGE_OFFSET_OVRD_VAL                      MCD_SERDES_TSEN_IP_BASE + 0x0034
#define MCD_SERDES_TSEN_IP_VOLTAGE_C_RES_OVRD_VAL                       MCD_SERDES_TSEN_IP_BASE + 0x0038
#define MCD_SERDES_TSEN_IP_VOLTAGE_GAIN_TRIM_OVRD_VAL                   MCD_SERDES_TSEN_IP_BASE + 0x003C
#define MCD_SERDES_TSEN_IP_voltage_ovrd_en                              MCD_SERDES_TSEN_IP_BASE + 0x0040
#define MCD_SERDES_TSEN_IP_REMOTE_GAIN_OVRD_VAL                         MCD_SERDES_TSEN_IP_BASE + 0x0044
#define MCD_SERDES_TSEN_IP_REMOTE_OFFSET_OVRD_VAL                       MCD_SERDES_TSEN_IP_BASE + 0x0048
#define MCD_SERDES_TSEN_IP_REMOTE_C_RES_OVRD_VAL                        MCD_SERDES_TSEN_IP_BASE + 0x004C
#define MCD_SERDES_TSEN_IP_REMOTE_OVRD_EN                               MCD_SERDES_TSEN_IP_BASE + 0x0050
#define MCD_SERDES_TSEN_IP_ACCUMULATOR                                  MCD_SERDES_TSEN_IP_BASE + 0x0100
#define MCD_SERDES_TSEN_IP_TEMPERATURE_SENSOR_VALUE                     MCD_SERDES_TSEN_IP_BASE + 0x0104
#define MCD_SERDES_TSEN_IP_REMOTE0_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x0108
#define MCD_SERDES_TSEN_IP_REMOTE1_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x010C
#define MCD_SERDES_TSEN_IP_REMOTE2_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x0110
#define MCD_SERDES_TSEN_IP_REMOTE3_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x0114
#define MCD_SERDES_TSEN_IP_REMOTE4_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x0118
#define MCD_SERDES_TSEN_IP_REMOTE5_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x011C
#define MCD_SERDES_TSEN_IP_REMOTE7_SENSOR                               MCD_SERDES_TSEN_IP_BASE + 0x0124
#define MCD_SERDES_TSEN_IP_VDD_VOLTAGE_SENSOR_VALUE                     MCD_SERDES_TSEN_IP_BASE + 0x0128
#define MCD_SERDES_TSEN_IP_CORE_VDD_VIN_VOLTAGE_SENSOR_VALUE            MCD_SERDES_TSEN_IP_BASE + 0x012C
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN0_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x0130
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN1_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x0134
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN2_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x0138
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN3_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x013C
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN4_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x0140
#define MCD_SERDES_TSEN_IP_SENSOR_A2D_VIN5_VOLTAGE_SENSOR_VALUE         MCD_SERDES_TSEN_IP_BASE + 0x0144
#define MCD_SERDES_TSEN_IP_IDENTIFICATION_REGISTER                      MCD_SERDES_TSEN_IP_BASE + 0x03FC

/* FEC-RS */
/* to convert host side of FEC-RS register address to line side of PCS register address  */
/* added difference of addresses of subunits fecrs4 and fecrs0 (0x29800 - 0x23C00)       */
#define UMAC_FECRS_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_FECRS_dbgctrl(_slice,_chan)                            (UMAC_MCPCS_BASE(_slice,_chan) + 0x3C00)                /* 0x0F00*/
#define UMAC_FECRS_dbgsts(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x3C04)                /* 0x0F01*/
#define UMAC_FECRS_dbgberintthres(_slice,_chan)                     (UMAC_MCPCS_BASE(_slice,_chan) + 0x3C14)                /* 0x0F05*/
#define UMAC_FECRS_frcinvalidtimerlo(_slice,_chan)                  (UMAC_MCPCS_BASE(_slice,_chan) + 0x3C18)                /* 0x0F06*/
#define UMAC_FECRS_frcinvalidtimerhi(_slice,_chan)                  (UMAC_MCPCS_BASE(_slice,_chan) + 0x3C1C)                /* 0x0F07*/
#define UMAC_FECRS_fint0(_slice,_chan)                              (UMAC_MCPCS_BASE(_slice,_chan) + 0x3DC0)                /* 0x0F70*/
#define UMAC_FECRS_ctrl(_slice,_chan)                               (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F20)                /* 0x0FC8*/
#define UMAC_FECRS_sts(_slice,_chan)                                (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F24)                /* 0x0FC9*/
#define UMAC_FECRS_corrcntlo(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F28)                /* 0x0FCA*/
#define UMAC_FECRS_corrcnthi(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F2C)                /* 0x0FCB*/
#define UMAC_FECRS_uncorrcntlo(_slice,_chan)                        (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F30)                /* 0x0FCC*/
#define UMAC_FECRS_uncorrcnthi(_slice,_chan)                        (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F34)                /* 0x0FCD*/
#define UMAC_FECRS_lanemapping(_slice,_chan)                        (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F38)                /* 0x0FCE*/
#define UMAC_FECRS_serlane0lo(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F48)                /* 0x0FD2*/
#define UMAC_FECRS_serlane0hi(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F4C)                /* 0x0FD3*/
#define UMAC_FECRS_serlane1lo(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F50)                /* 0x0FD4*/
#define UMAC_FECRS_serlane1hi(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F54)                /* 0x0FD5*/
#define UMAC_FECRS_serlane2lo(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F58)                /* 0x0FD6*/
#define UMAC_FECRS_serlane2hi(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F5C)                /* 0x0FD7*/
#define UMAC_FECRS_serlane3lo(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F60)                /* 0x0FD8*/
#define UMAC_FECRS_serlane3hi(_slice,_chan)                         (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F64)                /* 0x0FD9*/
#define UMAC_FECRS_eccerrcnt(_slice,_chan)                          (UMAC_MCPCS_BASE(_slice,_chan) + 0x3F68)                /* 0x0FDA*/
#define UMAC_FECRS_spare0(_slice,_chan)                             (UMAC_MCPCS_BASE(_slice,_chan) + 0x3FF0)                /* 0x0FFC*/
#define UMAC_FECRS_ieeecfg(_slice,_chan)                            (UMAC_MCPCS_BASE(_slice,_chan) + 0x3FF4)                /* 0x0FFD*/


#define UMAC_SERDESMUX_BASE(_slice,_chan) ((((_chan)<4)? 0x5c00 : 0xb800) + UMAC_BASE(_slice))

#define UMAC_SERDES_MUX_SerDes_Signal_Status_Override(_slice,_chan)    (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0000)    /* 0x1700 */
#define UMAC_SERDES_MUX_SerDes_Loopback_Enable(_slice,_chan)           (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0004)    /* 0x1701 */
#define UMAC_SERDES_MUX_Lane_Remap_RX0(_slice,_chan)                   (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0008)    /* 0x1702 */
#define UMAC_SERDES_MUX_FIFO_status0(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00C0)    /* 0x1730 */
#define UMAC_SERDES_MUX_FIFO_status1(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00C4)    /* 0x1731 */
#define UMAC_SERDES_MUX_FIFO_status2(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00C8)    /* 0x1732 */
#define UMAC_SERDES_MUX_FIFO_status3(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00CC)    /* 0x1733 */
#define UMAC_SERDES_MUX_FIFO_status4(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00D0)    /* 0x1734 */
#define UMAC_SERDES_MUX_FIFO_status5(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00D4)    /* 0x1735 */
#define UMAC_SERDES_MUX_FIFO_status6(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00D8)    /* 0x1736 */
#define UMAC_SERDES_MUX_FIFO_status7(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00DC)    /* 0x1737 */
#define UMAC_SERDES_MUX_FIFO_Error_Status(_slice,_chan)                (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0100)    /* 0x1740 */
#define UMAC_SERDES_MUX_SerDesSync_Loopback_Enable(_slice,_chan)       (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0104)    /* 0x1741 */
#define UMAC_SERDES_MUX_Pacer_Select(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0108)    /* 0x1742 */
#define UMAC_SERDES_MUX_Pacer_Divide_Lane0(_slice,_chan)               (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x010c)    /* 0x1743 */
#define UMAC_SERDES_MUX_Pacer_Divide_Lane1(_slice,_chan)               (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0110)    /* 0x1744 */
#define UMAC_SERDES_MUX_Pacer_Divide_Lane2(_slice,_chan)               (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0114)    /* 0x1745 */
#define UMAC_SERDES_MUX_Pacer_Divide_Lane3(_slice,_chan)               (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0118)    /* 0x1746 */
#define UMAC_SERDES_MUX_TX_PRBS_Config_Lane0(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x012C)    /* 0x174b */
#define UMAC_SERDES_MUX_TX_PRBS_Config_Lane1(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0130)    /* 0x174c */
#define UMAC_SERDES_MUX_TX_PRBS_Config_Lane2(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0134)    /* 0x174d */
#define UMAC_SERDES_MUX_TX_PRBS_Config_Lane3(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0138)    /* 0x174e */
#define UMAC_SERDES_MUX_RX_PRBS_Config_Lane0(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x014c)    /* 0x1753 */
#define UMAC_SERDES_MUX_RX_PRBS_Config_Lane1(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0150)    /* 0x1754 */
#define UMAC_SERDES_MUX_RX_PRBS_Config_Lane2(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0154)    /* 0x1755 */
#define UMAC_SERDES_MUX_RX_PRBS_Config_Lane3(_slice,_chan)             (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0158)    /* 0x1756 */
#define UMAC_SERDES_MUX_RX_PRBS_Error_Counter_Lane0(_slice,_chan)      (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x016c)    /* 0x175b */
#define UMAC_SERDES_MUX_RX_PRBS_Error_Counter_Lane1(_slice,_chan)      (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0170)    /* 0x175c */
#define UMAC_SERDES_MUX_RX_PRBS_Error_Counter_Lane2(_slice,_chan)      (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0174)    /* 0x175d */
#define UMAC_SERDES_MUX_RX_PRBS_Error_Counter_Lane3(_slice,_chan)      (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0178)    /* 0x175e */
#define UMAC_SERDES_MUX_TX_ErrorInjection_ConfigLane0(_slice,_chan)    (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x018c)    /* 0x1763 */
#define UMAC_SERDES_MUX_TX_ErrorInjection_ConfigLane1(_slice,_chan)    (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0190)    /* 0x1764 */
#define UMAC_SERDES_MUX_TX_ErrorInjection_ConfigLane2(_slice,_chan)    (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0194)    /* 0x1765 */
#define UMAC_SERDES_MUX_TX_ErrorInjection_ConfigLane3(_slice,_chan)    (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x0198)    /* 0x1766 */
#define UMAC_SERDES_MUX_ForceInterrupt0(_slice,_chan)                  (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x01c0)    /* 0x1770 */
#define UMAC_SERDES_MUX_LaneRemapTX0(_slice,_chan)                     (UMAC_SERDESMUX_BASE(_slice,_chan) + 0x00C0)    /* 0x1782 */


/* APP FIFOs */
/* to convert host side of APP-FIFO register address to line side of APP-FIFO register address  */
/* added difference of addresses of subunits appfifo1 and appfifo0 (0x2C800 - 0x2C400)          */
#define UMAC_APP_FIFO_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x0400)

#define UMAC_APP_FIFO_ctrl1(_slice)              (UMAC_BASE(_slice) + 0xC404)  /* 0x3101*/
#define UMAC_APP_FIFO_appfifolpbk(_slice)        (UMAC_BASE(_slice) + 0xC408)  /* 0x3102*/
#define UMAC_APP_FIFO_appfifolpthrsh(_slice)     (UMAC_BASE(_slice) + 0xC410)  /* 0x3104*/
#define UMAC_APP_FIFO_appfifoportmap0(_slice)    (UMAC_BASE(_slice) + 0xC414)  /* 0x3105*/
#define UMAC_APP_FIFO_rxfifoctrl0(_slice)        (UMAC_BASE(_slice) + 0xC41C)  /* 0x3107*/
#define UMAC_APP_FIFO_rxfifoctrl1(_slice)        (UMAC_BASE(_slice) + 0xC420)  /* 0x3108*/
#define UMAC_APP_FIFO_rxfifoctrl2(_slice)        (UMAC_BASE(_slice) + 0xC424)  /* 0x3109*/
#define UMAC_APP_FIFO_rxfifoctrl3(_slice)        (UMAC_BASE(_slice) + 0xC428)  /* 0x310A*/
#define UMAC_APP_FIFO_txfifoctrl0(_slice)        (UMAC_BASE(_slice) + 0xC43C)  /* 0x310F*/
#define UMAC_APP_FIFO_txfifoctrl1(_slice)        (UMAC_BASE(_slice) + 0xC440)  /* 0x3110*/
#define UMAC_APP_FIFO_txfifoctrl2(_slice)        (UMAC_BASE(_slice) + 0xC444)  /* 0x3111*/
#define UMAC_APP_FIFO_txfifoctrl3(_slice)        (UMAC_BASE(_slice) + 0xC448)  /* 0x3112*/
#define UMAC_APP_FIFO_chmap0(_slice)             (UMAC_BASE(_slice) + 0xC45C)  /* 0x3117*/
#define UMAC_APP_FIFO_chmap1(_slice)             (UMAC_BASE(_slice) + 0xC460)  /* 0x3118*/
#define UMAC_APP_FIFO_ctrl2(_slice)              (UMAC_BASE(_slice) + 0xC464)  /* 0x3119*/
#define UMAC_APP_FIFO_debctrl0(_slice)           (UMAC_BASE(_slice) + 0xC500)  /* 0x3140*/
#define UMAC_APP_FIFO_debctrl1(_slice)           (UMAC_BASE(_slice) + 0xC504)  /* 0x3141*/
#define UMAC_APP_FIFO_fint0(_slice)              (UMAC_BASE(_slice) + 0xC5C0)  /* 0x3170*/
#define UMAC_APP_FIFO_spare1(_slice)             (UMAC_BASE(_slice) + 0xC7F8)  /* 0x31FE*/
#define UMAC_APP_FIFO_spare0(_slice)             (UMAC_BASE(_slice) + 0xC7FC)  /* 0x31FF*/

/* interrupts - _reg_idx in 0..14 */
/* to convert host side of INTERRUPT register address to line side of INTERRUPT register address  */
/* added difference of addresses of subunits interrupts1 and interrupts0 (0x2BC00 - 0x26000)      */
#define UMAC_INTERRUPT_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_INTERRUPT_setintenable(_slice, _reg_idx)   (UMAC_BASE(_slice) + 0x6000 + (_reg_idx * 8))
#define UMAC_INTERRUPT_clrintenable(_slice, _reg_idx)   (UMAC_BASE(_slice) + 0x6004 + (_reg_idx * 8))
#define UMAC_INTERRUPT_intstat(_slice, _reg_idx)        (UMAC_BASE(_slice) + 0x6080 + (_reg_idx * 8))
#define UMAC_INTERRUPT_intclr(_slice, _reg_idx)         (UMAC_BASE(_slice) + 0x6084 + (_reg_idx * 8))
#define UMAC_INTERRUPT_intraw(_slice, _reg_idx)         (UMAC_BASE(_slice) + 0x6100 + (_reg_idx * 8))

/* serdesmux */
/* to convert host side of SERDES_MUX register address to line side of SERDES_MUX register address  */
/* added difference of addresses of subunits serdesmux1 and serdesmux0 (0x2B800 - 0x25C00)      */
#define UMAC_SERDES_MUX_LINE_REG_ADDR(_host_reg_addr) (_host_reg_addr + 0x5C00)

#define UMAC_SERDES_MUX_serdessigokovrd(_slice)          (UMAC_BASE(_slice) + 0x5C00)
#define UMAC_SERDES_MUX_serdeslpbk(_slice)               (UMAC_BASE(_slice) + 0x5C04)
#define UMAC_SERDES_MUX_laneremaprx0(_slice)             (UMAC_BASE(_slice) + 0x5C08)
#define UMAC_SERDES_MUX_fifosts0(_slice, _reg_idx)       (UMAC_BASE(_slice) + 0x5CC0 + (_reg_idx * 4))
#define UMAC_SERDES_MUX_fifoerrsts(_slice)               (UMAC_BASE(_slice) + 0x5D00)
#define UMAC_SERDES_MUX_serdessynclpbk(_slice)           (UMAC_BASE(_slice) + 0x5D04)
#define UMAC_SERDES_MUX_pacersel(_slice)                 (UMAC_BASE(_slice) + 0x5D08)
#define UMAC_SERDES_MUX_pacerdiv(_slice, _reg_idx)       (UMAC_BASE(_slice) + 0x5D0C + (_reg_idx * 4))
#define UMAC_SERDES_MUX_txprbscfg(_slice, _reg_idx)      (UMAC_BASE(_slice) + 0x5D2C + (_reg_idx * 4))
#define UMAC_SERDES_MUX_rxprbscfg(_slice, _reg_idx)      (UMAC_BASE(_slice) + 0x5D4C + (_reg_idx * 4))
#define UMAC_SERDES_MUX_rxprbserrcnt(_slice, _reg_idx)   (UMAC_BASE(_slice) + 0x5D6C + (_reg_idx * 4))
#define UMAC_SERDES_MUX_txerrorcfg(_slice, _reg_idx)     (UMAC_BASE(_slice) + 0x5D8C + (_reg_idx * 4))
#define UMAC_SERDES_MUX_fint0(_slice)                    (UMAC_BASE(_slice) + 0x5DC0)
#define UMAC_SERDES_MUX_laneremaptx0(_slice)             (UMAC_BASE(_slice) + 0x5E08)

/* DFX Server registers */
/*/Reset and Initialization/DFX/Units/DFX Server Registers/Device General Control 0*/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#define TEMPERATURE_SENSOR_28NM_CONTROL_MSB     0x800F8074
#define TEMPERATURE_SENSOR_STATUS               0x800F8078
#define REG_ADDR_DFX_SERVER_GEN_CONTROL0        0x800F8250
#else
#define TEMPERATURE_SENSOR_28NM_CONTROL_MSB     0xA00F8074
#define TEMPERATURE_SENSOR_STATUS               0xA00F8078
#define REG_ADDR_DFX_SERVER_GEN_CONTROL0        0xA00F8250
#endif



/* CM3 coprocessor related */
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#define REG_ADDR_CM3_GLOBAL_CONFIGURATION    0x30000500
#define REG_ADDR_CM3_MEMORY_BASE             0x30080000
/*<MG_IP> MG_IP/Units/MG_IP/MG Registers/MG Miscellaneous/Device ID*/
#define REG_ADDR_MG_DEV_ID                   0x3000004C
#else
#define REG_ADDR_CM3_GLOBAL_CONFIGURATION    0x60000500
#define REG_ADDR_CM3_MEMORY_BASE             0x60080000
/*<MG_IP> MG_IP/Units/MG_IP/MG Registers/MG Miscellaneous/Device ID*/
#define REG_ADDR_MG_DEV_ID                   0x6000004C
#endif

/* * HW Semaphore table*/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#define REG_ADDR_HW_SEMAPHORE_TABLE_BASE         0x30000800
#define REG_ADDR_HW_LAST_ACCESS_TIMESTAMP        0x30000040
#define REG_ADDR_MG_INTERNAL_INTERRUPT_CAUSE     0x30000038
#define REG_ADDR_MG_INTERNAL_INTERRUPT_MASK      0x3000003C
#define REG_ADDR_GLOBAL_INTERRUPT_SUMMARY_CAUSE  0x30000030
#define REG_ADDR_GLOBAL_INTERRUPT_SUMMARY_MASK   0x30000034
#define REG_ADDR_MG_CM3_TO_HOST_DOORBELL         0x30000538
#else
#define REG_ADDR_HW_SEMAPHORE_TABLE_BASE         0x60000800
#define REG_ADDR_HW_LAST_ACCESS_TIMESTAMP        0x60000040
#define REG_ADDR_MG_CM3_TO_HOST_DOORBELL         0x60000538
#endif

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif


