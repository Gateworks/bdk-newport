/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtd_ptp_api.c
*
* DESCRIPTION:
*       API Functions of PTP in MacSec.
*
* DEPENDENCIES:
*       None.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/

#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdAPIInternal.h"
#include "mtdMsecTypes.h"
#include "mtdMsecInternal.h"
#include "mtdMsecApi.h"
#include "mtdPtp1step.h"
#include "mtdPtpApi.h"

/*******************************************************************************
* mtd_enable_ptp
*
* DESCRIPTION:
*       This routine enable PTP by clearing PTP bypass
*
* INPUTS:
*    port - port number.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_enable_ptp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT data;
    data = mtd_ptp_read_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN);
    data |= 9;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN, data);
    if(retVal!=MTD_OK) return retVal;
    data = mtd_ptp_read_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN);
    data |= 9;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN, data);
    if(retVal!=MTD_OK) return retVal;
    data = mtd_ptp_read_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_TS_QUEUE);
    data |= 0x100;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_TS_QUEUE, 0x100);
    if(retVal!=MTD_OK) return retVal;
    data = mtd_ptp_read_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_TS_QUEUE);
    data |= 0x100;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_TS_QUEUE, 0x100);
    return retVal;
}
/*******************************************************************************
* mtd_disable_ptp
*
* DESCRIPTION:
*       This routine disables PTP by setting PTP bypass.
*
* INPUTS:
*    port - port number.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_disable_ptp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT data;
    data = mtd_ptp_read_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN);
    data &= ~1;
    data |= 8;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN, data);
    if(retVal!=MTD_OK) return retVal;
    data = mtd_ptp_read_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN);
    data &= ~1;
    data |= 8;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+MTD_PTP_PORT_OFF(port)+MTD_PTP_1STEP_CFG_GEN, data);
    
    /* Disable constant latency workaround */
    retVal = mtd_msec_set_constant_latency(port, 0);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_disable_ptp: mtd_msec_set_constant_latency failed\n");
        return(retVal);
    }

    return retVal;
}

/*******************************************************************************
* mtd_ptp_prgm_lut_entry
*
* DESCRIPTION:
*     program lut entry
*      lut_key: 80 bit match fields
*      lut_valid: 80 bit valid fields (correspond to lut_match)
*      lut_action: 32 bit action fields
*      lut_index: index of LUT entry to program
*      path: eg0_ptp for egress or ig0_ptp for ingress
*
* INPUTS:
*       lut_match - 80 bit match fields
*       lut_valid: 80 bit valid fields (correspond to lut_match)
*       lut_action: 32 bit action fields
*       lut_index: index of LUT entry to program
*       path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_prgm_lut_entry (MTD_U16 port, MTD_64 lut_key, MTD_64 lut_valid, MTD_32 lut_key_upper, MTD_32 lut_valid_upper, MTD_64 lut_action,
    MTD_16 lut_index, MTD_INT path )
{
    MTD_STATUS   retVal = MTD_OK;
//  MTD_U16 match_base_addr =(path+MTD_PTP_LUT_KEYMASK+0x10*MTD_PTP_ADDR_ADJ*lut_index);
    MTD_U16 match_base_addr =(path+MTD_PTP_LUT_KEYMASK+0x10*lut_index);
    MTD_U16 action_base_addr;
    MTD_U32 data;

    MTD_DBG_INFO("ptp_prgm_lut_entry %d\n", lut_index);

    MTD_DBG_INFO("port %d path %x, index %2d => key %0llx, vld %0llx, act %0llx\n", port, path, lut_index, lut_key, lut_valid, lut_action);
//printf("port %d path %x, index %2d => key %0llx, vld %0llx, act %0llx\n", port, path, lut_index, lut_key, lut_valid, lut_action);
  /* Have to write multiple words at a time, so don't use retVal = mtd_ptp_writecheck_reg */
//  mtdWait(10);
    data = (MTD_U32)((lut_key)&0xffffffffll);
//  data = ((lut_key)&0xffffffffll);
//printf("lut_key addr0 lut_key: %0llx, data:%x\n", lut_key, data);
    mtd_ptp_msec_sem_take(OS_WAIT_FOREVER);
    if(mtd_ptp_msec_set_link_down_reset(port,0)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtd_ptp_write_reg (port, match_base_addr+0*MTD_PTP_ADDR_ADJ,data);
    if(retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    data = (MTD_U32)((lut_key>>32)&0xffffffffll);
//  data = ((lut_key>>32)&0xffffffffll);
    retVal = _mtd_ptp_write_reg (port, match_base_addr+1*MTD_PTP_ADDR_ADJ,data);
    if(retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    retVal = _mtd_ptp_write_reg (port, match_base_addr+2*MTD_PTP_ADDR_ADJ,(MTD_UINT)((lut_key_upper)&0xffffffff));
    if(retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
//  mtdWait(10);
    data = (MTD_U32)((lut_valid>>0)&0xffffffffll);
//  data = ((lut_valid>>0)&0xffffffffll);
//printf("lut_valid addr0 data:%x\n", data);
    retVal = _mtd_ptp_write_reg (port, match_base_addr+4*MTD_PTP_ADDR_ADJ,data);
    if(retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    data = (MTD_U32)((lut_valid>>32)&0xffffffffll);
//  data = ((lut_valid>>32)&0xffffffffll);
    retVal = _mtd_ptp_write_reg (port, match_base_addr+5*MTD_PTP_ADDR_ADJ,data);
    if(retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    retVal = _mtd_ptp_write_reg (port, match_base_addr+6*MTD_PTP_ADDR_ADJ,(MTD_UINT)((lut_valid_upper>>0)&0xffffffff));
    if(mtd_ptp_msec_set_link_down_reset(port,1)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtd_ptp_msec_sem_give();
    if(retVal!=MTD_OK) return retVal;

  /* set action_base_addr [expr $base_addr($path)+$ptp_addr(LUT_ACTION)+$lut_index]; */
    action_base_addr = (path+MTD_PTP_LUT_ACTION+lut_index*MTD_PTP_ADDR_ADJ);

  /*# Have to write multiple words at a time, so don't use writecheck_reg */
  /*write_reg [expr $action_base_addr+0] [expr $lut_action & $mask_low]; */
//  mtdWait(10);
    retVal = mtd_ptp_write_reg (port, action_base_addr+0,(MTD_UINT)((lut_action)&0xffffffffll));
    if(retVal!=MTD_OK) return retVal;
/*  retVal = mtd_ptp_write_reg (port, action_base_addr+1,(lut_action>>32)&0xffffffff); */
    return retVal;
}

/*******************************************************************************
* mtd_ptp_check_lut_entry
*
* DESCRIPTION:
*   Check lut entry in memory
*
* INPUTS:
*       lut_index: index of LUT entry to program
*       path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_check_lut_entry ( MTD_U16 port, MTD_INT lut_index, MTD_INT path )
{
    MTD_STATUS   retVal = MTD_OK;
/*   MTD_UINT match_base_addr; */
    MTD_64 lut_match;
    MTD_32 lut_match_hi;
    MTD_64 lut_valid;
    MTD_32 lut_valid_hi;
    MTD_INT field = 0;
/*   MTD_UINT action_base_addr; */
    MTD_64 lut_action;
/*   MTD_64 dataMTD_32; */

    MTD_DBG_CRITIC_INFO("ptp_check_lut_entry %d\n", lut_index);
    mtd_read_lut_entry (port, &lut_match, &lut_valid, &lut_match_hi, &lut_valid_hi,
        &lut_action, lut_index, path );
    MTD_DBG_CRITIC_INFO("\nMATCH/VALID vectors 0x%llx 0x%llx\n", lut_match, lut_valid);

/*  foreach field [array names lut_match_fld_pos] { */
    while(mtd_ptp_lut_match_fld_pos_name[field]!=0)
    {
        MTD_U64 match_fld;
        MTD_U64 valid_fld;

        match_fld = mtd_ptp_lut_match_fld_extract( field, lut_match);
        valid_fld = mtd_ptp_lut_match_fld_extract( field, lut_valid);
        MTD_DBG_CRITIC_INFO("MATCH/VALID field %s 0x%llx %llx\n", mtd_ptp_lut_match_fld_pos_name[field], match_fld, valid_fld);
        field++;
    }

    MTD_DBG_CRITIC_INFO("\nACTION vectors 0x%llx\n", lut_action);
    if(path== MTD_VN_IG_PTP)
    {
        field = 0;
        while(mtd_ptp_lut_rx_action_fld_pos_name[field]!=0)
        {
            MTD_64 action_fld;

            action_fld = mtd_ptp_lut_rx_action_fld_extract (field, lut_action);
            MTD_DBG_CRITIC_INFO("Ingress ACTION field %s 0x%llx\n", mtd_ptp_lut_rx_action_fld_pos_name[field], action_fld);
            field ++;
        }
    }
    else if(path== MTD_VN_EG_PTP)
    {
        field = 0;
        while(mtd_ptp_lut_tx_action_fld_pos_name[field]!=0)
        {
            MTD_64 action_fld;

            action_fld = mtd_ptp_lut_tx_action_fld_extract (field, lut_action);
            MTD_DBG_CRITIC_INFO("Egress ACTION field %s 0x%llx\n", mtd_ptp_lut_tx_action_fld_pos_name[field], action_fld);
            field ++;
        }
    }
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_ts_tsq
*
* DESCRIPTION:
*       This routine gets Time stamp from TS Queue.
*
* INPUTS:
*    port - port number.
*       path  - NewPtp block number: igr or egr.
*       queue - NewPtp queue number: high or low.
*       seqId - sequence id of PTP frame .
*       msgId - message id of PTP frame .
n*
* OUTPUTS:
*       ts - NewPtp Time stamp data.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_ts_tsq
(
    IN  MTD_U16 port,
    IN  MTD_PTP_Blk path,
    IN  MTD_PTP_1STEP_QUEUE_TYPE queue,
    IN  MTD_U16 seqId,
    IN  MTD_U16 msgId,
    OUT MtdPtp1StepTsStruct *ts
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT numhwords;
    MtdPtpTsQueueStruct tsQueue;
    MTD_INT i;
    MTD_INT numdata;
    MTD_PTP_1STEP_LUT_ACT action;

    if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
    {
        numhwords = mtd_get_ptp_tsqh_usage(port, path);
        action = MTD_PTP_Act_StampHigh;
    }
    else
    {
        numhwords = mtd_get_ptp_tsql_usage(port, path);
        action = MTD_PTP_Act_StampLow;
    }
    numdata = numhwords;

/*  MTD_DBG_INFO("@@@@@@@@@@@@  mtd_ptp_get_ts_tsq get number %d\n", numhwords); */
    numhwords /= MTD_PTP_TS_QUEUE_SIZE;

    if(numhwords == 0)
    {
        MTD_DBG_INFO("TS queue is empty\n");
#if 1
        if((numdata/MTD_PTP_TS_QUEUE_SIZE==0)&&(numdata%MTD_PTP_TS_QUEUE_SIZE))
        {
            MTD_INT idx =0;
            MtdPtpTsQueueStruct tsQueue;
            retVal = mtd_ptp_find_lut_action(port, action, path, &idx);
            if(retVal!=MTD_OK) return MTD_FAIL;
            retVal = mtd_ptp_enable_lut_action(port, idx, action, path,MTD_FALSE);
            if(retVal!=MTD_OK) return MTD_FAIL;
            if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
                retVal = mtd_ptp_get_tsqh_part(port, path, numdata%MTD_PTP_TS_QUEUE_SIZE, &tsQueue);
            else
                retVal = mtd_ptp_get_tsql_part(port, path, numdata%MTD_PTP_TS_QUEUE_SIZE, &tsQueue);

            if(retVal!=MTD_OK) return MTD_FAIL;
            retVal = mtd_ptp_enable_lut_action(port, idx, action, path,MTD_TRUE);
            if(retVal!=MTD_OK) return MTD_FAIL;
        }
#endif
        return MTD_FAIL;
    }
    tsQueue.seqId=seqId - 1;
    i = 0;
    while(tsQueue.seqId<=seqId)
    {
        if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
            retVal = mtd_ptp_get_tsqh ( port, path, &tsQueue);
        else
            retVal = mtd_ptp_get_tsql ( port, path, &tsQueue);
//:    tsQueue.seqId++;   /* Xu */
        i++;
        if(i >= numhwords)
            break;
        if((tsQueue.seqId==seqId)&&(tsQueue.msgId==msgId))
        {
            break;
        }
    }
//printf("@@@@@@@@@@@@  mtd_ptp_get_ts_tsq get seqId: %d:%d\n", tsQueue.seqId, seqId);
    if((tsQueue.seqId==seqId)&&(tsQueue.msgId==msgId))
    {
        ts->extTs.nanoseconds = tsQueue.ts.extTs.nanoseconds;
        ts->extTs.topseconds = tsQueue.ts.extTs.topseconds;
        ts->extTs.seconds = tsQueue.ts.extTs.seconds;
//printf("@@@@@@@@@@@@  mtd_ptp_get_ts_tsq get extTs: %x:%x:%x\n", ts->extTs.nanoseconds, ts->extTs.topseconds, ts->extTs.seconds);

        return MTD_OK;
    }
    else
    {
        ts->extTs.nanoseconds = 0;
        ts->extTs.topseconds = 0;
        ts->extTs.seconds = 0;
        return MTD_FAIL;
    }
    return retVal;
}


/*******************************************************************************
* mtd_ptp_get_ntp_ts_tsq
*
* DESCRIPTION:
*       This routine gets Time stamp from TS Queue for NTP.
*
* INPUTS:
*    port - port number.
*       path  - NewPtp block number: igr or egr.
*       queue - NewPtp queue number: high or low.
*
* OUTPUTS:
*       numwords - number of TS elements in Queue.
*       ts - NewPtp Time stamp data.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_ntp_ts_tsq
(
    IN  MTD_U16 port,
    IN  MTD_PTP_Blk path,
    IN  MTD_PTP_1STEP_QUEUE_TYPE queue,
    OUT MTD_INT *numwords,
    OUT MtdPtp1StepTsStruct *ts
)
{
    MTD_STATUS   retVal = MTD_OK;
    MtdPtpTsQueueStruct tsQueue;
    MTD_INT numdata;
    MTD_PTP_1STEP_LUT_ACT action;

    if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
    {
        numdata = mtd_get_ptp_tsqh_usage(port, path);
        action = MTD_PTP_Act_StampHigh;
    }
    else
    {
        numdata = mtd_get_ptp_tsql_usage(port, path);
        action = MTD_PTP_Act_StampLow;
    }
    *numwords = numdata;
/*  MTD_DBG_INFO("@@@@@@@@@@@@  mtd_ptp_get_ts_tsq get number %d\n", *numwords); */
    *numwords /= MTD_PTP_TS_QUEUE_SIZE;

    if(*numwords == 0)
    {
#if 1
        if((numdata/MTD_PTP_TS_QUEUE_SIZE==0)&&(numdata%MTD_PTP_TS_QUEUE_SIZE))
        {
            MTD_INT idx =0;
            MtdPtpTsQueueStruct tsQueue;
/*printf("!!!!!!!!!!! Clear invalid TS bytes %d  !!!!!!!!!!!!!\n", numdata%MTD_PTP_TS_QUEUE_SIZE);
*/
            retVal = mtd_ptp_find_lut_action(port, action, path, &idx);
            if(retVal!=MTD_OK) return MTD_FAIL;
            retVal = mtd_ptp_enable_lut_action(port, idx, action, path,MTD_FALSE);
            if(retVal!=MTD_OK) return MTD_FAIL;
            if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
                retVal = mtd_ptp_get_tsqh_part(port, path, numdata%MTD_PTP_TS_QUEUE_SIZE, &tsQueue);
            else
                retVal = mtd_ptp_get_tsql_part(port, path, numdata%MTD_PTP_TS_QUEUE_SIZE, &tsQueue);

            if(retVal!=MTD_OK) return MTD_FAIL;
            retVal = mtd_ptp_enable_lut_action(port, idx, action, path,MTD_TRUE);
            if(retVal!=MTD_OK) return MTD_FAIL;
        }
#endif
        MTD_DBG_INFO("TS queue is empty\n");
        ts->extTs.nanoseconds = 0;
        ts->extTs.topseconds = 0;
        ts->extTs.seconds = 0;
        return MTD_FAIL;
    }
    {
        if(queue == MTD_PTP_1STEP_QUEUE_HIGH)
            retVal = mtd_ptp_get_tsqh ( port, path, &tsQueue);
        else
            retVal = mtd_ptp_get_tsql ( port, path, &tsQueue);
    }

/*printk("@@@@@@@@@@@@  mtd_ptp_get_ts_tsq get seqId %d, msgId %d\n", tsQueue.seqId, tsQueue.msgId==msgId);*/
    ts->extTs.nanoseconds = tsQueue.ts.extTs.nanoseconds;
    ts->extTs.topseconds = tsQueue.ts.extTs.topseconds;
    ts->extTs.seconds = tsQueue.ts.extTs.seconds;
/*printk("@@@@@@@@@@@ msg %x Queue TS Second %d:%d nanosecond %d\n", tsQueue.msgId, ts->extTs.topseconds, ts->extTs.seconds,ts->extTs.nanoseconds);*/
    *numwords = *numwords - 1;
    return MTD_OK;
}
/* TAI / TOD */

/*******************************************************************************
* mtd_get_ptp_tai_tod
*
* DESCRIPTION:
*       This routine gets Time of day of PTP TAI.
*
* INPUTS:
*    port - port number.
*
* OUTPUTS:
*        frac - fraction nanoseconds
*       ns - nanoseconds.
*       sec_lo - low bits seconds.
*       sec_hi - high bits seconds.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_tod (MTD_U16 port, MTD_UINT *_ns, MTD_UINT *_sec_lo, MTD_UINT *_sec_hi )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];

    MTD_UINT  frac;
    MTD_UINT  ns;
    MTD_UINT  sec_lo;
    MTD_UINT  sec_hi;
    MTD_U64   sec;

    frac   = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_TOD_0*MTD_PTP_ADDR_ADJ));
    ns     = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_TOD_1*MTD_PTP_ADDR_ADJ));
    sec_lo = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_TOD_2*MTD_PTP_ADDR_ADJ));
    sec_hi = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_TOD_3*MTD_PTP_ADDR_ADJ));

    sec =  sec_hi;
    sec =  (sec << 32);
    sec = sec + sec_lo + ns/1000000000;

    MTD_DBG_INFO("sec_hi:%08x sec_lo:%08x ns:%08x => \n", sec_hi, sec_lo, ns);
    MTD_DBG_INFO(" => seconds sec %lld\n", sec);
    *_ns=ns;
    *_sec_lo=sec_lo;
    *_sec_hi=sec_hi;
    return retVal;
}

/*******************************************************************************
* mtd_get_ptp_tai_frc
*
* DESCRIPTION:
*       This routine gets Free running counter of PTP TAI.
*
* INPUTS:
*    port - port number.
*
* OUTPUTS:
*       ns - nanoseconds.
*       sec_lo - low bits seconds.
*       sec_hi - high bits seconds.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_frc (MTD_U16 port, MTD_UINT *_ns, MTD_UINT *_sec_lo, MTD_UINT *_sec_hi )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];

    MTD_UINT  frac;
    MTD_UINT  ns;
    MTD_UINT  sec_lo;
    MTD_UINT  sec_hi;
    MTD_U64   sec;

    frac   = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_FRC_0*MTD_PTP_ADDR_ADJ));
    ns     = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_FRC_1*MTD_PTP_ADDR_ADJ));
    sec_lo = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_FRC_2*MTD_PTP_ADDR_ADJ));
    sec_hi = mtd_ptp_read_reg(port, (my_base_addr + MTD_REG_FRC_3*MTD_PTP_ADDR_ADJ));

    sec =  sec_hi;
    sec =  (sec << 32);
    sec = sec + sec_lo + ns/1000000000;

    MTD_DBG_INFO("sec_hi:%08x sec_lo:%08x ns:%08x => \n", sec_hi, sec_lo, ns);
    MTD_DBG_INFO(" => seconds sec %lld\n", sec);
    *_ns=ns;
    *_sec_lo=sec_lo;
    *_sec_hi=sec_hi;
    return retVal;
}

/*******************************************************************************
* mtd_get_ptp_tai_drift_adjust
*
* DESCRIPTION:
*       This routine gets drift adjust of PTP TAI.
*
* INPUTS:
*    port - port number.
*
* OUTPUTS:
*       adj - adjust value.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_drift_adjust (MTD_U16 port, MTD_UINT *adj)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
  /* drift adjustment, default is 0 */
    MTD_U16 reg_addr = my_base_addr + MTD_REG_DRIFT_ADJ_CFG*MTD_PTP_ADDR_ADJ;
    *adj   = mtd_ptp_read_reg(port, reg_addr);
    return retVal;
}

/*******************************************************************************
* mtd_set_ptp_tai_drift_adjust
*
* DESCRIPTION:
*       This routine gets drift adjust of PTP TAI.
*
* INPUTS:
*    port - port number.
*       adj - adjust value.
*
* OUTPUTS:
*   None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_ptp_tai_drift_adjust (MTD_U16 port, MTD_UINT adj)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
  /* drift adjustment, default is 0 */
    MTD_U16 reg_addr = my_base_addr + MTD_REG_DRIFT_ADJ_CFG*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, adj);
    return retVal;
}

/*******************************************************************************
* mtd_get_ptp_tsqh_drain
*
* DESCRIPTION:
*       This routine gets high TS queue of PTP TAI fully.
*
* INPUTS:
*    port - port number.
*   path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tsqh_drain ( MTD_U16 port,  MTD_PTP_Blk path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT numhwords = mtd_get_ptp_tsqh_usage(port, path);
  /*get_ptp_tsqh_data $port $path [expr $numhwords/2] */
    mtd_get_ptp_tsqh_data(port, path, numhwords);
    return retVal;
}

/*******************************************************************************
* mtd_get_ptp_tsql_drain
*
* DESCRIPTION:
*       This routine gets low TS queue of PTP TAI fully.
*
* INPUTS:
*    port - port number.
*   path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tsql_drain ( MTD_U16 port,  MTD_PTP_Blk path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT numhwords = mtd_get_ptp_tsql_usage(port, path);
  /*get_ptp_tsql_data $port $path [expr $numhwords/2] */
    mtd_get_ptp_tsql_data(port, path, numhwords);
    return retVal;
}

/*******************************************************************************
* mtd_set_tai_tod_func
*
* DESCRIPTION:
*       This routine sets TAI TOD trigger generaly.
*
* INPUTS:
*    port - port number.
*   tod_func - value: 0 - update, 1 -increment, 2- decrement, 3-capture
*   trig - tod_func_trig, default 0, triggers tod function when set to 1
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_tod_func (MTD_U16 port, MTD_UINT tod_func, MTD_UINT trig)
{
    MTD_STATUS   retVal = MTD_OK;

    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);

    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC, tod_func);
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC_TRIG, trig);

    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;

    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC_TRIG, 0);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;

#ifdef DEBUG_MTD
    mtd_ptp_1step_print_tai_tod_func_cfg(port);
#endif
    return retVal;
}

/*******************************************************************************
********************************************************************************/

/* set ingress or egress asymmetry */
MTD_STATUS mtd_set_asymmetry(MTD_UINT asym, MTD_PTP_Blk path, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
   /* Both ingress and egress paths */
    if(path == MTD_PTP_igr)
    {
        retVal = mtd_ptp_write_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), asym&0xffff);
        if(retVal!=MTD_OK) return retVal;
        retVal = mtd_ptp_write_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), asym>>16);
        if(retVal!=MTD_OK) return retVal;
    }
    else
    {
        retVal = mtd_ptp_write_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), asym&0xffff);
        if(retVal!=MTD_OK) return retVal;
        retVal = mtd_ptp_write_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), asym>>16);
        if(retVal!=MTD_OK) return retVal;
    }
    return retVal;
}
MTD_UINT mtd_get_asymmetry(MTD_PTP_Blk path, MTD_U16 port)
{
    MTD_UINT  val;

    if(path == MTD_PTP_igr)
    {
        val = mtd_ptp_read_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ));
    }
    else
    {
        val = mtd_ptp_read_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ));
    }
    return val;

}
/* set ingress linkdelay */
MTD_STATUS mtd_set_link_delay(MTD_INT ldelay, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    retVal = mtd_ptp_write_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+26*MTD_PTP_ADDR_ADJ), ldelay&0xffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+27*MTD_PTP_ADDR_ADJ), ldelay>>16);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

MTD_STATUS mtd_msec_set_constant_latency (MTD_U16 port, MTD_UINT flag )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_UINT regval;
    addr = 0xC02;
    regval = mtd_ptp_read_reg (port, addr);

    mtd_msec_bit_write(regval, flag, 16);
    retVal = mtd_ptp_write_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;

    addr = 0x1C0A;
    regval = mtd_ptp_read_reg (port, addr);

    mtd_msec_bit_write(regval, flag, 13);
    retVal = mtd_ptp_write_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;

    return retVal;
}

/*******************************************************************************
* mtd_ptp_print_tai_tod_cfg_gen
*
* DESCRIPTION:
*         Show TAI TOD cfg general
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Show TAI TOD cfg gen */
MTD_STATUS mtd_ptp_print_tai_tod_cfg_gen
(
    IN MTD_U16 port
)
{
#ifdef DEBUG_MTD
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
/*  MTD_UINT addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+ tod_cfg_gen; */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    MTD_INT field;
    MTD_U64 field_val ;
    MTD_DBG_INFO("%x %x\n", addr, regval);
/*  foreach field [array names mtd_tai_tod_cfg_gen_pos] { */
    field = 0;
    field_val = 0;
    while(mtd_tai_tod_cfg_gen_pos[field]!=0)
    {
        field_val = mtd_tai_tod_cfg_gen_extract( field, regval);
        MTD_DBG_INFO("TAI TOD CFG GEN field 0x%x", field_val);
        field++;
    }
#endif
    return MTD_OK;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_mode
*
* DESCRIPTION:
*   Set TAI TOD cfg general
*   clk_mode: 1: clock generation, 2: clock reception, 3: clock reception adv
*
* INPUTS:
*       port - port number
*       clk_mode - clk_mode:
*          1: clock generation, 2: clock reception, 3: clock reception adv
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TAI TOD cfg gen */
/* clk_mode: 1: clock generation, 2: clock reception, 3: clock reception adv */
MTD_STATUS mtd_ptp_set_tai_clk_mode
(
    IN MTD_U16 port,
    IN MTD_INT clk_mode
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, clk_mode);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
/*
  if(retVal!=MTD_OK) return retVal;
  retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
  if(retVal!=MTD_OK) return retVal;
*/
    return retVal;
}

MTD_STATUS mtd_set_ntp_tod_mode (MTD_U16 port, MTD_UINT ntp_mode)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_NTP_TOD_MODE, ntp_mode);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
/*
  if(retVal!=MTD_OK) return retVal;
  retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
  if(retVal!=MTD_OK) return retVal;
*/
    return retVal;
}

/*******************************************************************************
* mtd_ptp_disable_tai_clk_gen
*
* DESCRIPTION:
*    Disable TAI from generating external clock signal,
*    keeping internal clock generation
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Disable TAI from generating external clock signal, keeping internal clock generation */
MTD_STATUS mtd_ptp_disable_tai_clk_gen
(
    IN MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, 0);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, 1);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_gen
*
* DESCRIPTION:
*         Set TAI to generate external clock signal
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TAI to generate external clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_gen
(
    IN MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, 1);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, 1);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_rec
*
* DESCRIPTION:
*         Set TAI to update TOD based on external clock signal
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TAI to update TOD based on external clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_rec
(
    IN MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, 2);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, 1);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_rec_adv
*
* DESCRIPTION:
*         Set TAI to update TOD based and auto adjust frequency based on ext clock signal
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TAI to update TOD based and auto adjust frequency based on ext clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_rec_adv
(
    IN MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, 3);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, 1);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_tai_trig_load_timer
*
* DESCRIPTION:
*         Set TOD func trig to copy LOAD into NEXT RT
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TOD func trig to copy LOAD into NEXT RT */
MTD_STATUS mtd_ptp_tai_trig_load_timer
(
    IN MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC_TRIG, 1);
/* MTD_DBG_CRITIC_INFO("ptp_tai_trig_load_timer set MTD_TOD_FUNC_TRIG %x\n", regval);  */

    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC_TRIG, 0);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);

    return retVal;
}

/*******************************************************************************
* mtd_ptp_print_tai_intr
*
* DESCRIPTION:
*         PrMTD_INT TAI interrupts
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* PrMTD_INT TAI interrupts */
MTD_STATUS mtd_ptp_print_tai_intr
(
    IN MTD_U16 port
)
{
#ifdef DEBUG_MTD
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tai_intr] ] */
    MTD_UINT addr = MTD_TAI_INTR;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    MTD_DBG_INFO("trig_gen_MTD_INT  %d", (regval >> 0)&1);
    MTD_DBG_INFO("pulse_in_MTD_INT  %d", (regval >> 1)&1);
    MTD_DBG_INFO("clk_gen_MTD_INT   %d", (regval >> 2)&1);
    MTD_DBG_INFO("req_drift_MTD_INT %d", (regval >> 3)&1);
#endif
    return MTD_OK;
}

/*******************************************************************************
* mtd_ptp_set_drift_thr_cfg
*
* DESCRIPTION:
*         Set drift threshold config
*
* INPUTS:
*       port - port number
*       minimal_drift - min drift in ns that triggers drift adj
*       drift_thr - min drift in ns that causes interrupt to be invoked to CPU
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set drift threshold config */
/* minimal_drift: min drift in ns that triggers drift adj */
/* drift_thr: min drift in ns that causes interrupt to be invoked to CPU */
MTD_STATUS mtd_ptp_set_drift_thr_cfg
(
    IN MTD_U16 port,
    IN MTD_UINT minimal_drift,
    IN MTD_UINT drift_thr
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list drift_thr_cfg] ] */
    MTD_UINT addr = MTD_DRIFT_THR_CFG;
    retVal = mtd_ptp_writecheck_reg(port, addr, ((minimal_drift&0xff)<<24)|(drift_thr&0xffffff));
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_clock_cyc
*
* DESCRIPTION:
*         Set clock cycle
*        Due to rtl incompleteness, cyc_ns need to be 0,
*        and cyc_s needs to be 2
*
* INPUTS:
*       port - port number
*       cyc_s  - clock cycle seconds
*       cyc_ns - clock cycle nanoseconds
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set clock cycle */
MTD_STATUS mtd_ptp_set_clock_cyc
(
    IN MTD_U16 port,
    IN MTD_UINT cyc_s,
    IN MTD_UINT cyc_ns
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list clock_cyc] ] */
    MTD_UINT addr = MTD_CLOCK_CYC;
    retVal = mtd_ptp_writecheck_reg(port, addr, (cyc_ns<<2)|(cyc_s&0x3));
    return retVal;
}

/*******************************************************************************
* mtd_ptp_go_clock_gen
*
* DESCRIPTION:
*         clock generation setup
*
* INPUTS:
*       port - port number
*       ntTime - next rise time
*       cyc - clock cycle
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* clock generation setup */
MTD_STATUS mtd_ptp_go_clock_gen
(
    IN MTD_U16 port,
    IN MTD_NPTP_TIME_STRUCT *ntTime,
    IN MTD_NPTP_TIME_STRUCT *cyc
)
{
    MTD_STATUS   retVal = MTD_OK;
  /* Disable TAI clock gen first, start internal clock */
    retVal = mtd_ptp_disable_tai_clk_gen(port);
    if(retVal!=MTD_OK) return retVal;
  /* Setup time registers */
    retVal = mtd_set_ptp_tai_timereg(port,  MTD_REG_TOD_0, 0, 0, 0, 0);
    if(retVal!=MTD_OK) return retVal;
/*  retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_NEXT_RT_0*MTD_PTP_ADDR_ADJ, 0, 30, 0, 0);  */
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_NEXT_RT_0, ntTime->highsec, ntTime->lowsec, ntTime->nanosec, ntTime->subnano);
    if(retVal!=MTD_OK) return retVal;
  /* setup clock cycle */
/*  retVal = mtd_ptp_set_clock_cyc(port, 2, 0); */
    retVal = mtd_ptp_set_clock_cyc(port, cyc->lowsec, cyc->nanosec);
    if(retVal!=MTD_OK) return retVal;
  /* trigger loading of NEXT RT */
  /* Start TAI clock gen */
    retVal = mtd_ptp_set_tai_clk_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_go_clock_rec
*
* DESCRIPTION:
*         clock reception setup
*
* INPUTS:
*       port - port number
*       todTime - TOD time
*       ntTime - next rise time
*       cyc - clock cycle
*       deley - clock propagation delay
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* clock reception setup */
MTD_STATUS mtd_ptp_go_clock_rec
(
    IN MTD_U16 port,
    IN MTD_NPTP_TIME_STRUCT *todTime,
    IN MTD_NPTP_TIME_STRUCT *ntTime,
    IN MTD_NPTP_TIME_STRUCT *cyc,
    IN MTD_UINT delay
)
{
    MTD_STATUS   retVal = MTD_OK;
  /* Disable TAI clock gen first, start internal clock */
    retVal = mtd_ptp_disable_tai_clk_gen(port);
    if(retVal!=MTD_OK) return retVal;
  /* Setup time registers */
/*  retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TOD_0*MTD_PTP_ADDR_ADJ, 0xabcd, 0x12345678, 0, 0);  */
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TOD_0, todTime->highsec, todTime->lowsec, todTime->nanosec, todTime->subnano);
    if(retVal!=MTD_OK) return retVal;
  /*  retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_NEXT_RT_0, 0, 30, 0);  */
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_NEXT_RT_0, ntTime->highsec, ntTime->lowsec, ntTime->nanosec, ntTime->subnano);
    if(retVal!=MTD_OK) return retVal;
  /* setup clock cycle */
/*  retVal = mtd_ptp_set_clock_cyc(port, 2, 0); */
    retVal = mtd_ptp_set_clock_cyc(port, cyc->lowsec, cyc->nanosec);
    if(retVal!=MTD_OK) return retVal;

  /* Start TAI clock reception */
    retVal = mtd_ptp_set_tai_clk_rec(port);

    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_pclk_period
*
* DESCRIPTION:
*         set pclk period
*
* INPUTS:
*       port - port number
*       period - pclk period
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set pclk period */
MTD_STATUS mtd_ptp_set_pclk_period
(
    IN MTD_U16 port,
    IN MTD_INT period
)
{
    MTD_STATUS   retVal = MTD_OK;
    retVal = mtd_set_ptp_tai_reg(port,  MTD_REG_PCLK_CFG*MTD_PTP_ADDR_ADJ, (period << 1) | 1);
    return retVal;
}
/* pclk period generated by 1548P Z1 ASIC is actually  */
/* 8ns more than pclk_cfg setting so write a pclk_cfg  */
/* setting that is 8ns less than what you want */

/*******************************************************************************
* mtd_ptp_set_pclk_freq
*
* DESCRIPTION:
*         set pclk period to 10Mhz
*
* INPUTS:
*       port - port number
*       freq - pclk period
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set pclk period to 10Mhz */
MTD_STATUS mtd_ptp_set_pclk_freq
(
    IN MTD_U16 port,
    IN MTD_INT freq
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT period = (1000000000/freq);
    MTD_DBG_INFO("Setting PCLK frequency to %d HZ", freq);
    retVal = mtd_ptp_set_pclk_period(port, period-8);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_pulse_delay_en
*
* DESCRIPTION:
*         Set pulse delay enable. If set to 1, pulse_delay will be added to TOD_LOAD
*         when doing UPDATE operation.
*
* INPUTS:
*       port - port number
*        en - pulse_delay
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_pulse_delay_en (MTD_U16 port, MTD_BOOL en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT data = mtd_ptp_readcheck_reg(port, addr);
    mtd_msec_bit_write(data,en,15);
    retVal = mtd_ptp_writecheck_reg(port, addr, data);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_tai_pulse_delay_en
*
* DESCRIPTION:
*         Get pulse delay enable. If set to 1, pulse_delay will be added to TOD_LOAD
*         when doing UPDATE operation.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        en - pulse_delay
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_pulse_delay_en (MTD_U16 port, MTD_BOOL *en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT data = mtd_ptp_readcheck_reg(port, addr);
    if(data&0x8000)
        *en = MTD_TRUE;
    else
        *en = MTD_FALSE;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_pulse_delay
*
* DESCRIPTION:
*         Set pulse delay
*
* INPUTS:
*       port - port number
*        val - pulse delay value
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_pulse_delay (MTD_U16 port, MTD_UINT val)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list pulse_delay] ] */
/*   MTD_UINT addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+ pulse_delay; */
    MTD_UINT addr = MTD_PULSE_DELAY;
/*  MTD_UINT cnt = mtd_ptp_read_reg (port, addr); */
/*   writecheck_reg addr val */
    retVal = mtd_ptp_writecheck_reg(port, addr, val);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_tai_pulse_delay
*
* DESCRIPTION:
*         Get pulse delay
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_tai_pulse_delay
(
    IN MTD_U16 port
)
{
//#ifdef DEBUG_MTD
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list pulse_delay] ] */
    MTD_UINT addr = MTD_PULSE_DELAY;
    MTD_UINT cnt = 0;
    cnt = mtd_ptp_read_reg (port, addr);
    MTD_DBG_INFO("%08h (%d)", cnt, cnt);
//#endif
    return MTD_OK;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_delay_en
*
* DESCRIPTION:
*         Set clock delay enable. If set to 1, clk_delay will be used to compensate
*         TOD alignment clock delay
*
* INPUTS:
*       port - port number
*        en - clk_delay
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_clk_delay_en (MTD_U16 port, MTD_BOOL en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT data = mtd_ptp_readcheck_reg(port, addr);
    mtd_msec_bit_write(data,en,14);
    retVal = mtd_ptp_writecheck_reg(port, addr, data);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_tai_clk_delay_en
*
* DESCRIPTION:
*         Get clock delay enable. If set to 1, clk_delay will be used to compensate
*         TOD alignment clock delay
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        en - clk_delay
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_clk_delay_en (MTD_U16 port, MTD_BOOL *en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT data = mtd_ptp_readcheck_reg(port, addr);
    if(data&0x4000)
        *en = MTD_TRUE;
    else
        *en = MTD_FALSE;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai_clk_delay
*
* DESCRIPTION:
*         Set clock delay
*
* INPUTS:
*       port - port number
*        val - pulse delay value
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_clk_delay (MTD_U16 port, MTD_UINT val)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_CLK_DELAY;
    retVal = mtd_ptp_writecheck_reg(port, addr, val);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_tai_clk_delay
*
* DESCRIPTION:
*         Get clock delay
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_tai_clk_delay
(
    IN MTD_U16 port
)
{
//#ifdef DEBUG_MTD
    MTD_UINT addr = MTD_CLK_DELAY;
    MTD_UINT cnt = 0;
    cnt = mtd_ptp_read_reg (port, addr);
    MTD_DBG_INFO("%08h (%d)", cnt, cnt);
//#endif
    return MTD_OK;
}

/*******************************************************************************
* mtd_ptp_enable_tai
*
* DESCRIPTION:
*         Enable TAI
*
* INPUTS:
*      port - port number
*      kpTodCfg    - keep original TOD comfiguration
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_enable_tai
(
    IN MTD_U16 port,
    IN MTD_UINT kpTodCfg
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    retVal = mtd_ptp_writecheck_reg(port, addr, kpTodCfg);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_disable_tai
*
* DESCRIPTION:
*         Disable TAI
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*      kpTodCfg    - keep original TOD comfiguration
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_disable_tai
(
    IN MTD_U16 port,
    OUT MTD_UINT *kpTodCfg
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    *kpTodCfg = regval;
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, 0);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, 0);
//  regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_EN_SYNCE_TAI_CLK, 0);
//  regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_EXT_CLK_EN, 0);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_tai
*
* DESCRIPTION:
*         Set TAI TOD cfg
*
* INPUTS:
*       port - port number
*       clk_mode -
*       in_clk_en -
*       tai_clkout_sel - It is useless for 10G mode
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_set_tai
(
    IN MTD_U16 port,
    IN MTD_INT clk_mode,
    IN MTD_INT in_clk_en,
    IN MTD_INT tai_clkout_sel
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_cfg_gen] ] */
    MTD_UINT addr = MTD_TOD_CFG_GEN;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_CLK_MODE, clk_mode);
    regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_IN_CLK_EN, in_clk_en);
//  regval = mtd_tai_tod_cfg_gen_set_field(regval,  MTD_TAI_CLKOUT_SEL, tai_clkout_sel);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_print_tai_tod_cfg_gen(port);
    if(retVal!=MTD_OK) return retVal;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_tai_get_timer_operation
*
* DESCRIPTION:
*         Get tod function timer operation
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       timerOp - timer operation
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_get_timer_operation
(
    IN MTD_U16 port,
    OUT MTD_TOD_FUNC_TIMER_OP *timerOp
)
{
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    *timerOp = mtd_tai_tod_func_cfg_extract( MTD_TAI_TOD_TOD_FUNC, regval);
    return MTD_OK;
}

/*******************************************************************************
* mtd_ptp_tai_set_timer_operation
*
* DESCRIPTION:
*         Set tod function timer operation
*
* INPUTS:
*       port - port number
*       timerOp - timer operation
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_set_timer_operation
(
    IN MTD_U16 port,
    IN MTD_TOD_FUNC_TIMER_OP timerOp
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TOD_FUNC, timerOp);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_tai_set_pulse_width
*
* DESCRIPTION:
*         Set pulse width
*
* INPUTS:
*       port - port number
*       width_ns - width nanoseconds
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_set_pulse_width
(
    IN MTD_U16 port,
    IN MTD_UINT width_ns
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_PULSE_WIDTH, (width_ns*10/MTD_PTP_CYCLE)+1);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_tai_get_pulse_width
*
* DESCRIPTION:
*         Get pulse width
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       width_ns - width nanoseconds
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_get_pulse_width
(
    IN MTD_U16 port,
    OUT MTD_UINT *width_ns
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    *width_ns = mtd_tai_tod_func_cfg_extract( MTD_TAI_TOD_PULSE_WIDTH, regval);
    if(*width_ns>0)
    {
        *width_ns -= 1;
        *width_ns *= MTD_PTP_CYCLE;
        *width_ns /=10;
    }
    else
    {
        *width_ns = 0;
    }
    return retVal;
}

/*******************************************************************************
* mtd_ptp_tai_set_trig_gen_en
*
* DESCRIPTION:
*         Set enable trig generator gen
*
* INPUTS:
*       port - port number
*       bitval -
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_set_trig_gen_en
(
    IN MTD_U16 port,
    IN MTD_INT bitval
)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);
    regval = mtd_tai_tod_func_cfg_set_field(regval, MTD_TAI_TOD_TRIG_GEN_EN, bitval);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    return retVal;
}

static MTD_UINT ptpGetMask(MTD_INT value)
{
    MTD_UINT data = 0;
    MTD_UINT mask = 0;
    while(value)
    {
        data +=1;
        value>>=1;
    }
    if(data)
    {
/*    mask =1<<data; */
        mask =1<<(data-1);
        mask = mask - 1;
    }
    return mask;
}

/*******************************************************************************
* mtd_ptp_get_pulse_gen
*
* DESCRIPTION:
*        Get pulse generation setup (master)
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       width_ns - width nanoseconds
*       trigsec - trigger time seconds
*       trignsec - trigger time nenoseconds
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* get pulse generation setup (master) */
MTD_STATUS mtd_ptp_get_pulse_gen (MTD_U16 port, MTD_UINT* width_ns, MTD_UINT* trigsec, MTD_UINT* trignsec)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT sechi, fnsec;

  /* get pulse length */
    retVal = mtd_ptp_tai_get_pulse_width(port,  width_ns);
    if(retVal!=MTD_OK) return retVal;
/*MTD_DBG_CRITIC_INFO("trig pulse width %x nsec\n", *width_ns); */

    retVal = mtd_get_ptp_tai_timereg(port, MTD_REG_TRIG_GEN_TOD_0,&sechi, (MTD_UINT *)trigsec, (MTD_UINT *)trignsec, &fnsec);
    if(retVal!=MTD_OK) return retVal;
/*MTD_DBG_CRITIC_INFO("trig time %x %x sec %x nsec %x fsec\n", sechi, *trigsec, *trignsec, fnsec); */

    return retVal;
}


/*******************************************************************************
* mtd_ptp_go_pulse_gen
*
* DESCRIPTION:
*         pulse generation setup (master)
*
* INPUTS:
*       port - port number
*       width_ns - width nanoseconds
*       trigsec - trigger time seconds
*       trignsec - trigger time nenoseconds
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* pulse generation setup (master) */
MTD_STATUS mtd_ptp_go_pulse_gen (MTD_U16 port, MTD_INT width_ns, MTD_INT trigsec, MTD_INT trignsec)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT sechi, seclo, nsec, fnsec, secMask, nsecMask;
    MTD_UINT kpTodCfg;

  /* disable tai  */
    retVal = mtd_ptp_disable_tai(port, &kpTodCfg);
    if(retVal!=MTD_OK) return retVal;

  /* set pulse length */
    retVal = mtd_ptp_tai_set_pulse_width(port,  width_ns);
    if(retVal!=MTD_OK) return retVal;

  /* set trig_gen_en */
    retVal = mtd_ptp_tai_set_trig_gen_en(port,  1);
    if(retVal!=MTD_OK) return retVal;

  /* set Trig TOD */
    sechi = 0;
    seclo = trigsec;
    nsec = trignsec;
    fnsec = 0;

    MTD_DBG_CRITIC_INFO("trig time %x %x sec %x nsec %x fsec\n", sechi, seclo, nsec, fnsec);
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TRIG_GEN_TOD_0, sechi, seclo, nsec, fnsec);
    if(retVal!=MTD_OK) return retVal;

  /* set TGT mask*/
    secMask=ptpGetMask(trigsec);
    if((secMask)||(trigsec))
    {
        nsecMask=0xffffffff;
    }
    else
    {
        nsecMask=ptpGetMask(trignsec);
    }

    nsecMask = nsecMask & ~( ptpGetMask(width_ns));

    MTD_DBG_CRITIC_INFO("mask time %x %x sec %x nsec %x fsec\n", 0, secMask, nsecMask, 0);
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TRIG_GEN_MSK_0, 0, secMask, nsecMask, 0);
    if(retVal!=MTD_OK) return retVal;
  /* enable tai pulse generation with internal clock */
    retVal = mtd_ptp_enable_tai(port, kpTodCfg);
/*  retVal = mtd_ptp_set_tai(port, 0, 0, 0); */
    if(retVal!=MTD_OK) return retVal;

    return retVal;
}


/*******************************************************************************
* mtd_ptp_go_pulse_rec
*
* DESCRIPTION:
*         pulse reception setup (slave)
*
* INPUTS:
*       port - port number
*       delay - Pulse delay time
*       nextTime - Next Rise time
*       ldTime - load time
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* pulse reception setup (slave) */
MTD_STATUS mtd_ptp_go_pulse_rec (MTD_U16 port, MTD_INT delay, MtdPtpTimeStruct *nextTime, MtdPtpTimeStruct * ldTime)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT kpTodCfg;
  /* disable tai */
    retVal = mtd_ptp_disable_tai(port, &kpTodCfg);
    if(retVal!=MTD_OK) return retVal;
  /* clear pulse counter */
    retVal = mtd_set_tai_pulse_in_cnt(port, 0);
    if(retVal!=MTD_OK) return retVal;
  /* set the pulse delay (in ns) */
/*  retVal = mtd_set_tai_pulse_delay(port, 1000000000); */
    retVal = mtd_set_tai_pulse_delay(port, delay);
    if(retVal!=MTD_OK) return retVal;
  /* set the NRT with a bogus value */
/*  retVal = mtd_set_ptp_tai_timereg(port,  MTD_REG_NEXT_RT_0*MTD_PTP_ADDR_ADJ, 0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4, 0); */
    retVal = mtd_set_ptp_tai_timereg(port,  MTD_REG_NEXT_RT_0, nextTime->sec_hi, nextTime->sec_lo, nextTime->nanosec, nextTime->frec);
    if(retVal!=MTD_OK) return retVal;
  /* set TLV with the same value set in the TGT of the master */
/*  retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TOD_LOAD_0*MTD_PTP_ADDR_ADJ, 0, 10, 0, 0); */
    retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TOD_LOAD_0, ldTime->sec_hi, ldTime->sec_lo, ldTime->nanosec, ldTime->frec);
    if(retVal!=MTD_OK) return retVal;
  /* enable tai pulse reception with internal clock (is this really needed?) Need to set correct pulse_in_sel !! */
  /* mtd_set_tai 2 1 0 */

  /* make sure that the NRT is set with TLV+pulse_delay when the pulse arrives */
  /* enable tai pulse generation with internal clock */
    retVal = mtd_ptp_enable_tai(port, kpTodCfg);
/*  retVal = mtd_ptp_set_tai(port, 0, 0, 0); */
    if(retVal!=MTD_OK) return retVal;

    return retVal;
}

/*******************************************************************************
* mtd_set_ptp_tai_tod
*
* DESCRIPTION:
*       Set TOD
*
* INPUTS:
*       port - port number
*       ns - nanoseconds of TOD
*       sec_lo - low seconds of TOD
*       sec_hi - high seconds of TOD
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set TOD */
MTD_STATUS mtd_set_ptp_tai_tod
(
    IN MTD_U16 port,
    IN MTD_UINT ns,
    IN MTD_UINT sec_lo,
    IN MTD_UINT sec_hi
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT kpTodCfg;
  /* disable tai */
    retVal = mtd_ptp_disable_tai(port, &kpTodCfg);
    if(retVal!=MTD_OK) return retVal;

    retVal = _mtd_set_ptp_tai_tod (port, ns, sec_lo, sec_hi);
    if(retVal!=MTD_OK) return retVal;

  /* enable tai pulse generation with internal clock */
    retVal = mtd_ptp_enable_tai(port, kpTodCfg);
/*  retVal = mtd_ptp_set_tai(port, 0, 0, 0); */
    if(retVal!=MTD_OK) return retVal;
    return retVal;
    return retVal;
}


/*******************************************************************************
* mtd_ptp_set_drift_adj
*
* DESCRIPTION:
*       Clock drift adjustment
*
* INPUTS:
*       port - port number
*       drift_base_adj_sl - base drift adjust low sec
*       drift_base_adj_ns - base drift adjust ns (include sign)
*       drift_base_adj_fs - base drift adjust fs
*       drift_fine_adj_fs - fine drift adjust fs
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set drift adjustment */
MTD_STATUS mtd_ptp_set_drift_adj
(
    IN MTD_U16 port,
    IN MTD_INT drift_base_adj_sl,
    IN MTD_INT drift_base_adj_ns,
    IN MTD_INT drift_base_adj_fs,
    IN MTD_INT drift_fine_adj_fs
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT kpTodCfg;
  /* disable tai */
    retVal = mtd_ptp_disable_tai(port, &kpTodCfg);
    if(retVal!=MTD_OK) return retVal;
/*
MTD_DBG_CRITIC_INFO("\n!!!!!^^^^^^^^^^^^^^^^^^^^^^^^^^^^!!!!!!!!!!!!!!!!!!!\n");
#ifdef DEBUG_MTD
printf("!!!!! mtd_ptp_set_drift_adj %x %x %x %x\n", drift_base_adj_sl, drift_base_adj_ns, drift_base_adj_fs, drift_fine_adj_fs);
#else
printk("!!!!! mtd_ptp_set_drift_adj %x %x %x %x\n", drift_base_adj_sl, drift_base_adj_ns, drift_base_adj_fs, drift_fine_adj_fs);
#endif
MTD_DBG_CRITIC_INFO("!!!!! mtd_ptp_set_drift_adj %x %x %x %x\n", drift_base_adj_sl, drift_base_adj_ns, drift_base_adj_fs, drift_fine_adj_fs);
*/

/*MTD_DBG_CRITIC_INFO("\n!!!!!! disable TAI done !!!!!!!!!\n");  */
    if(!((drift_base_adj_sl==0)&& (drift_base_adj_ns==0)&& (drift_base_adj_fs==0)))
    {
        MTD_INT ns;
        ns = (drift_base_adj_ns>0)?drift_base_adj_ns:-drift_base_adj_ns;
        retVal = mtd_set_ptp_tai_timereg(port, MTD_REG_TOD_LOAD_0, 0, drift_base_adj_sl, ns, drift_base_adj_fs);
        if(retVal!=MTD_OK) return retVal;
/*   MTD_DBG_CRITIC_INFO("set_ptp_tai_timereg MTD_TOD_LOAD read 0x%08x 0x%08x 0x%08x 0x%08x\n", mtd_ptp_read_reg (port, MTD_TOD_LOAD_0),  mtd_ptp_read_reg (port, MTD_TOD_LOAD_1), mtd_ptp_read_reg (port, MTD_TOD_LOAD_2),  mtd_ptp_read_reg (port, MTD_TOD_LOAD_3)); */

        {
            MTD_UINT addr = MTD_TOD_FUNC_CFG;
            MTD_UINT regval = mtd_ptp_read_reg (port, addr);
            regval = regval & ~0xc0000000 ;
            if(drift_base_adj_ns>0)
            {
/*      regval = regval | 0x40000000 ; */
                regval = regval | 0x80000000 ;
            }
            else
            {
                regval = regval | 0x40000000 ;
/*      regval = regval | 0x80000000  */;
            }

            regval = regval | 0x10000000 ;
            MTD_DBG_CRITIC_INFO("!!!!! mtd_ptp_set_drift_adj trig config %x addr %xn", regval, addr);
            retVal = mtd_ptp_writecheck_reg(port, addr, regval);

            if(retVal!=MTD_OK) return retVal;
            regval = regval & ~0x10000000 ;
            retVal = mtd_ptp_writecheck_reg(port, addr, regval);


        }

    }

    if(!((drift_fine_adj_fs==0)))
    {

        static MTD_INT last_drift_fine_adj_fs;
/*
#ifdef DEBUG_MTD
printf("\n!!!!!set_drift_adj %x !!!!!!!!!\n", drift_fine_adj_fs);
#else
printk("\n!!!!!set_drift_adj %x !!!!!!!!!\n", drift_fine_adj_fs);
#endif
*/
        if(drift_fine_adj_fs!=last_drift_fine_adj_fs)
        {
/*   MTD_DBG_CRITIC_INFO("\n************ mtd_set_drift_adj 0x%08x \n", drift_fine_adj_fs); */
            retVal = mtd_set_drift_adj(port, drift_fine_adj_fs);
            if(retVal!=MTD_OK) return retVal;
            last_drift_fine_adj_fs = drift_fine_adj_fs;
        }
/*    retVal = mtd_set_drift_adj_step(port,  0); */
    }

  /* enable tai pulse generation with internal clock */
    retVal = mtd_ptp_enable_tai(port, kpTodCfg);
/*  retVal = mtd_ptp_set_tai(port, 0, 0, 0);  */
    if(retVal!=MTD_OK) return retVal;
    return retVal;

    return retVal;
}
/*******************************************************************************
* mtd_ptp_get_drift_adj
*
* DESCRIPTION:
*    Get clock drift adjustment
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       drift_base_adj_sl - base drift adjust low sec
*       drift_base_adj_ns - base drift adjust ns (include sign)
*       drift_base_adj_fs - base drift adjust fs
*       drift_fine_adj_fs - fine drift adjust fs
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set drift adjustment */
MTD_STATUS mtd_ptp_get_drift_adj
(
    IN MTD_U16 port,
    OUT MTD_INT *drift_base_adj_sl,
    OUT MTD_INT *drift_base_adj_ns,
    OUT MTD_INT *drift_base_adj_fs,
    OUT MTD_INT *drift_fine_adj_fs
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_TOD_FUNC_TIMER_OP  timeOp;
    MTD_UINT sec_hi;
/*MTD_DBG_CRITIC_INFO("!!!!! mtd_ptp_get_drift_adj %x %x\n", drift_base_adj_fs,drift_fine_adj_fs); */

    retVal = mtd_get_ptp_tai_timereg(port, MTD_REG_TOD_LOAD_0, &sec_hi, (MTD_UINT *) drift_base_adj_sl,(MTD_UINT *) drift_base_adj_ns, (MTD_UINT *)drift_base_adj_fs);
    if(retVal!=MTD_OK) return retVal;
/*MTD_DBG_CRITIC_INFO("get_ptp_tai_timereg MTD_TOD_LOAD read 0x%08x 0x%08x 0x%08x 0x%08x\n", sec_hi, sec_lo, *drift_base_adj_ns, *drift_base_adj_fs); */
    retVal = mtd_ptp_tai_get_timer_operation(port, &timeOp);

/*MTD_DBG_CRITIC_INFO("!!!!! mtd_ptp_tai_get_timer_operation %x\n", timeOp); */
    if(timeOp==MTD_TOD_FUNC_TIMER_DEC)
    {
        *drift_base_adj_ns = -(*drift_base_adj_ns);
    }

    retVal = mtd_get_drift_adj(port, (MTD_UINT *)drift_fine_adj_fs);
/*MTD_DBG_CRITIC_INFO("!!!!! mtd_get_drift_adj %x\n", drift_fine_adj_fs);  */
    MTD_DBG_CRITIC_INFO("!!!!! mtd_ptp_get_drift_adj %x %x %x %x\n", *drift_base_adj_sl, *drift_base_adj_ns, *drift_base_adj_fs, *drift_fine_adj_fs);
    return retVal;
}

/* PTP Interrupt */
/*******************************************************************************
* mtd_get_ptp_intr_msk
*
* DESCRIPTION:
*         Get new PTP interrupt mask.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
*
* OUTPUTS:
*       mask  - New PTP interrupt mask.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_intr_msk ( MTD_U16 port, MTD_PTP_Blk path, MTD_UINT *mask)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;
    MTD_UINT data;

    MTD_DBG_INFO("Get PTP Interrupt mask (port %d, path %d)\n", port, path);
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET_MSK;

    data = mtd_ptp_read_reg (port, reg_addr);
    data &= 0xffff;
    *mask = data;

    return retVal;
}

/*******************************************************************************
* mtd_set_ptp_intr_msk
*
* DESCRIPTION:
*         Set new PTP interrupt mask.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
*       mask  - New PTP interrupt mask.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_ptp_intr_msk ( MTD_U16 port, MTD_PTP_Blk path, MTD_UINT mask)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;
    MTD_UINT data;

    MTD_DBG_INFO("Set PTP Interrupt mask (port %d, path %d mask %x)\n", port, path,mask);
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET_MSK;

    data = mtd_ptp_read_reg (port, reg_addr);
    data &= 0xffff;
    MTD_DBG_CRITIC_INFO("port%d path %d old int_set_msk %04x = %08x\n", port, path, reg_addr, data);
    retVal = mtd_ptp_write_reg(port, reg_addr,mask);
    data = mtd_ptp_read_reg (port, reg_addr);
    data &= 0xffff;
    MTD_DBG_CRITIC_INFO("port%d path %d new int_set_msk %04x = %08x\n", port, path, reg_addr, data);

    return retVal;
}

/*******************************************************************************
* mtd_disable_ptp_watchdog_timer
*
* DESCRIPTION:
*         Set new PTP mtd_ptp_watchdog_timer disable.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_disable_ptp_watchdog_timer ( MTD_U16 port, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;

    MTD_DBG_INFO("Set PTP watchdog timer disable (port %d, path %d)\n", port, path);
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TIMEOUT_CTL;

    retVal = mtd_ptp_write_reg(port, reg_addr,0);

    return retVal;
}

#ifdef bit_get
#define nptp_bit_get bit_get
#else
#define MTD_PTP_BIT(x)           ((MTD_UINT)0x00000001 << (x))
#define nptp_bit_get(p,x)     (((p) &  (MTD_PTP_BIT(x))) >> (x))
#endif

/*******************************************************************************
* mtd_get_ptp_interrupts
*
* DESCRIPTION:
*         Get new PTP interrupts.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        igrMTD_INT - IGR interupts
*        egrMTD_INT - EGR interupts
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_interrupts (MTD_U16 port, MTD_UINT *igrInt, MTD_UINT *egrInt)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;
    MTD_UINT data;

    MTD_DBG_INFO("Get PTP Interrupt (port %d)\n", port);
    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET;

    data = mtd_ptp_read_reg (port, reg_addr);
    *igrInt = data&0xffff;
    MTD_DBG_CRITIC_INFO("port%d igr int_set %04x = %08x\n", port, reg_addr, data);
    MTD_DBG_CRITIC_INFO("%04x %04x\n", reg_addr, data);
    MTD_DBG_CRITIC_INFO("test %X\n", (MTD_UINT)nptp_bit_get(data, 15));
    MTD_DBG_CRITIC_INFO("si_rw_err  %X\n", (MTD_UINT)nptp_bit_get(data, 14));
    MTD_DBG_CRITIC_INFO("late_dispatch %X\n", (MTD_UINT)nptp_bit_get(data, 13));
    MTD_DBG_CRITIC_INFO("stat_full %X\n", (MTD_UINT)nptp_bit_get(data, 10));
    MTD_DBG_CRITIC_INFO("stat_almost_full %X\n", (MTD_UINT)nptp_bit_get(data, 9));
    MTD_DBG_CRITIC_INFO("instr_ppe_req  %X\n", (MTD_UINT)nptp_bit_get(data, 8));
    MTD_DBG_CRITIC_INFO("parser_ppe_instr  %X\n", (MTD_UINT)nptp_bit_get(data, 7));
    MTD_DBG_CRITIC_INFO("instr_ppe_timeout  %X\n", (MTD_UINT)nptp_bit_get(data, 6));
    MTD_DBG_CRITIC_INFO("instr_err  %X\n", (MTD_UINT)nptp_bit_get(data, 5));
    MTD_DBG_CRITIC_INFO("ppd_timeout %X\n", (MTD_UINT)nptp_bit_get(data, 4));
    MTD_DBG_CRITIC_INFO("ts_low_act %X\n", (MTD_UINT)nptp_bit_get(data, 3));
    MTD_DBG_CRITIC_INFO("ts_high_act %X\n", (MTD_UINT)nptp_bit_get(data, 2));
    MTD_DBG_CRITIC_INFO("ts_low_full %X\n", (MTD_UINT)nptp_bit_get(data, 1));
    MTD_DBG_CRITIC_INFO("ts_high_full %X\n", (MTD_UINT)nptp_bit_get(data, 0));
    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET;

    data = mtd_ptp_read_reg (port, reg_addr);
    *egrInt = data&0xffff;
    MTD_DBG_CRITIC_INFO("port%d egr int_set %04x = %08x\n", port, reg_addr, data);
    MTD_DBG_CRITIC_INFO("%04x %04x", reg_addr, data);
    MTD_DBG_CRITIC_INFO("%04x %04x", reg_addr, data);

    MTD_DBG_CRITIC_INFO("test %X\n", (MTD_UINT)nptp_bit_get(data, 15));
    MTD_DBG_CRITIC_INFO("si_rw_err  %X\n", (MTD_UINT)nptp_bit_get(data, 14));
    MTD_DBG_CRITIC_INFO("late_dispatch %X\n", (MTD_UINT)nptp_bit_get(data, 13));
    MTD_DBG_CRITIC_INFO("stat_full %X\n", (MTD_UINT)nptp_bit_get(data, 10));
    MTD_DBG_CRITIC_INFO("stat_almost_full %X\n", (MTD_UINT)nptp_bit_get(data, 9));
    MTD_DBG_CRITIC_INFO("instr_ppe_req  %X\n", (MTD_UINT)nptp_bit_get(data, 8));
    MTD_DBG_CRITIC_INFO("parser_ppe_instr  %X\n", (MTD_UINT)nptp_bit_get(data, 7));
    MTD_DBG_CRITIC_INFO("instr_ppe_timeout  %X\n", (MTD_UINT)nptp_bit_get(data, 6));
    MTD_DBG_CRITIC_INFO("instr_err  %X\n", (MTD_UINT)nptp_bit_get(data, 5));
    MTD_DBG_CRITIC_INFO("ppd_timeout %X\n", (MTD_UINT)nptp_bit_get(data, 4));
    MTD_DBG_CRITIC_INFO("ts_low_act %X\n", (MTD_UINT)nptp_bit_get(data, 3));
    MTD_DBG_CRITIC_INFO("ts_high_act %X\n", (MTD_UINT)nptp_bit_get(data, 2));
    MTD_DBG_CRITIC_INFO("ts_low_full %X\n", (MTD_UINT)nptp_bit_get(data, 1));
    MTD_DBG_CRITIC_INFO("ts_high_full %X\n", (MTD_UINT)nptp_bit_get(data, 0));
    return retVal;
}


/*******************************************************************************
* mtd_clear_ptp_interrupts
*
* DESCRIPTION:
*         Clear new PTP interrupts.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_clear_ptp_interrupts ( MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;

    MTD_DBG_INFO("PTP IGR clearing interrupts (port %d)\n", port);
    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET;
    retVal = mtd_ptp_write_reg(port, reg_addr, 0xffffffff);
    if(retVal!=MTD_OK) return retVal;

    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_INTR_SET;
    retVal = mtd_ptp_write_reg(port, reg_addr, 0xffffffff);

    return retVal;
}

/*******************************************************************************
* mtd_set_tai_intr_msk
*
* DESCRIPTION:
*         Set new PTP TAI interrupt mask.
*
* INPUTS:
*       port - port number
*       mask  - New PTP TAI interrupt mask.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_intr_msk (MTD_U16 port, MTD_UINT mask)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr = MTD_TAI_INTR_MASK;
    MTD_UINT data;

    data = mtd_ptp_read_reg(port, reg_addr);
    data &= ~0xf;
    retVal = mtd_ptp_write_reg(port, reg_addr, data | (mask&0xf));
    return retVal;
}

/*******************************************************************************
* mtd_get_tai_intr_msk
*
* DESCRIPTION:
*         Get new PTP TAI interrupt mask.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       mask  - New PTP TAI interrupt mask.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_intr_msk (MTD_U16 port, MTD_UINT *mask)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr = MTD_TAI_INTR_MASK;

    *mask = mtd_ptp_read_reg(port, reg_addr);
    *mask &= 0xf;
    return retVal;
}

/*******************************************************************************
* mtd_ptp_global_intr_en
*
* DESCRIPTION:
*         Set new PTP Global interrupt enable.
*
* INPUTS:
*       port - port number
*       en  - New PTP interrupt enable/disable.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_global_intr_en ( MTD_U16 port, MTD_INT en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;
    MTD_UINT data;

    MTD_DBG_INFO("PTP set PTP interrupt enable (port %d enable %x)\n", port, en&1);
    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_CFG_GEN;
    data = mtd_ptp_read_reg(port, reg_addr);
    data &= ~0x2;
    if(en)
        data |= 2;
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    if(retVal!=MTD_OK) return retVal;

    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_CFG_GEN;
    data = mtd_ptp_read_reg(port, reg_addr);
    data &= ~0x2;
    if(en)
        data |= 2;
    retVal = mtd_ptp_write_reg(port, reg_addr, data);

    return retVal;
}

/*******************************************************************************
* mtd_prgm_ptp_lut_ent_msgType
*
* DESCRIPTION:
*         program an lut entry that matches on specified msgtype and actions
*        msgid: 0 - Sync, 1 - DelayReq, 2 - PdelayReq, 3 - PdelayResp
*               8 - FollowUp, 9 - DelayResp, A - PdelayRespFU,
*               B - Announce, C - Signaling, D - Management
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       msgId - PTP Message Id.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_ptp_lut_ent_msgType(MTD_U16 port, MTD_INT idx, MTD_PTPv2_message_type msgId, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_ptp_lut_ent_msgType port %d path %d idx %d msgId %d action %x\n", port, path, idx, msgId, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
    lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, msgId);
    lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_ptp_lut_ent_domain_num
*
* DESCRIPTION:
*     program an lut entry that matches on specified domain number and actions
*     domain_num: domain number used as lut key
*     Action abreviation
*     DR - drop, INI - IniPiggyback, INS - InsertTST
*     SH - StampHigh, AA - AddAsymmetry, NO - no action
*     multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       domain_num - PTP domain number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_ptp_lut_ent_domain_num(MTD_U16 port, MTD_INT idx, MTD_INT domain_num, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_ptp_lut_ent_domain_num port %d path %d idx %d domain_num %d action %x\n", port, path, idx, domain_num, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
    lut_key_top = (MTD_U32)mtd_ptp_lut_key_adjust(MTD_K_DomainNumber, domain_num);
    lut_vld_top = (MTD_U32)mtd_ptp_vld_key_adjust(MTD_K_DomainNumber);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}

/*******************************************************************************
* mtd_prgm_ptp_lut_ent_transspec
*
* DESCRIPTION:
*         program an lut entry that matches on specified transspec and actions
*        multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       transspec - PTP transspec.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_ptp_lut_ent_transspec(MTD_U16 port, MTD_INT idx, MTD_INT transspec, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_ptp_lut_ent_transspec port %d path %d idx %d transspec %d action %x\n", port, path, idx, transspec, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
    lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_TransportSpecific, transspec);
    lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_TransportSpecific);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_ipv4
*
* DESCRIPTION:
*         program an lut entry that matches IPV4 and actions
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_ipv4(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_ipv4 port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagIPv4, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagIPv4);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_ntp
*
* DESCRIPTION:
*         program an lut entry that matches NTP and actions
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*       ext_dev - extend device
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_ntp(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path, MTD_INT ext_dev)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_ntp port %d path %d idx %d action %x ext_dev %d\n", port, path, idx, actions, ext_dev);

    if(ext_dev==0)
    {
        lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagNTP, 1);
        lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagNTP);
    }
    else
    {
        lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv1, 1);
        lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv1);
    }

    lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
    lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);
    if((path== MTD_PTP_egr)&&(actions!= MTD_PTP_Act_No_Action))
        lut_act |= mtd_prgm_ptp_get_lut_actions(MTD_PTP_Act_HoldForTransmission);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_ntp_list
*
* DESCRIPTION:
*         program an lut entry that matches NTP and actions
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - List of  Lut actions. The last action is MTD_PTP_Act_No_Action.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*       ext_dev - extend device
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_ntp_list(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACT *actions, MTD_PTP_Blk path, MTD_INT ext_dev)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT i;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_ntp port %d path %d idx %d action %x\n", port, path, idx, *actions);

    if(ext_dev==0)
    {
        lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagNTP, 1);
        lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagNTP);
    }
    else
    {
        lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv1, 1);
        lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv1);
    }
    lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
    lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
    lut_act = 0LL;
    i=0;
    do
    {
        lut_act |= mtd_prgm_ptp_get_lut_act(actions[i]);
        i++;
    }while(actions[i] != MTD_PTP_Act_No_Action);

    if((path== MTD_PTP_egr)&&(i>0))
        lut_act |= mtd_prgm_ptp_get_lut_act(MTD_PTP_Act_HoldForTransmission);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}




/*******************************************************************************
* mtd_prgm_lut_ent_ptpv2
*
* DESCRIPTION:
*         program an lut entry that matches PTPv2 and actions
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_ptpv2(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_ptpv2 port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_ptpv1
*
* DESCRIPTION:
*         program an lut entry that matches PTPv1 and actions
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_ptpv1(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_ptpv1 port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv1, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv1);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/* use the IP-in-IP for Y1731 */
/*******************************************************************************
* mtd_prgm_lut_ent_1731
*
* DESCRIPTION:
*         program an lut entry that matches Y1731 and actions
*               multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_1731(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_1731 port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagY1731, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagY1731);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_1731_opcode
*
* DESCRIPTION:
*         program an lut entry that matches the IP-in-IP for Y1731, Version PTP for opcode and actions
*        multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       opcode - opcode on Y1731, Version PTP.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_1731_opcode(MTD_U16 port, MTD_INT idx, MTD_INT opcode, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_1731_opcode port %d path %d idx %d opcode %d action %x\n", port, path, idx, opcode,  actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_VersionPTP, opcode);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_VersionPTP);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_stag
*
* DESCRIPTION:
*         program an lut entry that matches stag and actions
*        multiple actions are defined in a list
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_stag(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_stag port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagSTAG, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagSTAG);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}
/*******************************************************************************
* mtd_prgm_lut_ent_always0
*
* DESCRIPTION:
*         program an lut entry that do nothing
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_prgm_lut_ent_always0(MTD_U16 port, MTD_INT idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act;
    MTD_INT addr = (path == MTD_PTP_igr)? MTD_VN_IG_PTP: MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP mtd_prgm_lut_ent_always0 port %d path %d idx %d action %x\n", port, path, idx, actions);

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 0);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = mtd_prgm_ptp_get_lut_actions(actions);

    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));
    return retVal;
}


/*******************************************************************************
* mtd_get_ptp_stats
*
* DESCRIPTION:
*     prints out the ptp statistics .
*
* INPUTS:
*       port - port number
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_stats ( MTD_U16 port, MTD_PTP_Blk path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr;

/*  set path_igr (![string compare -nocase path "igr"]] */
    MTD_INT path_igr;
    MTD_INT index = 0;
    MTD_PTP_TYPE base_addr_id;
    char **stats_names_list;

    MTD_DBG_CRITIC_INFO("PTP stats (port %d, path %d)\n", port, path);

  /* both egr & igr stats are on the egr space !! */
    base_addr_id = mtd_get_ptp_base_addr_id(path);
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_STATS;

/*  set path_igr (![string compare -nocase path "igr"]] */
    path_igr = (path == MTD_PTP_igr)?1:0;
    if(path_igr)
    {
        stats_names_list = mtd_ptp_igr_stats_names_list;
//   my_base_addr = my_base_addr + 32*MTD_PTP_ADDR_ADJ;   ;/* igr stats come right after egr stats */
    }
    else
    {
        stats_names_list = mtd_ptp_egr_stats_names_list;
    }

    index = 0;
/*  foreach reg stats_names_list { */
    while(stats_names_list[index]!=0)
    {
        MTD_U16 reg_addr;

        reg_addr = my_base_addr + index*MTD_PTP_ADDR_ADJ;
        MTD_DBG_CRITIC_INFO("%04x %15s %08x\n", reg_addr, stats_names_list[index], mtd_ptp_read_reg(port, reg_addr));
        index++;
    }
    return retVal;
}

/*******************************************************************************
* mtd_ptp_lut_clear
*
* DESCRIPTION:
*     Clear PTP lut.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_lut_clear (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    MTD_INT index;

 /* Ingress  */
    for(index = 0; index < 16;  index++)
    {
        retVal = mtd_ptp_prgm_lut_entry( port, 0ll, 0ll, 0, 0, 0, index, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK) return retVal;
    }
 /* Egress  */
    for(index = 0; index < 16;  index++)
    {
        retVal = mtd_ptp_prgm_lut_entry( port, 0ll, 0ll, 0, 0, 0, index, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK) return retVal;
    }
    return retVal;
}

/*******************************************************************************
* mtd_ptp_get_drift_mcand
*
* DESCRIPTION:
*       This routine gets absolute value of drift multiplicand.
*
* INPUTS:
*        port - port number.
*
* OUTPUTS:
*       mcand - absolute value of drift multiplicand.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_drift_mcand (MTD_U16 port, MTD_UINT *mcand)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr = MTD_DRIFT_MCAND;
    *mcand = mtd_ptp_read_reg(port, reg_addr);
    return retVal;
}

/*******************************************************************************
* mtd_ptp_set_drift_mcand
*
* DESCRIPTION:
*       This routine sets absolute value of drift multiplicand.
*
* INPUTS:
*        port - port number.
*       mcand - absolute value of drift multiplicand.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_set_drift_mcand (MTD_U16 port, MTD_UINT mcand)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr = MTD_DRIFT_MCAND;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, mcand);
    return retVal;
}


/*******************************************************************************
*
*   Initial PTP
*
*********************************************************************************/


/*******************************************************************************
* mtd_new_ptp_init
*
* DESCRIPTION:
*        Completely Initialize new PTP block. It should be called before using any
*       new PTP function.
*
* INPUTS:
*        dev - point to device configuration
*       port - port number
*       link_mode - 0-1G, 1-10G
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_new_ptp_init (MTD_DEV* dev, MTD_U16 port, MTD_INT link_mode)
{
    MTD_STATUS   retVal = MTD_OK;
//  MTD_UINT ver;
  /*  MTD_INT i; */
    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_PTP_NOT_SUPPORT;

    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> init\n");
    retVal = mtd_ptp_dev_init(dev, port, link_mode);
    mtd_msec_set_mac_power_mode(dev, port, MTD_MACSEC_POWER_MODE_ACTIVE);
    retVal = mtd_init_macsec(port, link_mode);

    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> disable_ptp\n");
    mtd_disable_ptp(port);
//  MTD_DBG_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_1step_set_smac_loopback\n");
//  mtd_ptp_1step_set_smac_loopback(port, 1);

    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_update_init\n");
    retVal = mtd_ptp_update_init(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_parser_init\n");
    retVal = mtd_ptp_parser_init(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_update_set_udata\n");
    retVal = mtd_ptp_update_set_udata(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_update_check_udata\n");
    retVal = mtd_ptp_update_check_udata(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_parser_set_udata\n");
    retVal = mtd_ptp_parser_set_udata(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_parser_check_udata\n");
    retVal = mtd_ptp_parser_check_udata(port);
    if(retVal!=MTD_OK) return retVal;
/*  MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_lut_clear\n");
  retVal = mtd_ptp_lut_clear(port);
  if(retVal!=MTD_OK) return retVal;
*/
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_lut_init\n");
    retVal = mtd_ptp_lut_init(port);
    if(retVal!=MTD_OK) return retVal;

    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> correcting latadj \n");


    if(link_mode == 1)
    {
        mtd_set_ptp_igr_stt_ctl(port, 396);
        mtd_set_ptp_egr_stt_ctl(port, 396);
        mtd_set_igr_fr_latency(port, 35);
        mtd_set_ptp_igr_latadj(port, 1277);
        mtd_set_ptp_egr_latadj(port, mtd_get_ptp_egr_stt_ctl(port) * mtd_get_core_period() + 1301);
    }
    else if(link_mode == 0)
    {
        mtd_set_ptp_igr_stt_ctl(port, 1840);
        mtd_set_ptp_egr_stt_ctl(port, 2700);
        mtd_set_igr_fr_latency (port, 70);
        mtd_set_ptp_igr_latadj(port, 922);
        mtd_set_ptp_egr_latadj(port, mtd_get_ptp_egr_stt_ctl(port) * mtd_get_core_period() + 281);
    }

    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> drift set to 0\n");
    retVal = mtd_set_drift_adj(port, 0);
    if(retVal!=MTD_OK) return retVal;

    retVal = mtd_set_ptp_igr_mode(port, 1);
    if(retVal!=MTD_OK) return retVal;

    /* PTP init: check retVal, Enable constant latency */
    retVal = mtd_msec_set_constant_latency(port, 1);
    if(retVal!=MTD_OK) return retVal;

    /* for old chip */
    /*retVal = mtd_set_ptp_tai_step( port, 1, 0x9999999A);
    if(retVal!=MTD_OK) return retVal; */


    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> enable_ptp\n");
    retVal = mtd_enable_ptp(port);


    if(retVal!=MTD_OK) return retVal;

    return retVal;
}

/*******************************************************************************
* mtd_new_ntp_init
*
* DESCRIPTION:
*        Completely Initialize new NTP block. It should be called before using any
*       new NTP function.
*
* INPUTS:
*        dev - point to device configuration
*       port - port number
*       udp_src_port - second NTP source extend device number
*                      First extend device is 123, that is default on NTP standard.
*       udp_dst_port - second NTP destination extend device number
*                      First extend device is 123, that is default on NTP standard.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_new_ntp_init (MTD_DEV* dev, MTD_U16 port, MTD_INT udp_src_port_2, MTD_INT udp_dst_port_2, MTD_INT link_mode)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_PTP_NOT_SUPPORT;

    retVal = mtd_new_ptp_init(dev, port, link_mode);
    if(retVal != retVal) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_ptp_lut_init_ntp\n");
    retVal = mtd_ptp_lut_init_ntp(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_set_tai_ntp_mode\n");
    retVal = mtd_set_tai_ntp_mode(port);
    if(retVal!=MTD_OK) return retVal;
    MTD_DBG_CRITIC_INFO(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> mtd_set_ntp_mode\n");
    retVal = mtd_set_ntp_mode(port, 1);
    if(retVal!=MTD_OK) return retVal;


    return retVal;
}

/*******************************************************************************
* mtd_ptp_lut_set_udp
*
* DESCRIPTION:
*        Set configuration over UDP
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS  mtd_ptp_lut_set_udp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    retVal = mtd_ptp_lut_update (port, mtd_ptp_lut_key_adjust(MTD_K_FlagUDP, 1), mtd_ptp_vld_key_adjust(MTD_K_FlagUDP), 0ll,
        0ll, 0ll, 0ll,
        0, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
    return retVal;
}

/*******************************************************************************
* mtd_ptp_lut_clear_udp
*
* DESCRIPTION:
*        Reset configuration over UDP
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS  mtd_ptp_lut_clear_udp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    retVal =  mtd_ptp_lut_update (port, mtd_ptp_lut_key_adjust(MTD_K_FlagUDP, 1), mtd_ptp_vld_key_adjust(MTD_K_FlagUDP), 0ll,
        mtd_ptp_lut_key_adjust(MTD_K_FlagUDP, 0), mtd_ptp_vld_key_adjust(MTD_K_FlagUDP), 0ll,
        0, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
    return retVal;
}


/* mtd_ptp_1step_config initialize 1-step function based on mtd_ptp_cfg.
   return 0: success.
          1: no support.
          -1: failure
*/


static MTD_STATUS mtd_ptp_1step_V2_init(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, MTD_INT numIngLut, MTD_INT numEgLut)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_upper=0;
    MTD_U32 lut_vld_upper=0;
    MTD_U64 lut_act;
    MTD_INT i;


    for(i=0; i<numIngLut; i++)
    {
    /* Set Ingress configuration */
        lut_act = mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_action, 0x7);
/*   lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_mode, 0x1);    Xu check, it is useless*/
        if((mtd_ptp_cfg[i].ingaction)&MTD_PTP_1STEP_ING_ACT_TS_TAG_EX)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_InsertTST, 1) |
                mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_E, 1);

        if((mtd_ptp_cfg[i].ingaction)&MTD_PTP_1STEP_ING_ACT_TS_TAG)
        {
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_InsertTST, 1) |
                mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_E, 0);
        }


        if((mtd_ptp_cfg[i].ingaction)&MTD_PTP_1STEP_ING_ACT_PIGGY)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_E, 0) |
                mtd_ptp_lut_act_adjust(MTD_PTP_Act_IniPiggyback, 0x1);


        if((mtd_ptp_cfg[i].ingaction)&MTD_PTP_1STEP_ING_ACT_LOW_QUEUE)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_E, 0) |
                mtd_ptp_lut_act_adjust(MTD_PTP_Act_StampLow, 1);


        if((mtd_ptp_cfg[i].ingaction)&MTD_PTP_1STEP_ING_ACT_HIGH_QUEUE)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_TST_E, 0) |
                mtd_ptp_lut_act_adjust(MTD_PTP_Act_StampHigh, 1);



        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_SYNC)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Sync);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_DELAY_REQ)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Delay_Req);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_PDELAY_REQ)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Pdelay_Req);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry(port,  lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_PDELAY_RESP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Pdelay_Resp);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_DELAY_RESP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Delay_Resp);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_FOLLOWUP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Follow_Up);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_PDELAY_RESP_FOLLOWUP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Pdelay_Resp_Follow_Up);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_ANNOUNCE)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Announce);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
    /* could add management and Signaling */
    }
  /*  Default => do nothing */
    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 0);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, 15, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
    if(retVal!=MTD_OK)
        return retVal;
    MTD_DBG_INFO(">>>Write igr lut entry 15: key %llx  vld %llx  act %llx\n", lut_key, lut_vld, lut_act);


  /* Set Egress configuration */
    for(i=0; i<numEgLut; i++)
    {
        lut_act = mtd_ptp_lut_act_adjust(MTD_PTP_Act_HoldForTransmission, 1);
        if(mtd_ptp_cfg[i].egaction & MTD_PTP_1STEP_EG_ACT_REMOVE_TST)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_RemoveTST, 1) ;

        if((mtd_ptp_cfg[i].egaction)&MTD_PTP_1STEP_EG_ACT_LOW_QUEUE)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_StampLow, 0x1);

        if((mtd_ptp_cfg[i].egaction)& MTD_PTP_1STEP_EG_ACT_HIGH_QUEUE)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_StampHigh, 0x1);

        if((mtd_ptp_cfg[i].egaction)&MTD_PTP_1STEP_EG_ACT_UPDATE_TS)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_UpdateTxTime, 1);

        if((mtd_ptp_cfg[i].egaction)&MTD_PTP_1STEP_EG_ACT_SET_RES_TS)
            lut_act |= mtd_ptp_lut_act_adjust(MTD_PTP_Act_UpdateResidence, 1);

        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_SYNC)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Sync);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write egr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_DELAY_REQ)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Delay_Req);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write egr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_PDELAY_REQ)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Pdelay_Req);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write egr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_PDELAY_RESP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Pdelay_Resp);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write egr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
        if((mtd_ptp_cfg[i].msgTypes)&MTD_PTP_1STEP_MSG_DELAY_RESP)
        {
            lut_key = mtd_ptp_lut_key_adjust( MTD_K_FlagPTPv2, 1);
            lut_vld = mtd_ptp_vld_key_adjust(MTD_K_FlagPTPv2);
            lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_MessageType, MTD_PTPv2_MSG_Delay_Resp);
            lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_MessageType);
            retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
            if(retVal!=MTD_OK)
                return retVal;
            MTD_DBG_INFO(">>>Write egr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
        }
    }

/*   mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, 0, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)); */
/*   MTD_DBG_INFO(">>>Write egr lut entry 0 : key %llx  vld %llx  act %llx\n", lut_key, lut_vld, lut_act); */
  /*  Default => do nothing */
    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 0);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_upper, lut_vld_upper, lut_act, 15, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
    if(retVal!=MTD_OK)
        return retVal;
    MTD_DBG_INFO(">>>Write egr lut entry 15: key %llx  vld %llx  act %llx\n", lut_key, lut_vld, lut_act);

    return retVal;
}

/*******************************************************************************
* mtd_ptp_1step_V2_ethernet_init
*
* DESCRIPTION:
*        Set configuration for PTP version 2, and over Ethernet.
*
* INPUTS:
*       port - port number
*       mtd_ptp_cfg  - pointer to 1-step PTP configuration
*       numIngLut - number of ingress Lut
*       numEgLut - number of Egress Lut
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_1step_V2_ethernet_init(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, MTD_INT numIngLut, MTD_INT numEgLut)
{
    MTD_STATUS   retVal = MTD_OK;

    retVal = mtd_ptp_lut_clear_udp (port);
    if(retVal!=MTD_OK)
        return retVal;

    retVal = mtd_ptp_1step_V2_init (port, mtd_ptp_cfg, numIngLut, numEgLut);

    return retVal;

}
/*******************************************************************************
* mtd_ptp_1step_V2_IP4_UDP_init
*
* DESCRIPTION:
*        Set configuration for PTP version 2, and over UDP/IP4.
*
* INPUTS:
*       port - port number
*       mtd_ptp_cfg  - pointer to 1-step PTPconfiguration
*       numIngLut - number of ingress Lut
*       numEgLut - number of Egress Lut
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_1step_V2_IP4_UDP_init(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, MTD_INT numIngLut, MTD_INT numEgLut)
{
    MTD_STATUS   retVal = MTD_OK;

    MTD_64 lut_key;
    MTD_64 lut_vld;
    MTD_32 lut_key_top=0;
    MTD_32 lut_vld_top=0;
    MTD_64 lut_act;
    MTD_INT i;

    retVal = mtd_ptp_lut_clear_udp (port);
    if(retVal!=MTD_OK)
        return retVal;
    retVal = mtd_ptp_1step_V2_init (port, mtd_ptp_cfg, numIngLut, numEgLut);
    if(retVal!=MTD_OK)
        return retVal;

    for(i=0; i<numIngLut; i++)
    {
        retVal = mtd_read_lut_entry(port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>> read lut entry : key %x:%llx  vld %x:%llx  act %llx\n",
            lut_key_top, lut_key, lut_vld_top, lut_vld, lut_act);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagIPv4, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagIPv4);
        retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
    }
    for(i=0; i<numEgLut; i++)
    {
        retVal = mtd_read_lut_entry(port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>> read lut entry : key %x:%llx  vld %x:%llx  act %llx\n",
            lut_key_top, lut_key, lut_vld_top, lut_vld, lut_act);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagIPv4, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagIPv4);
        retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
    }

    return retVal;
}


/*******************************************************************************
* mtd_ptp_1step_V2_IP6_UDP_init
*
* DESCRIPTION:
*        Set configuration for PTP version 2, and over UDP/IP6.
*
* INPUTS:
*       port - port number
*       mtd_ptp_cfg  - pointer to 1-step PTPconfiguration
*       numIngLut - number of ingress Lut
*       numEgLut - number of Egress Lut
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_1step_V2_IP6_UDP_init(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, MTD_INT numIngLut, MTD_INT numEgLut)
{
    MTD_STATUS   retVal = MTD_OK;

    MTD_64 lut_key;
    MTD_64 lut_vld;
    MTD_32 lut_key_top=0;
    MTD_32 lut_vld_top=0;
    MTD_64 lut_act;
    MTD_INT i;

    retVal = mtd_ptp_lut_clear_udp (port);
    if(retVal!=MTD_OK)
        return retVal;
    retVal = mtd_ptp_1step_V2_init (port, mtd_ptp_cfg, numIngLut, numEgLut);
    if(retVal!=MTD_OK)
        return retVal;

    for(i=0; i<numIngLut; i++)
    {
        retVal = mtd_read_lut_entry(port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>> read lut entry : key %x:%llx  vld %x:%llx  act %llx\n",
            lut_key_top, lut_key, lut_vld_top, lut_vld, lut_act);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagIPv6, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagIPv6);
        retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, i, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
    }
    for(i=0; i<numEgLut; i++)
    {
        retVal = mtd_read_lut_entry( port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>> read lut entry : key %x:%llx  vld %x:%llx  act %llx\n",
            lut_key_top, lut_key, lut_vld_top, lut_vld, lut_act);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagUDP, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagUDP);
        lut_key = lut_key | mtd_ptp_lut_key_adjust( MTD_K_FlagIPv6, 1);
        lut_vld = lut_vld | mtd_ptp_vld_key_adjust(MTD_K_FlagIPv6);
        retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, i, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
        if(retVal!=MTD_OK)
            return retVal;
        MTD_DBG_INFO(">>>Write igr lut entry %d : key %llx  vld %llx  act %llx\n", i, lut_key, lut_vld, lut_act);
    }

    return retVal;
}

/*******************************************************************************
* mtd_ptp_1step_config
*
* DESCRIPTION:
*        General function to set configuration for LUT
*
* INPUTS:
*       port - port number
*       mtd_ptp_cfg  - pointer to 1-step PTPconfiguration
*       numIngLut - number of ingress Lut
*       numEgLut - number of Egress Lut
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_1step_config(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, MTD_INT numIngLut, MTD_INT numEgLut)
{
    MTD_STATUS   retVal = MTD_OK;

    if(mtd_ptp_cfg[0].version== MTD_PTP_1STEP_VER_V2)
    {
        switch(mtd_ptp_cfg[0].overLayer)
        {
        case MTD_PTP_1STEP_OVER_L2:
            return mtd_ptp_1step_V2_init (port, mtd_ptp_cfg, numIngLut, numEgLut);

        case MTD_PTP_1STEP_OVER_IP4_UDP:
            return mtd_ptp_1step_V2_IP4_UDP_init (port, mtd_ptp_cfg, numIngLut, numEgLut);

        case MTD_PTP_1STEP_OVER_IP6_UDP:
            return mtd_ptp_1step_V2_IP6_UDP_init (port, mtd_ptp_cfg, numIngLut, numEgLut);

        default:
            return MTD_FAIL;
        }
    }
    else
        return MTD_FAIL;

    return retVal;
}

