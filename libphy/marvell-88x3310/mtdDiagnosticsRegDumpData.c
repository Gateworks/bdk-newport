/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains global data for doing register dumps
of registers for the Marvell 88X32X0, 88X33X0, 88E20X0 and 
88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdDiagnosticsRegDumpData.h"
#include <stdio.h>

#if MTD_CUNIT_REG_DATA
const MTD_MDIO_ADDR_TYPE cUnitRegData[MTD_CUNIT_NUM_REGS] = {
{31,0xF000}, /*Mode Configuration*/
{31,0xF001}, /*Port Control*/
{31,0xF002}, /*RCLK Clock Control*/
{31,0xF003}, /*EEE Buffer Control Register 1, internal use only */
{1,0xC033},  /*EEE Buffer Control Register 1 */    
{31,0xF004}, /*EEE Buffer Control Register 2*/
{31,0xF005}, /*EEE Buffer Control Register 3*/
{31,0xF006}, /*EEE Buffer Control Register 4*/
{31,0xF010}, /*GPIO Interrupt Enable*/
{31,0xF011}, /*GPIO Interrupt Status*/
{31,0xF011}, /*LH */    
{31,0xF012}, /*GPIO Data*/
{31,0xF013}, /*GPIO Tristate Control*/
{31,0xF014}, /*GPIO Interrupt Type 1*/
{31,0xF015}, /*GPIO Interrupt Type 2*/
{31,0xF020}, /*LED[0] Control*/
{31,0xF021}, /*LED[1] Control*/
{31,0xF022}, /*LED[2] Control*/
{31,0xF023}, /*LED[3] Control*/
{31,0xF026}, /*LED Mixing Control*/
{31,0xF027}, /*LED Timer Control*/
{31,0xF040}, /*Port Interrupt Status*/
{31,0xF041}, /*Global Interrupt Control*/
{31,0xF042}, /*Global Interrupt Status*/
{31,0xF043}, /*Port Interrupt Mask*/
{31,0xF06B}, /*Magic Packet MAC Addr LSB*/
{31,0xF06C}, /*Magic Packet MAC Addr ISB*/
{31,0xF06D}, /*Magic Packet MAC Addr MSB*/
{31,0xF06E}, /*WOL Control Register*/
{31,0xF06F}, /*WOL Status Register*/
{31,0xF088}, /*Reference Clock Control*/
{31,0xF089}, /*Temperature Sensor 1*/
{31,0xF089}, /*LH */
{31,0xF08a}, /*Temperature Sensor 2*/
{31,0xF08c}, /*Temperature Sensor 3*/
{31,0xF092}, /*DVM Digital Register1*/
{31,0xF093}, /*DVM Digital Register2*/
{31,0xF094}, /*DVM Digital Register3*/
{31,0xF095}, /*DVM Digital Register4*/
{31,0xF096}, /*DVM Digital Register5*/
{31,0xF097}, /*DVM Digital Register6*/
{31,0xF098}, /*DVM Digital Register7*/
{31,0xF099}, /*DVM Digital Register8*/
{31,0xF09A}, /*DVM Digital Register9*/
{31,0xF09B}, /*DVM Digital Register10*/
{31,0xF09C}, /*DVM Digital Register11*/
{31,0xF09D}, /*DVM Digital Register12*/
{31,0xF09E}, /*DVM Digital Register13*/
{31,0xF09F}, /*DVM Digital Register14*/
{31,0xF0A0}, /*DVM Digital Register15*/
{31,0xF0A3}, /*DVM Digital Register16*/
{31,0xF0A4}, /*DVM Digital Register17*/
{31,0xF0A5}, /*DVM Digital Register18*/
{31,0xF0A6}, /*DVM Digital Register19*/
{31,0xF0A7}, /*DVM Digital Register1a*/
{1,0xC04A},  /*port control Register. E21X0 only*/
{31,0xF007}, /*Port control2 Register.E21X0 only*/
{31,0xF00F}, /*Local and remote fault control Register.E21X0 only*/
{31,0xF03A}, /*Serial LED Control Register.E21X0 only*/
{31,0xF0A8}, /*Device Max Speed limit control Register. Not for X32X0*/
/* Following Rate Match Registers are not applicable for X32X0 device */
{31,0xF880}, /*Rate_Matching_FIFO Register*/
{31,0xF881}, /*Rate_Matching_FIFO Register*/
{31,0xF882}, /*Rate_Matching_FIFO Register*/
{31,0xF883}, /*Rate_Matching_FIFO Register*/
{31,0xF885}, /*Rate_Matching_FIFO Register*/
{31,0xF886}, /*Rate_Matching_FIFO Register*/
{31,0xF887}, /*Rate_Matching_FIFO Register*/
{31,0xF888}, /*Rate_Matching_FIFO Register*/
{31,0xF889}, /*Rate_Matching_FIFO Register*/
{31,0xF88A}, /*Rate_Matching_FIFO Register*/
{31,0xF88B}, /*Rate_Matching_FIFO Register*/
{31,0xF88C}, /*Rate_Matching_FIFO Register*/
{31,0xF88D}, /*Rate_Matching_FIFO Register*/
{31,0xF88E}, /*Rate_Matching_FIFO Register*/
{31,0xF88F}, /*Rate_Matching_FIFO Register*/
{31,0xF890}, /*Rate_Matching_FIFO Register*/
{31,0xF891}, /*Rate_Matching_FIFO Register*/
{31,0xF892}, /*Rate_Matching_FIFO Register*/
{31,0xF893}, /*Rate_Matching_FIFO Register*/
{31,0xF894}, /*Rate_Matching_FIFO Register*/
{31,0xF895}, /*Rate_Matching_FIFO Register*/
{31,0xF896}, /*Rate_Matching_FIFO Register*/
{31,0xF897}, /*Rate_Matching_FIFO Register*/
{31,0xF898}, /*Rate_Matching_FIFO Register*/
{31,0xF899}, /*Rate_Matching_FIFO Register*/
{31,0xF89A}, /*Rate_Matching_FIFO Register*/
{31,0xF89B}, /*Rate_Matching_FIFO Register*/
{31,0xF89C}, /*Rate_Matching_FIFO Register*/
{31,0xF89D}};/*Rate_Matching_FIFO Register*/
#endif

#if MTD_F2R_REG_DATA
const MTD_MDIO_ADDR_TYPE f2rRegData[MTD_F2R_NUM_REGS] = {
{31,0xF800}, /*Frame to Register PHY DA[15:0]*/
{31,0xF801}, /*Frame to Register PHY DA[31:16]*/
{31,0xF802}, /*Frame to Register PHY DA[47:32]*/
{31,0xF803}, /*Frame to Register PHY SA[15:0]*/
{31,0xF804}, /*Frame to Register PHY SA[31:16]*/
{31,0xF805}, /*Frame to Register PHY SA[47:32]*/
{31,0xF806}, /*Frame to Register PHY TYPE*/
{31,0xF807}}; /*F2R Page Extension Register*/
#endif

#if MTD_HUNIT_10GBASER_REG_DATA
const MTD_MDIO_ADDR_TYPE hUnit10grRegData[MTD_HUNIT_10GBASER_NUM_REGS] = {
{4,0x1000}, /*10GBASE-R PCS Control 1*/
{4,0x1001}, /*10GBASE-R PCS Status 1*/
{4,0x1001}, /*LH/LL and OR of bits in 4.1008*/    
{4,0x1002}, /*PCS Device Identifier 1*/
{4,0x1003}, /*PCS Device Identifier 2*/
{4,0x1004}, /*PCS Speed Ability*/
{4,0x1005}, /*PCS Devices In Package 1*/
{4,0x1006}, /*PCS Devices In Package 2*/
{4,0x1008}, /*10GBASE-R PCS Status 2*/
{4,0x1008}, /*LH */    
{4,0x100E}, /*PCS Package Identifier 1*/
{4,0x100F}, /*PCS Package Identifier 2*/
{4,0x1020}, /*10GBASE-R PCS Status 1*/
{4,0x1021}, /*10GBASE-R PCS Status 2*/
{4,0x1021}, /*LH/LL*/    
{4,0x1022}, /*10GBASE-R PCS Test Pattern Seed A 0*/
{4,0x1023}, /*10GBASE-R PCS Test Pattern Seed A 1*/
{4,0x1024}, /*10GBASE-R PCS Test Pattern Seed A 2*/
{4,0x1025}, /*10GBASE-R PCS Test Pattern Seed A 3*/
{4,0x1026}, /*10GBASE-R PCS Test Pattern Seed B 0*/
{4,0x1027}, /*10GBASE-R PCS Test Pattern Seed B 1*/
{4,0x1028}, /*10GBASE-R PCS Test Pattern Seed B 2*/
{4,0x1029}, /*10GBASE-R PCS Test Pattern Seed B 3*/
{4,0x102A}, /*10GBASE-R PCS Test Pattern Control*/
{4,0x102B}, /*10GBASE-R PCS Test Pattern Error Counter*/
{4,0x9000}, /*10GBASE-R Interrupt Enable Register*/
{4,0x9001}, /*10GBASE-R Interrupt Status Register*/
{4,0x9001}, /*LH */    
{4,0x9002}}; /*10GBASE-R  PCS Real Time Status Register*/
#endif

#if MTD_HUNIT_1000BX_REG_DATA
const MTD_MDIO_ADDR_TYPE hUnit1000bxRegData[MTD_HUNIT_1000BX_NUM_REGS] = {
{4,0x2000}, /*1000BASE-X/SGMII Control Register*/
{4,0x2001}, /*1000BASE-X/SGMII Status Register*/
{4,0x2001}, /*LH/LL */    
{4,0x2002}, /*PHY Identifier*/
{4,0x2003}, /*PHY Identifier*/
{4,0x2004}, /*SGMII (Media side) Auto-Negotiation Advertisement Register*/
{4,0x2005}, /*SGMII (Media side) Link Partner Ability Register*/
{4,0x2006}, /*1000BASE-X Auto-Negotation Expansion Register*/
{4,0x2007}, /*1000BASE-X Next Page Transmit Register*/
{4,0x2008}, /*1000BASE-X Link Partner Next Page Register*/
{4,0x200F}, /*Extended Status Register*/
{4,0xA000}, /*1000BASE-X Timer Mode Select Register*/
{4,0xA001}, /*1000BASE-X Interrupt Enable Register*/
{4,0xA002}, /*1000BASE-X Interrupt Status Register*/
{4,0xA003}, /*1000ASE-X PHY Specific Status Register*/
{4,0xA004}}; /*"1000ASE-X RX Skew Register (Feature available in 3220}, // 3240 A0}, // not in 3240 Z1)"*/
#endif

#if MTD_HUNIT_COMMON_REG_DATA
const MTD_MDIO_ADDR_TYPE hUnitCommonRegData[MTD_HUNIT_COMMON_NUM_REGS] = {
{4,0xF003}, /*SERDES Control Register 1*/
{4,0xF00A}, /*FIFO and CRC Interrupt Enable*/
{4,0xF00B}, /*FIFO and CRC Interrupt Status*/
{4,0xF00B}, /*LH */    
{4,0xF00C}, /*PPM FlFO Control 1*/
{4,0xF010}, /*Packet Generation Control 1*/
{4,0xF011}, /*Packet Generation Control 2*/
{4,0xF012}, /*Initial Payload 0-1/Packet Generation*/
{4,0xF013}, /*Initial Payload 2-3/Packet Generation*/
{4,0xF016}, /*Packet Generation Length*/
{4,0xF017}, /*Packet Generation Burst Sequence*/
{4,0xF018}, /*Packet Generation IPG*/
{4,0xF01B}, /*Transmit Packet Counter [15:0]*/
{4,0xF01C}, /*Transmit Packet Counter [31:16]*/
{4,0xF01D}, /*Transmit Packet Counter [47:32]*/
{4,0xF01E}, /*Transmit Byte Counter [15:0]*/
{4,0xF01F}, /*Transmit Byte Counter [31:16]*/
{4,0xF020}, /*Transmit Byte Counter [47:32]*/
{4,0xF021}, /*Receive Packet Counter [15:0]*/
{4,0xF022}, /*Receive Packet Counter [31:16]*/
{4,0xF023}, /*Receive Packet Counter [47:32]*/
{4,0xF024}, /*Receive Byte Count [15:0]*/
{4,0xF025}, /*Receive Byte Count [31:16]*/
{4,0xF026}, /*Receive Byte Count [47:32]*/
{4,0xF027}, /*Receive Packet Error Count [15:0]*/
{4,0xF028}, /*Receive Packet Error Count [31:16]*/
{4,0xF029}, /*Receive Packet Error Count [47:32]*/
{4,0xF02a}, /*Link_drop Count [15:0]*/
{4,0xF030}, /*PRBS Control*/
{4,0xF031}, /*PRBS Symbol Tx Counter [15:0]*/
{4,0xF032}, /*PRBS Symbol Tx Counter [31:16]*/
{4,0xF033}, /*PRBS Symbol Tx Counter [47:32]*/
{4,0xF034}, /*PRBS Symbol Rx Counter [15:0]*/
{4,0xF035}, /*PRBS Symbol Rx Counter [31:16]*/
{4,0xF036}, /*PRBS Symbol Rx Counter [47:32]*/
{4,0xF037}, /*PRBS Error Count [15:0]*/
{4,0xF038}, /*PRBS Error Count [31:16]*/
{4,0xF039}, /*PRBS Error Count [47:32]*/
{4,0xF040}, /*PRBS Control */
{4,0xF041}, /*PRBS Elapse Time Counter */
{4,0xF042}, /*PRBS Master Error Counter[15:0] */
{4,0xF043}, /*PRBS Master Error Counter[31:16] */
{4,0xF044}, /*PRBS Master Error Counter[47:32] */
{4,0xF045}, /*PRBS Intermediate Error Counter[15:0] */
{4,0xF046}, /*PRBS Intermediate Error Counter[31:16] */
{4,0xF047}}; /*PRBS Intermediate Error Counter[34:32] */
#endif

#if MTD_HUNIT_RXAUI_REG_DATA
const MTD_MDIO_ADDR_TYPE hUnitRxauiRegData[MTD_HUNIT_RXAUI_NUM_REGS] = {
{4,0x0000}, /*10GBASE-X4 PCS Control 1*/
{4,0x0001}, /*10GBASE-X4 PCS Status 1*/
{4,0x0001}, /*LH/LL and OR of bits in 4.0008*/    
{4,0x0002}, /*PCS Device Identifier 1*/
{4,0x0003}, /*PCS Device Identifier 2*/
{4,0x0004}, /*PCS Speed Ability*/
{4,0x0005}, /*PCS Devices In Package 1*/
{4,0x0006}, /*PCS Devices In Package 2*/
{4,0x0008}, /*10GBASE-X4 PCS Status 2*/
{4,0x0008}, /*LH */    
{4,0x000E}, /*PCS Package Identifier 1*/
{4,0x000F}, /*PCS Package Identifier 2*/
{4,0x0018}, /*10GBASE-X Lane Status*/
{4,0x0019}, /*10GBASE-X Test Control Register*/
{4,0x8000}, /*10GBASE-X4 Control*/
{4,0x8001}, /*10GBASE-X4 Interrupt Enable 1*/
{4,0x8002}, /*10GBASE-X4 Interrupt Enable 2*/
{4,0x8003}, /*10GBASE-X4 Interrupt Status 1*/
{4,0x8003}, /*LH */    
{4,0x8004}, /*10GBASE-X4 Interrupt Status 2*/
{4,0x8004}, /*LH */    
{4,0x8006}, /*10GBASE-X4 Real Time Status Register 2*/
{4,0x8010}, /*10GBASE-X4 Random Sequence Control*/
{4,0x8011}, /*10GBASE-X4 Jitter Packet Transmit Counter LSB*/
{4,0x8012}, /*10GBASE-X4 Jitter Packet Transmit Counter MSB*/
{4,0x8013}, /*10GBASE-X4 Jitter Packet Received Counter LSB*/
{4,0x8014}, /*10GBASE-X4 Jitter Packet Received Counter MSB*/
{4,0x8015}, /*10GBASE-X4 Jitter Pattern Error Counter LSB*/
{4,0x8016}}; /*10GBASE-X4 Jitter Pattern Error Counter MSB*/
#endif

#if MTD_TUNIT_MMD1_REG_DATA
const MTD_MDIO_ADDR_TYPE tUnitMmd1RegData[MTD_TUNIT_MMD1_NUM_REGS] = {
{1,0x0000}, /*PMA/PMD Control 1*/
{1,0x0001}, /*PMA/PMD Status 1*/
{1,0x0001}, /*LL also fault based on OR of LH in 1.0008 */
{1,0x0002}, /*PMA/PMD Device Identifier 1*/
{1,0x0003}, /*PMA/PMD Device Identifier 2*/
{1,0x0004}, /*PMA/PMD Speed Ability*/
{1,0x0005}, /*PMA/PMD Devices In Package 1*/
{1,0x0006}, /*PMA/PMD Devices In Package 2*/
{1,0x0007}, /*10G PMA/PMD Control 2*/
{1,0x0008}, /*10G PMA/PMD Status 2*/
{1,0x0008}, /*LH */
{1,0x0009}, /*10G PMA Transmit Disable*/
{1,0x000A}, /*10G PMA/PMD Signal Detect*/
{1,0x000B}, /*PMA/PMD Extended Ability*/
{1,0x000E}, /*PMA/PMD Package Identifier 1*/
{1,0x000F}, /*PMA/PMD Package Identifier 2*/
{1,0x0081}, /*Status Register Valid*/
{1,0x0082}, /*10G Pair Swap and Polarity*/
{1,0x0083}, /*10GBASE-T TX Power Level Setting*/
{1,0x0084}, /*10GBASE-T Test Mode*/
{1,0x0085}, /*10GBASE-T SNR Operating Margin Channel A*/
{1,0x0086}, /*10GBASE-T SNR Operating Margin Channel B*/
{1,0x0087}, /*10GBASE-T SNR Operating Margin Channel C*/
{1,0x0088}, /*10GBASE-T SNR Operating Margin Channel D*/
{1,0x0089}, /*10GBASE-T Minimum Margin Channel A*/
{1,0x008A}, /*10GBASE-T Minimum Margin Channel B*/
{1,0x008B}, /*10GBASE-T Minimum Margin Channel C*/
{1,0x008C}, /*10GBASE-T Minimum Margin Channel D*/
{1,0x008D}, /*10GBASE-T RX Signal Power Channel A*/
{1,0x008E}, /*10GBASE-T RX Signal Power Channel B*/
{1,0x008F}, /*10GBASE-T RX Signal Power Channel C*/
{1,0x0090}, /*10GBASE-T RX Signal Power Channel D*/
{1,0x0091}, /*Skew Delay Channel B*/
{1,0x0092}, /*Skew Delay Channel C and D*/
{1,0x0093}, /*10GBASE-T Fast Retrain Status and Control*/
{1,0xC000}, /*XG Extended Control Register*/
{1,0xC001}, /*XG Extended Status Register*/
{1,0xC001}, /*LH */
{1,0xC003}, /*MDIO Test 1*/
{1,0xC004}, /*MDIO Test 2*/
{1,0xC005}, /*MDIO Test 3*/
{1,0xC006}, /*10G Interrupt Mask*/
{1,0xC007}, /*10G Interrupt Status*/
{1,0xC007}, /*LH */
{1,0xC008}, /*10G Misc Control/status*/
{1,0xC008}, /*LH */
{1,0xC00B}, /*Test Control*/
{1,0xC00C}, /*Test Status*/
{1,0xC00D}, /*Cable Diagnostics Control/Status*/
{1,0xC00E}, /*Cable Diagnostics Results 1*/
{1,0xC00F}, /*Cable Diagnostics Results 2*/
{1,0xC010}, /*Cable Diagnostics Results 3*/
{1,0xC011}, /*Firmware Revision 1*/
{1,0xC012}, /*Firmware Revision 1*/
{1,0xC031}, /*1G Misc Control*/
{1,0xC031}, /*NbaseT Downshift Control 88X33x0/E20x0/E21x0 devices only */
{1,0xC031}, /*NbaseT Downshift Status 88X33x0/E20x0/E21x0 devices only */
{1,0xC050}, /*Boot Status*/
{1,0xC055}, /*10G Link Drop Control*/
{1,0xC056}}; /*10G Link Drop Count*/
#endif
    
#if MTD_TUNIT_MMD3_REG_DATA
const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData[MTD_TUNIT_MMD3_NUM_REGS] = {
{3,0x0000}, /*PCS Control 1*/
{3,0x0001}, /*PCS Status 1*/
{3,0x0001}, /*LH/LL also OR of bits in 3.0008 */
{3,0x0002}, /*PCS Device Identifier 1*/
{3,0x0003}, /*PCS Device Identifier 2*/
{3,0x0004}, /*PCS Speed Ability*/
{3,0x0005}, /*PCS Devices In Package 1*/
{3,0x0006}, /*PCS Devices In Package 2*/
{3,0x0007}, /*PCS Control 2*/
{3,0x0008}, /*PCS Status 2*/
{3,0x0008}, /*LH */    
{3,0x000E}, /*PCS Package Identifier 1*/
{3,0x000F}, /*PCS Package Identifier 2*/
{3,0x0014}, /*EEE Capability*/
{3,0x0016}, /*EEE Wake Error Counter*/
{3,0x0020}, /*10GBASE-T PCS Status 1*/
{3,0x0021}, /*10GBASE-T PCS Status 2*/
{3,0x0021}}; /*LH/LL*/
#endif
    
#if MTD_TUNIT_MMD3_REG_DATA2
const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData2[MTD_TUNIT_MMD3_2_NUM_REGS] = {
{3,0xDC8B}, /*10G PPM Fifo Status*/
{3,0xDC8C}, /*10G PPM Fifo Control*/
{3,0xDC90}, /*10G Packet Generation Control*/
{3,0xDC91}, /*10G Packet Generation Control 1*/
{3,0xDC92}, /*10G Packet Generation Initial Data MSB*/
{3,0xDC93}, /*10G Packet Generation Initial Data LSB*/
{3,0xDC94}, /*10G Packet Generation Length*/
{3,0xDC95}, /*10G Packet Generation Burst Sequence*/
{3,0xDC96}, /*10G Packet Generation IPG*/
{3,0xDC97}, /*10G Transmit Packet Counter LSB*/
{3,0xDC98}, /*10G Transmit Packet Counter Mid-16bit*/
{3,0xDC99}, /*10G Transmit Packet Counter MSB*/
{3,0xDC9A}, /*10G Transmit Byte Counter LSB*/
{3,0xDC9B}, /*10G Transmit Byte Counter Mid-16bit*/
{3,0xDC9C}, /*10G Transmit Byte Counter MSB*/
{3,0xDCA0}, /*10G Packet Checker Control*/
{3,0xDCA1}, /*10G Receive Packet Counter LSB*/
{3,0xDCA2}, /*10G Receive Packet Counter Mid-16bit*/
{3,0xDCA3}, /*10G Receive Packet Counter MSB*/
{3,0xDCA4}, /*10G Receive Byte Counter LSB*/
{3,0xDCA5}, /*10G Receive Byte Counter Mid-16bit*/
{3,0xDCA6}, /*10G Receive Byte Counter MSB*/
{3,0xDCA7}, /*10G Receive Error Counter LSB*/
{3,0xDCA8}, /*10G Receive Error Counter Mid-16bit*/
{3,0xDCA9}}; /*10G Receive Error Counter MSB*/
#endif
    
#if MTD_TUNIT_MMD3_REG_DATA3
const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData3[MTD_TUNIT_MMD3_3_NUM_REGS] = {
{3,0x8000}, /*Copper Specific Control Register 1*/
{3,0x8001}, /*Copper Specific Control Register 2*/
{3,0x8002}, /*Copper Specific Control Register 3*/
{3,0x8003}, /*Down Shift Control*/
{3,0x8008}, /*Copper Specific Status Register 1*/
{3,0x8009}, /*Copper Specific Status Register 2*/
{3,0x800A}, /*Receive Error Counter LSB*/
{3,0x800B}, /*Receive Error Counter MSB*/
{3,0x8010}, /*Copper Specific Interrupt Enable Register 1*/
{3,0x8011}, /*Copper Specific Interrupt Register 1*/
{3,0x8011}, /*LH */
{3,0x8012}, /*Copper Specific Interrupt Enable Register 2*/
{3,0x8013}, /*Copper Specific Interrupt Register 2*/
{3,0x8013}, /*LH */    
{3,0x8030}, /*Packet Generation Control*/
{3,0x8031}, /*XOR Mask 0-1/Packet Generation LSB*/
{3,0x8032}, /*XOR Mask 2-3/Packet Generation MSB*/
{3,0x8033}, /*Packet Generation Length*/
{3,0x8034}, /*Packet Generation Burst Sequence*/
{3,0x8035}, /*Packet Generation IPG*/
{3,0x8036}, /*Transmit Packet Counter LSB*/
{3,0x8037}, /*Transmit Packet Counter MSB*/
{3,0x8038}, /*Transmit Byte Counter LSB*/
{3,0x8039}, /*Transmit Byte Counter MSB*/
{3,0x803A}, /*Receive Packet Counter LSB*/
{3,0x803B}, /*Receive Packet Counter MSB*/
{3,0x803C}, /*Receive Byte Count LSB*/
{3,0x803D}, /*Receive Byte Count MSB*/
{3,0x803E}, /*Receive Packet Error Count LSB*/
{3,0x803F}, /*Receive Packet Error Count MSB*/
{3,0x8182}, /*1G Pair Swap and Polarity*/
{3,0x8EB8}}; /*Analog Registers: PTPLL_UREG*/
#endif
    
#if MTD_TUNIT_MMD7_REG_DATA
const MTD_MDIO_ADDR_TYPE tUnitMmd7RegData[MTD_TUNIT_MMD7_NUM_REGS] = {
{7,0x0000}, /*Auto-Negotiation Control*/
{7,0x0001}, /*Auto-Negotiation Status*/
{7,0x0001}, /*LH/LL */    
{7,0x0002}, /*Auto-Negotiation Device Identifier 1*/
{7,0x0003}, /*Auto-Negotiation Device Identifier 2*/
{7,0x0005}, /*Auto-Negotiation Devices In Package 1*/
{7,0x0006}, /*Auto-Negotiation Devices In Package 2*/
{7,0x000E}, /*Auto-Negotiation Package Identifier 1*/
{7,0x000F}, /*Auto-Negotiation Package Identifier 2*/
{7,0x0010}, /*Auto-Negotiation Advertisement Register 1*/
{7,0x0013}, /*Link Partner Base Page Ability Register 1*/
{7,0x0016}, /*Next Page Transmit Register / Extended Next Page Transmit Register*/
{7,0x0017}, /*Extended Next Page Transmit Register Unformatted Code Field U0 to U15*/
{7,0x0018}, /*Extended Next Page Transmit Register Unformatted Code Field U16 to U31*/
{7,0x0019}, /*Link Partner Next Page Register / Link Partner Extended Next Page Ability Register*/
{7,0x001A}, /*Link Partner Extended Next Page Ability Register Unformatted Code Field U0 to U15*/
{7,0x001B}, /*Link Partner Extended Next Page Ability Register Unformatted Code Field U16 to U31*/
{7,0x0020}, /*10GBASE-T Auto-Negotiation Control Register*/
{7,0x0021}, /*10GBASE-T Auto-Negotiation Status Register*/
{7,0x0021}, /*LH */
{7,0x003C}, /*EEE Advertisement Register*/
{7,0x003D}, /*Link Partner EEE Advertisement Register*/
{7,0x003E}, /*EEE Advertisement 2 Register 2.5/5G, only valid for 88X33X0 devices*/
{7,0x003F}, /*Link Partner EEE Ability 2 Register 2.5/5G only valid for 88X33X0 devices*/
{7,0x0040}, /*MGbase-T AN Control 2 Register (2.5/5G), only valid for 88X33X0 devices*/
{7,0x0041}, /*MGbase-T AN Status 2 Register (2.5/5G), only valid for 88X33X0 devices */    
{7,0x8000}, /*10/100/1000 Auto-Negotiation Control/Status Register*/
{7,0x8000}, /*LH */    
{7,0x8001}, /*10/100/1000 Auto-Negotiation Status Register*/   
{7,0x8001}, /*LH */
{7,0x8002}, /*10/100/1000 Ability Register*/
{7,0x8004}, /*Internal AN control register*/
{7,0x8008}, /*Marvell Advertisement Register 2(user defined message 5 oui code[15:0]])*/
{7,0x8009}, /*Marvell Advertisement Register 2(user defined message 5 oui code[23:16])*/
{7,0x800A}, /*Marvell Advertisement Register 1(user defined message 5 user code[15:0])*/
{7,0x800B}, /*Marvell Advertisement Register 2(user defined message 5 user code[19:16])*/
{7,0x800C}, /*Marvell negotiated fast retrain  Advertisement Register*/
{7,0x800D}, /*Marvell negotiated fast retrain  Status Register*/
{7,0x800F}}; /* Serdes status/control */
#endif
    
#if MTD_XUNIT_10GBASER_REG_DATA
const MTD_MDIO_ADDR_TYPE xUnit10grRegData[MTD_XUNIT_10GBASER_NUM_REGS] = {
{3,0x1000}, /*10GBASE-R PCS Control 1*/
{3,0x1001}, /*10GBASE-R PCS Status 1*/    
{3,0x1001}, /*LH/LL and OR of bits in 3.1008 */
{3,0x1002}, /*PCS Device Identifier 1*/
{3,0x1003}, /*PCS Device Identifier 2*/
{3,0x1004}, /*PCS Speed Ability*/
{3,0x1005}, /*PCS Devices In Package 1*/
{3,0x1006}, /*PCS Devices In Package 2*/
{3,0x1008}, /*10GBASE-R PCS Status 2*/
{3,0x1008}, /*LH */    
{3,0x100E}, /*PCS Package Identifier 1*/
{3,0x100F}, /*PCS Package Identifier 2*/
{3,0x1020}, /*10GBASE-R PCS Status 1*/
{3,0x1021}, /*10GBASE-R PCS Status 2*/
{3,0x1021}, /*LH/LL */    
{3,0x1022}, /*10GBASE-R PCS Test Pattern Seed A 0*/
{3,0x1023}, /*10GBASE-R PCS Test Pattern Seed A 1*/
{3,0x1024}, /*10GBASE-R PCS Test Pattern Seed A 2*/
{3,0x1025}, /*10GBASE-R PCS Test Pattern Seed A 3*/
{3,0x1026}, /*10GBASE-R PCS Test Pattern Seed B 0*/
{3,0x1027}, /*10GBASE-R PCS Test Pattern Seed B 1*/
{3,0x1028}, /*10GBASE-R PCS Test Pattern Seed B 2*/
{3,0x1029}, /*10GBASE-R PCS Test Pattern Seed B 3*/
{3,0x102A}, /*10GBASE-R PCS Test Pattern Control*/
{3,0x102B}, /*10GBASE-R PCS Test Pattern Error Counter*/
{3,0x9000}, /*10GBASE-R Interrupt Enable Register*/
{3,0x9001}, /*10GBASE-R Interrupt Status Register*/
{3,0x9001}, /*LH */    
{3,0x9002}}; /*10GBASE-R  PCS Real Time Status Register*/
#endif
    
#if MTD_XUNIT_1000BX_REG_DATA
const MTD_MDIO_ADDR_TYPE xUnit1000bxRegData[MTD_XUNIT_1000BX_NUM_REGS] = {
{3,0x2000}, /*1000BASE-X/SGMII Control Register*/
{3,0x2001}, /*1000BASE-X/SGMII Status Register*/
{3,0x2001}, /*LH/LL */    
{3,0x2002}, /*PHY Identifier*/
{3,0x2003}, /*PHY Identifier*/
{3,0x2004}, /*1000BASE-X Auto-Negotiation Advertisement Register*/
{3,0x2004}, /*SGMII (System side) Auto-Negotiation Advertisement Register*/
{3,0x2005}, /*1000BASE-X Link Partner Ability Register*/
{3,0x2005}, /*SGMII (System side) Link Partner Ability Register*/
{3,0x2006}, /*1000BASE-X Auto-Negotation Expansion Register*/
{3,0x2006}, /*LH */    
{3,0x2007}, /*1000BASE-X Next Page Transmit Register*/
{3,0x2008}, /*1000BASE-X Link Partner Next Page Register*/
{3,0x200F}, /*Extended Status Register*/
{3,0xA000}, /*1000BASE-X Timer Mode Select Register*/
{3,0xA001}, /*1000BASE-X Interrupt Enable Register*/
{3,0xA002}, /*1000BASE-X Interrupt Status Register*/
{3,0xA002}, /*LH */    
{3,0xA003}, /*1000ASE-X PHY Specific Status Register*/
{3,0xA003}, /*LH */    
{3,0xA004}}; /*"1000ASE-X RX Skew Register (Feature available in 3220}, // 3240 A0}, // not in 3240 Z1)"*/
#endif
    
#if MTD_XUNIT_COMMON_REG_DATA
const MTD_MDIO_ADDR_TYPE xUnitCommonRegData[MTD_XUNIT_COMMON_NUM_REGS] = {
{3,0xF003}, /*SERDES Control Register 1*/
{3,0xF00A}, /*FIFO and CRC Interrupt Enable*/
{3,0xF00B}, /*FIFO and CRC Interrupt Status*/
{3,0xF00B}, /*LH */
{3,0xF00C}, /*PPM FlFO Control 1*/
{3,0xF010}, /*Packet Generation Control 1*/
{3,0xF011}, /*Packet Generation Control 2*/
{3,0xF012}, /*Initial Payload 0-1/Packet Generation*/
{3,0xF013}, /*Initial Payload 2-3/Packet Generation*/
{3,0xF016}, /*Packet Generation Length*/
{3,0xF017}, /*Packet Generation Burst Sequence*/
{3,0xF018}, /*Packet Generation IPG*/
{3,0xF01B}, /*Transmit Packet Counter [15:0]*/
{3,0xF01C}, /*Transmit Packet Counter [31:16]*/
{3,0xF01D}, /*Transmit Packet Counter [47:32]*/
{3,0xF01E}, /*Transmit Byte Counter [15:0]*/
{3,0xF01F}, /*Transmit Byte Counter [31:16]*/
{3,0xF020}, /*Transmit Byte Counter [47:32]*/
{3,0xF021}, /*Receive Packet Counter [15:0]*/
{3,0xF022}, /*Receive Packet Counter [31:16]*/
{3,0xF023}, /*Receive Packet Counter [47:32]*/
{3,0xF024}, /*Receive Byte Count [15:0]*/
{3,0xF025}, /*Receive Byte Count [31:16]*/
{3,0xF026}, /*Receive Byte Count [47:32]*/
{3,0xF027}, /*Receive Packet Error Count [15:0]*/
{3,0xF028}, /*Receive Packet Error Count [31:16]*/
{3,0xF029}, /*Receive Packet Error Count [47:32]*/
{3,0xF02a}, /*Link_drop Count [15:0]*/
{3,0xF030}, /*PRBS Control*/
{3,0xF031}, /*PRBS Symbol Tx Counter [15:0]*/
{3,0xF032}, /*PRBS Symbol Tx Counter [31:16]*/
{3,0xF033}, /*PRBS Symbol Tx Counter [47:32]*/
{3,0xF034}, /*PRBS Symbol Rx Counter [15:0]*/
{3,0xF035}, /*PRBS Symbol Rx Counter [31:16]*/
{3,0xF036}, /*PRBS Symbol Rx Counter [47:32]*/
{3,0xF037}, /*PRBS Error Count [15:0]*/
{3,0xF038}, /*PRBS Error Count [31:16]*/
{3,0xF039}, /*PRBS Error Count [47:32]*/
{3,0xF040}, /*PRBS Control */
{3,0xF041}, /*PRBS Elapse Time Counter */
{3,0xF042}, /*PRBS Master Error Counter[15:0] */
{3,0xF043}, /*PRBS Master Error Counter[31:16] */
{3,0xF044}, /*PRBS Master Error Counter[47:32] */
{3,0xF045}, /*PRBS Intermediate Error Counter[15:0] */
{3,0xF046}, /*PRBS Intermediate Error Counter[31:16] */
{3,0xF047}}; /*PRBS Intermediate Error Counter[34:32] */
#endif

MTD_STATUS mtdCopyRegsToBuf
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN const MTD_MDIO_ADDR_TYPE addrArray[],
    IN MTD_U16 addrArrayLength,
    IN MTD_8 dumpBuffer[],
    IN MTD_U16 dumpBufferLength,
    INOUT MTD_U16 *bufferOffset
)
{
    MTD_U16 addrIndex;
    MTD_U16 valueRead;
    int bytesWritten;

    for (addrIndex = 0; addrIndex < addrArrayLength; addrIndex++)
    {
        /* make sure there's room for the data to fit in dumpBuffer */
        if (((*bufferOffset) + MTD_SIZEOF_OUTPUT) > dumpBufferLength)
        {
            return MTD_FAIL; /* tried to read more than will fit in the dumpBuffer*/
        }

        /* read the register */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,addrArray[addrIndex].mmd,addrArray[addrIndex].reg,&valueRead));

        /* dump the port, address and value to the char buffer */
        bytesWritten = sprintf(&dumpBuffer[*bufferOffset],"%02d %02d.%04x=%04x\n", (int)port,
                               (int)addrArray[addrIndex].mmd, (int)addrArray[addrIndex].reg, (int)valueRead);

        MTD_DBG_INFO("%s", &dumpBuffer[*bufferOffset]);

        /* make sure the bytes written aren't larger than the expected size */
        if ((bytesWritten < 0) ||
            ((bytesWritten+1) > MTD_SIZEOF_OUTPUT))
        {   
            /* serious error, could cause writing past end of buffer */
            /* or sprintf returned an error */
            return MTD_FAIL;
        }
        else
        {
            /* update the index to point to the next available space */
            *bufferOffset += (MTD_U16)(bytesWritten + 1);
        }
    }

    return MTD_OK;
}















