/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data defines/data for
higher-level functions that are shared by the H Unit (host/interface
to the MAC) and the X Unit (media/fiber interface) for the 
Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdApiRegs.h"
#include "mtdHXunit.h"
#include "mtdHunit.h"
#include "mtdDiagnostics.h"

#define MTD_SERDES_CTRL_STATUS MTD_T_UNIT_AN,0x800F /* control/status for serdes initialization */

/******************************************************************************
 SERDES control (common)
******************************************************************************/

#define MTD_SERDES_SHORT_REACH (1)
#define MTD_SERDES_LONG_REACH  (0)
MTD_STATUS mtdSetSerdesOverrideReach
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL reachFlag
)
{
    const MTD_U8 bitPosition = ((HorXunit == MTD_H_UNIT) ? (10):(11));
    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,bitPosition,1,MTD_GET_BOOL_AS_BIT(reachFlag)));

    return MTD_OK;    
}

MTD_STATUS mtdGetSerdesOverrideReach
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *reachFlag
)
{
    const MTD_U8 bitPosition = ((HorXunit == MTD_H_UNIT) ? (10):(11));
    MTD_U16 temp;
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,bitPosition,1,&temp));

    MTD_CONVERT_UINT_TO_BOOL(temp, *reachFlag);

    return MTD_OK;        
}

#define MTD_SERDES_DISABLE_AUTO_INIT (1)
#define MTD_SERDES_ENABLE_AUTO_INIT  (0)
MTD_STATUS mtdSetSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL autoInitFlag
)
{    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,13,1,MTD_GET_BOOL_AS_BIT(autoInitFlag)));

    return MTD_OK;       
}

MTD_STATUS mtdGetSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *autoInitFlag
)
{
    MTD_U16 temp;

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,13,1,&temp));

    MTD_CONVERT_UINT_TO_BOOL(temp, *autoInitFlag);

    return MTD_OK;    
}

MTD_STATUS mtdRerunSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit
)
{
    const MTD_U16 bit12Value = ((HorXunit == MTD_H_UNIT) ? (1):(0));
    MTD_U16 temp,temp2,temp3;
    MTD_U16 waitCounter;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp));

    ATTEMPT(mtdHwSetRegFieldToWord(temp,7,13,3,&temp2));  /* override, disable, and execute bits set */
    ATTEMPT(mtdHwSetRegFieldToWord(temp2,bit12Value,12,1,&temp2)); /* set if this is H or X unit */

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_SERDES_CTRL_STATUS,temp2));

    /* wait for it to be done */
    waitCounter = 0;
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp3));
    while((temp3 & 0x8000) && (waitCounter < 100))
    {
        ATTEMPT(mtdWait(devPtr,1));
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp3));
        waitCounter++;
    }

    /* put it back only override and disable whether timed out or not */    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,13,2,temp));

    if (waitCounter >= 100)
    {
        return MTD_FAIL; /* execute timed out */
    }

    return MTD_OK;
    
}


MTD_STATUS mtdRerunSerdesAutoInitUseAutoMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    MTD_U16 temp,temp2,temp3;
    MTD_U16 waitCounter;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp));

    ATTEMPT(mtdHwSetRegFieldToWord(temp,1,15,1,&temp2));  /* execute bits and disable bits set */
    ATTEMPT(mtdHwSetRegFieldToWord(temp2,1,13,1,&temp2));

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_SERDES_CTRL_STATUS,temp2));

    /* wait for it to be done */
    waitCounter = 0;
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp3));
    while((temp3 & 0x8000) && (waitCounter < 100))
    {
        ATTEMPT(mtdWait(devPtr,1));
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_SERDES_CTRL_STATUS,&temp3));
        waitCounter++;
    }

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,13,1,temp>>13)); /* set disable bit back the way it was */

    /* if speed changed, let it stay. that's the speed that it ended up changing to/serdes was initialied to */

    if (waitCounter >= 100)
    {
        return MTD_FAIL; /* execute timed out */
    }

    return MTD_OK;
    
    
}



MTD_STATUS mtdGetSerdesAutoInitSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_U16 *autoSpeedDetected
)
{
    if (HorXunit == MTD_H_UNIT)
    {
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,0,4,autoSpeedDetected));
    }
    else
    {
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_SERDES_CTRL_STATUS,4,4,autoSpeedDetected));
    }

    return MTD_OK;
}


MTD_STATUS mtdSetSerdesControl1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_BOOL rx_powerdown,
    IN MTD_BOOL block_tx_on_loopback
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,12,1,MTD_GET_BOOL_AS_BIT(loopback)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,8,1,MTD_GET_BOOL_AS_BIT(rx_powerdown)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,6,1,MTD_GET_BOOL_AS_BIT(block_tx_on_loopback)));
    
    return MTD_OK;
}

MTD_STATUS mtdGetSerdesControl1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_BOOL *rx_powerdown,
    OUT MTD_BOOL *block_tx_on_loopback
)
{
    MTD_U16 temp;    

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,12,1,&temp));    
    MTD_CONVERT_UINT_TO_BOOL(temp, *loopback);
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,8,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, *rx_powerdown);
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL1,6,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, *block_tx_on_loopback);

    return MTD_OK;
}

MTD_STATUS mtdSetSerdesLanePolarity
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL invert_input_pol,
    IN MTD_BOOL invert_output_pol
)
{
    MTD_U8 input_pol_bit, output_pol_bit;

    if (HorXunit == MTD_H_UNIT)
    {
        if (MTD_IS_X32X0_BASE(devPtr->deviceId))
        {
            input_pol_bit = 14;
            output_pol_bit = 12;
        }
        else
        {
            input_pol_bit = 12;
            output_pol_bit = 8;
        }
    }
    else
    {
        input_pol_bit = 15;
        output_pol_bit = 13;
    }

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL2,input_pol_bit,1,MTD_GET_BOOL_AS_BIT(invert_input_pol)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL2,output_pol_bit,1,MTD_GET_BOOL_AS_BIT(invert_output_pol)));        

    return MTD_OK;
}

MTD_STATUS mtdGetSerdesLanePolarity
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL *invert_input_pol,
    IN MTD_BOOL *invert_output_pol
)
{
    MTD_U8 input_pol_bit, output_pol_bit;
    MTD_U16 temp;

    if (HorXunit == MTD_H_UNIT)
    {
        if (MTD_IS_X32X0_BASE(devPtr->deviceId))
        {
            input_pol_bit = 14;
            output_pol_bit = 12;
        }
        else
        {
            input_pol_bit = 12;
            output_pol_bit = 8;
        }
    }
    else
    {
        input_pol_bit = 15;
        output_pol_bit = 13;
    }

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL2,input_pol_bit,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, *invert_input_pol);
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_SERDES_CONTROL2,output_pol_bit,1,&temp));        
    MTD_CONVERT_UINT_TO_BOOL(temp, *invert_output_pol);
    
    return MTD_OK;
}

MTD_STATUS mtdSetSerdesInterruptEnable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL fifo_overflow,
    IN MTD_BOOL fifo_underflow,
    IN MTD_BOOL pkt_check_crc
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,1,1,MTD_GET_BOOL_AS_BIT(fifo_overflow)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,0,1,MTD_GET_BOOL_AS_BIT(fifo_underflow)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,2,1,MTD_GET_BOOL_AS_BIT(pkt_check_crc)));
    
    return MTD_OK;
}

MTD_STATUS mtdGetSerdesInterruptEnable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *fifo_overflow,
    OUT MTD_BOOL *fifo_underflow,
    OUT MTD_BOOL *pkt_check_crc
)
{
    MTD_U16 temp;

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,1,1,&temp));    
    MTD_CONVERT_UINT_TO_BOOL(temp, *fifo_overflow);
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,0,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, *fifo_underflow);
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,2,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, *pkt_check_crc);
    
    return MTD_OK;
}

MTD_STATUS mtdGetSerdesInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *fifo_overflow,
    OUT MTD_BOOL *fifo_underflow,
    OUT MTD_BOOL *pkt_check_crc
)
{
    MTD_U16 temp,temp2;

    /* clears latch bits, so need to read register in one operation */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_STATUS,&temp));

    mtdHwGetRegFieldFromWord(temp,1,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *fifo_overflow);

    mtdHwGetRegFieldFromWord(temp,0,1,&temp2);    
    MTD_CONVERT_UINT_TO_BOOL(temp2, *fifo_underflow);

    mtdHwGetRegFieldFromWord(temp,2,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *pkt_check_crc);
        
    return MTD_OK;
}

MTD_STATUS mtdSetGetSerdesPPMFifo
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,    
    INOUT MTD_U16 *fifo_offset
)
{
    if (*fifo_offset > MTD_SERDES_PPM_FIFO_GETONLY)
    {
        return MTD_FAIL; /* out of range */
    }

    if (MTD_IS_X32X0_BASE(devPtr->deviceId) ||
        MTD_IS_X33X0_BASE(devPtr->deviceId) ||
        MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        /* only get is allowed */
        if (*fifo_offset != MTD_SERDES_PPM_FIFO_GETONLY)
        {
            return MTD_FAIL; /* these devices cannot be changed they are forced to 11b */
        }
    }

    if (*fifo_offset < MTD_SERDES_PPM_FIFO_GETONLY)
    {
        /* update it in the register, leave input parameter the same */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CONTROL1,14,2,*fifo_offset));            
        
    }

    /* if get only, read don't change the register setting */
    /* set/get, read it back after writing it to make sure it was able to be set to desired setting */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_FIFO_CONTROL1,14,2,fifo_offset));            
    
    return MTD_OK;
}

MTD_STATUS mtdConfigurePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL readToClear,
    IN MTD_BOOL dontuseSFDinChecker,
    IN MTD_U16 pktPatternControl,
    IN MTD_BOOL generateCRCoff,
    IN MTD_U32 initialPayload,
    IN MTD_U16 frameLengthControl,
    IN MTD_U16 numPktsToSend,
    IN MTD_BOOL randomIPG,
    IN MTD_U16 ipgDuration
)
{
    if (pktPatternControl > MTD_PKT_RANDOM_WORD || pktPatternControl == 1)
    {
        return MTD_FAIL;
    }

    if (frameLengthControl == 6 || frameLengthControl == 7)
    {
        return MTD_FAIL;
    }
    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL1,15,1,MTD_GET_BOOL_AS_BIT(readToClear)));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL1,2,1,MTD_GET_BOOL_AS_BIT(dontuseSFDinChecker)));

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL2,4,4,pktPatternControl));
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL2,3,1,MTD_GET_BOOL_AS_BIT(generateCRCoff)));

    /* load up initial payload */
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_PAYLOAD1,(MTD_U16)initialPayload));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_PAYLOAD2,(MTD_U16)(initialPayload>>16)));

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_LENGTH,frameLengthControl));

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_BURSTSEQ,numPktsToSend));

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_IPG,15,1,MTD_GET_BOOL_AS_BIT(randomIPG)));
    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_IPG,0,15,ipgDuration));
    
    return MTD_OK;
}

MTD_STATUS mtdEnablePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL enableGenerator,
    IN MTD_BOOL enableChecker
)
{
    MTD_U16 temp=0,numPacket=0;
    
    /* better to start/stop at the same time if possible, use a single write to limit delays between them */
    temp = ((MTD_GET_BOOL_AS_BIT(enableGenerator))<<1) | (MTD_GET_BOOL_AS_BIT(enableChecker));    

    if (enableGenerator == MTD_FALSE)
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_BURSTSEQ,&numPacket));     
        /* need to write X.F017 = 0 to insure no fragments are sent when disabling the generator */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_BURSTSEQ,0x0000));        
    }

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL1,0,2,temp));

    if (enableGenerator == MTD_FALSE)
    {
        /* restore X.F017 to the configured value */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PKT_GEN_BURSTSEQ,numPacket));        
    }

    return MTD_OK;    
}

MTD_STATUS mtdPktGeneratorCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit    
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL1,6,1,1));   
    /* assumes delay is long enough to clear counters, this makes an assumption about the speed */
    /* of the MDIO as being relatively slow compared to the number of cycles it takes to clear the */
    /* clear the counters, relatively fast. may need a delay here for F2R, or really fast MDIO */
    /* speeds */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PKT_GEN_CONTROL1,6,1,0));    

    return MTD_OK;    
}

MTD_STATUS mtdPktGeneratorGetCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_U16 whichCounter,
    OUT MTD_U64 *packetCount,
    OUT MTD_U64 *byteCount    
)
{
    MTD_U16 temp;
    
    *packetCount = *byteCount = 0;
    
    switch (whichCounter)
    {
        case MTD_PKT_GET_TX:
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXPKTCTR1,&temp));
            *packetCount = temp;
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXPKTCTR2,&temp));
            *packetCount |= (((MTD_U64)(temp))<<16);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXPKTCTR3,&temp));
            *packetCount |= (((MTD_U64)(temp))<<32);

            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXBYTCTR1,&temp));
            *byteCount = temp;
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXBYTCTR2,&temp));
            *byteCount |= (((MTD_U64)(temp))<<16);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_TXBYTCTR3,&temp));
            *byteCount |= (((MTD_U64)(temp))<<32);            
            break;

        case MTD_PKT_GET_RX:
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXPKTCTR1,&temp));
            *packetCount = temp;
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXPKTCTR2,&temp));
            *packetCount |= (((MTD_U64)(temp))<<16);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXPKTCTR3,&temp));
            *packetCount |= (((MTD_U64)(temp))<<32);

            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXBYTCTR1,&temp));
            *byteCount = temp;
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXBYTCTR2,&temp));
            *byteCount |= (((MTD_U64)(temp))<<16);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_RXBYTCTR3,&temp));
            *byteCount |= (((MTD_U64)(temp))<<32);            
            break;

        case MTD_PKT_GET_ERR:
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_ERRPKTCTR1,&temp));
            *packetCount = temp;
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_ERRPKTCTR2,&temp));
            *packetCount |= (((MTD_U64)(temp))<<16);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PKT_GEN_ERRPKTCTR3,&temp));
            *packetCount |= (((MTD_U64)(temp))<<32);            
            break;

        default:
            return MTD_FAIL;
            break;            
    }
    
    return MTD_OK;
}

MTD_STATUS mtdPktGeneratorCheckerGetLinkDrop
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_U16 *linkDropCounter        
)
{
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_LINK_DROP_COUNTER,linkDropCounter));
    
    return MTD_OK;
}

/***************************** PRBS Control/Status/Counters *******************/

/* Bit Positions for PRBS Control/Status */
#define PRBS_READ_CLEAR_BIT 13
#define PRBS_LOCKED_BIT      8
#define PRBS_WAIT_LOCK_BIT   7
#define PRBS_CTR_RESET_BIT   6
#define PRBS_TX_EN_BIT       5
#define PRBS_RX_EN_BIT       4
#define PRBS_PATTERN_SEL_BIT 0 /* 4-bit field */

/*******************************************************************************
 MTD_STATUS mtdSetPRBSPattern
    Selects the PRBS pattern
*******************************************************************************/
MTD_STATUS mtdSetPRBSPattern
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  pattSel
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_PATTERN_SEL_BIT,4,(MTD_U16)pattSel));

    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdSetPRBSEnableTxRx
    Controls the transmit and receive
*******************************************************************************/
MTD_STATUS mtdSetPRBSEnableTxRx
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,
    IN MTD_U16  txEnable,
    IN MTD_U16  rxEnable
)
{
    MTD_U16 temp;

    if (rxEnable)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,0xF074,13,1,0));
    }
    else
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,0xF074,13,1,1));
    }
        
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_CONTROL,&temp));
    ATTEMPT(mtdHwSetRegFieldToWord(temp,txEnable,PRBS_TX_EN_BIT,1,&temp));
    ATTEMPT(mtdHwSetRegFieldToWord(temp,rxEnable,PRBS_RX_EN_BIT,1,&temp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_PRBS_CONTROL,temp));
        
    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdPRBSCounterReset
    Resets the PRBS counter when it's been set to manual reset and not clear-on-
    read
*******************************************************************************/
MTD_STATUS mtdPRBSCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_CTR_RESET_BIT,1,(MTD_U16)1));
        
    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdSetPRBSWaitForLock
    Makes the receiver start counting right away, even before it's locked 
    on the pattern
*******************************************************************************/
MTD_STATUS mtdSetPRBSWaitForLock
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,
    IN MTD_U16  disableWaitforLock
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_WAIT_LOCK_BIT,1,disableWaitforLock));
        
    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdGetPRBSWaitForLock
    Gets the value of the control bit that sets whether the counters start
    right away, or wait until the receiver is locked.
*******************************************************************************/
MTD_STATUS mtdGetPRBSWaitForLock
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,
    OUT MTD_U16 *disableWaitforLock
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_WAIT_LOCK_BIT,1,disableWaitforLock));
        
    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdSetPRBSClearOnRead
    Sets the bit that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MTD_STATUS mtdSetPRBSClearOnRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,
    IN MTD_U16  enableReadClear
)
{
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_READ_CLEAR_BIT,1,enableReadClear));
        
    return MTD_OK;
}


/*******************************************************************************
 MTD_STATUS mtdGetPRBSClearOnRead
    Reads the bit setting that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MTD_STATUS mtdGetPRBSClearOnRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,    
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *enableReadClear
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_READ_CLEAR_BIT,1,enableReadClear));
        
    return MTD_OK;
}


/*******************************************************************************
 MTD_STATUS mtdGetPRBSLocked
    Reads the status bit that indicates if the receiver is locked onto the
    PRBS pattern or not.
*******************************************************************************/
MTD_STATUS mtdGetPRBSLocked
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16    port,
    IN MTD_U16    HorXunit,
    OUT MTD_BOOL *prbsLocked
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_PRBS_CONTROL,PRBS_LOCKED_BIT,1,(MTD_U16 *)prbsLocked));
        
    return MTD_OK;
}

/*******************************************************************************
 MTD_STATUS mtdGetPRBSCounts
    Reads the counters. Will clear the counters if they've been setup to
    clear-on-read.
*******************************************************************************/
MTD_STATUS mtdGetPRBSCounts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,    
    IN MTD_U16   HorXunit,
    OUT MTD_U64 *txBitCount,
    OUT MTD_U64 *rxBitCount,
    OUT MTD_U64 *rxBitErrorCount
)
{
    MTD_U16 lowTxWord, lowRxWord, lowErrWord,
            midWord, hiWord;

    /* initialize values, in case of error return 0 */
    *txBitCount = *rxBitCount = *rxBitErrorCount = 0;

    /* must read low words first to latch the upper two words */

    /* read tx count lower/mid/upper */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_TXCTR1,&lowTxWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_TXCTR2,&midWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_TXCTR3,&hiWord));
    *txBitCount = lowTxWord + (((MTD_U64)(midWord))<<16) + (((MTD_U64)(hiWord))<<32);

    /* read rx count lower/mid/upper */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_RXCTR1,&lowRxWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_RXCTR2,&midWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_RXCTR3,&hiWord));
    *rxBitCount = lowRxWord + (((MTD_U64)(midWord))<<16) + (((MTD_U64)(hiWord))<<32);

    /* read err count lower/mid/upper */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_ERRCTR1,&lowErrWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_ERRCTR2,&midWord));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_PRBS_SYM_ERRCTR3,&hiWord));
    *rxBitErrorCount = lowErrWord + (((MTD_U64)(midWord))<<16) + (((MTD_U64)(hiWord))<<32);

    return MTD_OK;
}

/******************************************************************************
 Functions shared between H unit and X unit for 1000BX/SGMII
******************************************************************************/

MTD_STATUS mtdSet1000BXSGMIIControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_U16 speed,
    IN MTD_BOOL an_enable,
    IN MTD_BOOL power_down,
    IN MTD_BOOL restart_an,
    IN MTD_BOOL sw_reset
)
{       
    MTD_U16 bit6, bit13, temp;
    
    if (speed > MTD_SGMII_SPEED_ASIS)
    {
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,&temp));
  
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(loopback),14,1,&temp));

    if (speed != MTD_SGMII_SPEED_ASIS)
    {
        switch (speed)
        {
            case MTD_SGMII_SPEED_10M:
                bit6 = bit13 = 0;
                break;

            case MTD_SGMII_SPEED_100M:
                bit6 = 0;
                bit13 = 1;                
                break;

            case MTD_SGMII_SPEED_1G:
                bit6 = 1;
                bit13 = 0;
                break;

            default:
                return MTD_FAIL;
                break;
        }

        ATTEMPT(mtdHwSetRegFieldToWord(temp,bit6,6,1,&temp));
        ATTEMPT(mtdHwSetRegFieldToWord(temp,bit13,13,1,&temp));
        
    }

      
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(an_enable),12,1,&temp));  
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(power_down),11,1,&temp));
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(restart_an),9,1,&temp)); 
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(sw_reset),15,1,&temp));

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,temp));
    
    return MTD_OK;    
}

MTD_STATUS mtdGet1000BXSGMIIControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_U16 *speed,
    OUT MTD_BOOL *an_enable,
    OUT MTD_BOOL *power_down
)
{
    MTD_U16 temp,bit6,bit13; 
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,14,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp,*loopback);
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,6,1,&bit6));   
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,13,1,&bit13));
    *speed = (bit6<<1) | bit13;

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,12,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp,*an_enable);
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_CONTROL,11,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp,*power_down);
    
    return MTD_OK;
}

MTD_STATUS mtdGet1000BXSGMIIStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *an_complete,
    OUT MTD_BOOL *remote_fault,
    OUT MTD_BOOL *link_status_latched,
    OUT MTD_BOOL *link_status_current
)
{
    MTD_U16 temp,temp2;

    /* read once to get all bits including latched low link status (may clear LL link status) */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1000X_SGMII_STATUS,&temp));

    mtdHwGetRegFieldFromWord(temp,5,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2,*an_complete);

    mtdHwGetRegFieldFromWord(temp,4,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2,*remote_fault);

    mtdHwGetRegFieldFromWord(temp,2,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2,*link_status_latched);

    /* read it again to get current link status */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,HorXunit,MTD_1000X_SGMII_STATUS,2,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp,*link_status_current);
    
    return MTD_OK;
}

/******************************************************************************
 Functions shared between H unit and X unit for 10GBASE-R PCS
 XFI
 SFI
 USXGMII
 All use H unit or X unit 10GBASE-R PCS 
******************************************************************************/

/* can also call with mtdSetUSXGMIIControl() */
MTD_STATUS mtdSet10GBRControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_BOOL power_down,
    IN MTD_BOOL sw_reset
)
{
    MTD_U16 temp;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_CONTROL,&temp));    

    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(loopback),14,1,&temp)); 
    
    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(power_down),11,1,&temp)); 

    ATTEMPT(mtdHwSetRegFieldToWord(temp,MTD_GET_BOOL_AS_BIT(sw_reset),15,1,&temp)); 

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_10GBR_PCS_CONTROL,temp));

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        /* Needs workaround for loopback to work in E21X0 devices */
        if (HorXunit == MTD_X_UNIT)
        {
            return MTD_FAIL; /* No X unit in 21XX devices */
        }
        
        if (loopback)
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,4,0xF07E,13,3,5)); /* force signal lock */ 
        }
        else
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,4,0xF07E,13,3,1)); /* clear overwrite bit */
        }
    }
    
    return MTD_OK;
}

/* can also call with mtdGetUSXGMIIControl() */
MTD_STATUS mtdGet10GBRControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_BOOL *power_down
)
{
    MTD_U16 lb,pd,temp;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_CONTROL,&temp));
    mtdHwGetRegFieldFromWord(temp,14,1,&lb);
    mtdHwGetRegFieldFromWord(temp,11,1,&pd);
    MTD_CONVERT_UINT_TO_BOOL(lb, *loopback);
    MTD_CONVERT_UINT_TO_BOOL(pd, *power_down);
        
    return MTD_OK;
}

/* can also call with mtdGetUSXGMIIStatus1() */
MTD_STATUS mtdGet10GBRStatus1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *tx_lpi_latch,
    OUT MTD_BOOL *rx_lpi_latch,
    OUT MTD_BOOL *tx_lpi_current,
    OUT MTD_BOOL *rx_lpi_current,
    OUT MTD_BOOL *fault,
    OUT MTD_BOOL *link_status_latch,
    OUT MTD_BOOL *link_status_current    
)
{
    MTD_U16 temp1,temp2,temp3;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_STATUS1,&temp1)); /* latched value */

    mtdHwGetRegFieldFromWord(temp1,11,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *tx_lpi_latch);
    mtdHwGetRegFieldFromWord(temp1,10,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *rx_lpi_latch);
    mtdHwGetRegFieldFromWord(temp1,2,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *link_status_latch);
            
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_STATUS1,&temp2)); /* current value */

    mtdHwGetRegFieldFromWord(temp2,9,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *tx_lpi_current);
    mtdHwGetRegFieldFromWord(temp2,8,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *rx_lpi_current);
    mtdHwGetRegFieldFromWord(temp2,7,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *fault);
    mtdHwGetRegFieldFromWord(temp2,2,1,&temp3);
    MTD_CONVERT_UINT_TO_BOOL(temp3, *link_status_current);
        
    return MTD_OK;
}

/* can also call with mtdGetUSXGMIIFault() */
MTD_STATUS mtdGet10GBRFault
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,    
    OUT MTD_BOOL *tx_fault_latch,
    OUT MTD_BOOL *rx_fault_latch,
    OUT MTD_BOOL *tx_fault_current,
    OUT MTD_BOOL *rx_fault_current
)
{
    MTD_U16 temp1, fault;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_FAULT,&temp1)); /* latched value */
    mtdHwGetRegFieldFromWord(temp1,11,1,&fault);
    MTD_CONVERT_UINT_TO_BOOL(fault, *tx_fault_latch);
    mtdHwGetRegFieldFromWord(temp1,10,1,&fault);
    MTD_CONVERT_UINT_TO_BOOL(fault, *rx_fault_latch);

    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_FAULT,&temp1)); /* current value */
    mtdHwGetRegFieldFromWord(temp1,11,1,&fault);
    MTD_CONVERT_UINT_TO_BOOL(fault, *tx_fault_current);
    mtdHwGetRegFieldFromWord(temp1,10,1,&fault);
    MTD_CONVERT_UINT_TO_BOOL(fault, *rx_fault_current);

    return MTD_OK;
}

/* can also call with mtdGetUSXGMIIReceiveStatus() */
MTD_STATUS mtdGet10GBRReceiveStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit, 
    OUT MTD_BOOL *link_up,
    OUT MTD_BOOL *high_ber,
    OUT MTD_BOOL *block_lock    
)
{
    MTD_U16 temp1, temp2;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_RXSTATUS,&temp1)); /* current value */
    mtdHwGetRegFieldFromWord(temp1,12,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *link_up);
    mtdHwGetRegFieldFromWord(temp1,1,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *high_ber);
    mtdHwGetRegFieldFromWord(temp1,0,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *block_lock);
    
    
    return MTD_OK;
}

/* can also call with mtdGetUSXGMIIStatus2() */
MTD_STATUS mtdGet10GBRStatus2
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit, 
    OUT MTD_BOOL *has_block_lock,
    OUT MTD_BOOL *reported_high_ber,
    OUT MTD_U8 *ber_counter,
    OUT MTD_U8 *errored_blocks_counter    
)
{
    MTD_U16 temp1, temp2;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_PCS_STATUS2,&temp1)); /* latch value, clears latch/counters */
    mtdHwGetRegFieldFromWord(temp1,15,1,&temp2);

    MTD_CONVERT_UINT_TO_BOOL(temp2, *has_block_lock);

    mtdHwGetRegFieldFromWord(temp1,14,1,&temp2);
    MTD_CONVERT_UINT_TO_BOOL(temp2, *reported_high_ber);

    mtdHwGetRegFieldFromWord(temp1,8,6,&temp2);
    *ber_counter = (MTD_U8)temp2;
    
    mtdHwGetRegFieldFromWord(temp1,0,8,&temp2);
    *errored_blocks_counter = (MTD_U8)temp2;
    
    return MTD_OK;
}

MTD_STATUS mtdSetHXunitMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
)
{
    if (HorXunit == MTD_H_UNIT)
    {
        /* Shallow MAC Loopback */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_SERDES_CONTROL1,12,1,(MTD_U16)enable));
    }
    else /* X-unit */
    {
        if (MTD_HAS_X_UNIT(devPtr))
        {
            /* Deep MAC Loopback */
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_10GBR_PCS_CONTROL,14,1,(MTD_U16)enable));
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_SERDES_CONTROL1,6,1,(MTD_U16)(!passThrough)));
        } 
        else
        {
            MTD_DBG_ERROR("mtdSetHXunitMacLoopback: No X-unit in E20X0 and E21X0 PHY!\n");
            return MTD_FAIL;
        }
    }

    return MTD_OK;
}

MTD_STATUS mtdSetHXunitLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
)
{
    if (HorXunit == MTD_H_UNIT)
    {
        /* Deep Line Loopback */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_10GBR_PCS_CONTROL,14,1,(MTD_U16)enable));

        /* Needs workaround for loopback to work in E21X0 devices */
        if (MTD_IS_E21X0_BASE(devPtr->deviceId))
        {
            if (enable)
            {
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,0xF07E,13,3,5)); /* force signal lock */ 
            }
            else
            {
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,0xF07E,13,3,1)); /* clear overwrite bit */
            }
        }

        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_SERDES_CONTROL1,6,1,(MTD_U16)(!passThrough)));
    }
    else  /* X-unit */
    {
        if (MTD_HAS_X_UNIT(devPtr))
        {
            /* Shallow Line Loopback */
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_SERDES_CONTROL1,12,1,(MTD_U16)enable));
        }
        else
        {
            MTD_DBG_ERROR("mtdSetHXunitLineLoopback: No X-unit in E20X0 and E21X0 PHY!\n");
            return MTD_FAIL;
        }
    }
  
    return MTD_OK;
}

MTD_STATUS mtdSetShallowMacLoopbackLinkDown
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  linkDownSpeed,
    IN MTD_BOOL enable
)
{
    MTD_U16 macType;
    MTD_BOOL macIfPowerDown;
    MTD_U16 macIfSnoopSel;
    MTD_U16 macIfActiveLaneSelect;
    MTD_U16 macLinkDownSpeed;
    MTD_U16 macMaxIfSpeed; /* 33X0/E20X0/E21X0 devices only */
    MTD_U16 speedsAvailable;

    /* find out what speeds this device supports */
    ATTEMPT(mtdGetSpeedsAvailable(devPtr,port,&speedsAvailable));

    /* Get Host MAC interface control parameters */
    ATTEMPT(mtdGetMacInterfaceControl(devPtr,port,&macType, &macIfPowerDown, &macIfSnoopSel, \
            &macIfActiveLaneSelect, &macLinkDownSpeed, &macMaxIfSpeed));

    /* Set host link down speed */
    switch (linkDownSpeed)
    {
        case MTD_SPEED_10GIG_FD:
            if (!(speedsAvailable & MTD_SPEED_10GIG_FD))
            {
                MTD_DBG_ERROR("mtdSetShallowMacLoopbackLinkDown: Invalid link down speed!\n");
                return MTD_FAIL;
            }

            macLinkDownSpeed = MTD_MAC_SPEED_10_GBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_10G;
            break;

        case MTD_SPEED_5GIG_FD:
            if (!(speedsAvailable & MTD_SPEED_5GIG_FD))
            {
                MTD_DBG_ERROR("mtdSetShallowMacLoopbackLinkDown: Invalid link down speed!\n");
                return MTD_FAIL;
            }

            macLinkDownSpeed = MTD_MAC_SPEED_10_GBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_5G;
            break;

        case MTD_SPEED_2P5GIG_FD:
            if (!(speedsAvailable & MTD_SPEED_2P5GIG_FD))
            {
                MTD_DBG_ERROR("mtdSetShallowMacLoopbackLinkDown: Invalid link down speed!\n");
                return MTD_FAIL;
            }

            macLinkDownSpeed = MTD_MAC_SPEED_10_GBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_2P5G;
            break;

        case MTD_SPEED_1GIG_FD:
        case MTD_SPEED_1GIG_HD:            
            macLinkDownSpeed = MTD_MAC_SPEED_1000_MBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED;
            break;

        case MTD_SPEED_100M_FD:
        case MTD_SPEED_100M_HD:
            macLinkDownSpeed = MTD_MAC_SPEED_100_MBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED;
            break;

        case MTD_SPEED_10M_FD:
        case MTD_SPEED_10M_HD:
            macLinkDownSpeed = MTD_MAC_SPEED_10_MBPS;
            macMaxIfSpeed = MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED;
            break;

        default:
            MTD_DBG_ERROR("mtdSetShallowMacLoopbackLinkDown: Invalid link down speed!\n");
            return MTD_FAIL;
            break;
    }

    /* over write for X32X0 PHY */
    if (MTD_IS_X32X0_BASE(devPtr->deviceId))
    {
        macMaxIfSpeed = MTD_MAX_MAC_SPEED_NOT_APPLICABLE;
    }

    ATTEMPT(mtdSetMacInterfaceControl(devPtr,port,macType, macIfPowerDown, macIfSnoopSel, \
            macIfActiveLaneSelect, macLinkDownSpeed, macMaxIfSpeed,MTD_TRUE,MTD_TRUE));

    /* Shallow MAC Loopback */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_SERDES_CONTROL1,12,1,(MTD_U16)enable));
  
    return MTD_OK;
}
