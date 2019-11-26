/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/
#include "mcdApiTypes.h"
#include "mcdAPI.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdAPIInternal.h"
#include "mcdInternalIpcDefs.h"
#include "mcdInternalIpcApis.h"
#include "mcdApiRegs.h"
#include "mcdInternalInitApApis.h"
#include "mcdInternalPortApInitIf.h"
#include "mcdPortCtrlApLogDefs.h"
#include "mcdInternalCtrlApInitIf.h"


#ifdef MCD_IPC_CNV_ENABLE

/* forward declaration */
struct MCD_IPC_CNV_WORD32_ENTRY;


typedef struct
{
    MCD_U16  structSize; /* sizeof(structure) for validity check */
    MCD_U16  numOfWordEntries;
    struct MCD_IPC_CNV_WORD32_ENTRY *wordEntriesPtr;
} MCD_IPC_STRUCT_CNV_STC;

typedef struct MCD_IPC_CNV_WORD32_ENTRY
{
    MCD_U16                   numOfWords;
    MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat;
} MCD_IPC_CNV_WORD32_ENTRY_STC;

/* used when no data passed as message or reply payload */
static MCD_IPC_STRUCT_CNV_STC mcdInternalIpcCnvEmptyStruct = {0, 0, NULL};

/* Array of words coding macros */

#define MCD_IPC_CNV_BEGIN_MAC(_struct_name) \
    static MCD_IPC_CNV_WORD32_ENTRY_STC MCD_IPC_CNV_ENTRY_ARR_##_struct_name[] = {

#define MCD_IPC_CNV_END_MAC(_struct_name) \
    }; \
    static MCD_IPC_STRUCT_CNV_STC MCD_IPC_CNV_DATA_##_struct_name = { \
        sizeof(_struct_name), \
        (sizeof(MCD_IPC_CNV_ENTRY_ARR_##_struct_name) \
            / sizeof(MCD_IPC_CNV_ENTRY_ARR_##_struct_name[0])), \
        &(MCD_IPC_CNV_ENTRY_ARR_##_struct_name[0]) \
    };

#define MCD_IPC_CNV_DATA_MAC(_struct_name) MCD_IPC_CNV_DATA_##_struct_name

/* types are U32, 2U16, U16_2U8, 2U8_U16, 4U8 */
#define MCD_IPC_CNV_ENTRY_MAC(_num_of, _type) {_num_of, MCD_IPC_CNV_WORD32_FORMAT_##_type##_E}

/*MCD_IPC_PORT_AP_DATA_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_AP_DATA_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32),
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8),
MCD_IPC_CNV_ENTRY_MAC(1, 4U8),
MCD_IPC_CNV_ENTRY_MAC(1, U32),
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_AP_DATA_STRUCT)

/* MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32),
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, 4U8),
MCD_IPC_CNV_ENTRY_MAC(1, 4U8)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT)

/* MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32),
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT)

/*MCD_IPC_PORT_AP_INTROP_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_AP_INTROP_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32),
MCD_IPC_CNV_ENTRY_MAC(4, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_AP_INTROP_STRUCT)

/*MCD_IPC_PORT_INFO_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_INFO_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_INFO_STRUCT)

/*MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC)
MCD_IPC_CNV_ENTRY_MAC(4, 2U16),
MCD_IPC_CNV_ENTRY_MAC(3, U32),
MCD_IPC_CNV_ENTRY_MAC(2, 2U16),
MCD_IPC_CNV_ENTRY_MAC(5, U32),
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8)
MCD_IPC_CNV_END_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC)


/*MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC)
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8)
MCD_IPC_CNV_END_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC)

/*MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT)
MCD_IPC_CNV_ENTRY_MAC(1, 2U16),
MCD_IPC_CNV_ENTRY_MAC(2, U32)
MCD_IPC_CNV_END_MAC(MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT)

/*MCD_IPC_PORT_REPLY_AP_STATUS_GET*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_REPLY_AP_STATUS_GET)
MCD_IPC_CNV_ENTRY_MAC(2, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U32)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_REPLY_AP_STATUS_GET)

/*MCD_IPC_PORT_REPLY_AP_STATS_GET*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_REPLY_AP_STATS_GET)
MCD_IPC_CNV_ENTRY_MAC(2, 2U16),
MCD_IPC_CNV_ENTRY_MAC(1, U16_2U8),
MCD_IPC_CNV_ENTRY_MAC(2, U32)
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_REPLY_AP_STATS_GET)

/*MCD_IPC_PORT_REPLY_AP_INTROP_GET*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_REPLY_AP_INTROP_GET)
MCD_IPC_CNV_ENTRY_MAC(4, 2U16),
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_REPLY_AP_INTROP_GET)

/*MCD_IPC_LOG_GET*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_LOG_GET)
MCD_IPC_CNV_ENTRY_MAC(6, U32),
MCD_IPC_CNV_END_MAC(MCD_IPC_LOG_GET)

/*MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET*/
MCD_IPC_CNV_BEGIN_MAC(MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET)
MCD_IPC_CNV_ENTRY_MAC(2, U32),
MCD_IPC_CNV_END_MAC(MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET)


/* get conversion data by type - NULL if not supported*/
static MCD_IPC_STRUCT_CNV_STC* mcdInternalIpcCnvStructSendDataGet
(
    IN MCD_IPC_CTRL_MSG_DEF_TYPE structType
)
{
    switch (structType)
    {
        case MCD_IPC_PORT_AP_ENABLE_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_AP_DATA_STRUCT));
        case MCD_IPC_PORT_AP_DISABLE_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_AP_DATA_STRUCT));
        case MCD_IPC_PORT_AP_STATUS_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_PORT_AP_STATS_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_PORT_AP_INTROP_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_PORT_AP_INTROP_SET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_AP_INTROP_STRUCT));
        case MCD_IPC_PORT_AP_DEBUG_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_PORT_AVAGO_SERDES_INIT_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_PORT_AVAGO_SERDES_RESET_DATA_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_HWS_LOG_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_INFO_STRUCT));
        case MCD_IPC_RX_CLOCK_CTRL_PIN_SET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT));
        case MCD_IPC_PORT_POLLING_START_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC));
        case MCD_IPC_PORT_POLLING_STOP_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC));
        case MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_MSG:
        return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT));
        case MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_MSG:
        return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT));
        default: return NULL;
    }
}

static MCD_IPC_STRUCT_CNV_STC* mcdInternalIpcCnvStructReceiveDataGet
(
    IN MCD_IPC_CTRL_MSG_DEF_TYPE structType
)
{
    switch (structType)
    {
        case MCD_IPC_PORT_AP_STATUS_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_REPLY_AP_STATUS_GET));
        case MCD_IPC_PORT_AP_STATS_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_REPLY_AP_STATS_GET));
        case MCD_IPC_PORT_AP_INTROP_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_REPLY_AP_INTROP_GET));
        case MCD_IPC_PORT_AP_DEBUG_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_LOG_GET));
        case MCD_IPC_PORT_AVAGO_SERDES_INIT_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET));
        case MCD_IPC_HWS_LOG_GET_MSG:
            return &(MCD_IPC_CNV_DATA_MAC(MCD_IPC_LOG_GET));
        default: return &mcdInternalIpcCnvEmptyStruct;
    }
}

/* this function checks that array of word formats matches the */
/* size of conerted structure                                  */
static MCD_BOOL mcdInternalIpcCnvStructDataIsValid
(
    IN MCD_IPC_STRUCT_CNV_STC* cnvPtr
)
{
    MCD_U32 i, numOfWords, foundSize, structSizeof;
    typedef enum {e1, e2} ENUM_TYPE;

    if (sizeof(ENUM_TYPE) != 4)
    {
        MCD_DBG_ERROR(
            "sizeof(ENUM_TYPE) is %d - code is not applicable\n", sizeof(ENUM_TYPE));
        return MCD_FALSE;
    }

    numOfWords = 0;
    for (i = 0; (i < cnvPtr->numOfWordEntries); i++)
    {
        numOfWords += cnvPtr->wordEntriesPtr[i].numOfWords;
    }
    foundSize = (numOfWords * 4);
    structSizeof = ((cnvPtr->structSize + 3) & (~ 3)); /* alignment to 4 */
    if (foundSize != structSizeof)
    {
        MCD_DBG_ERROR(
            "mcdInternalIpcCnvStructDataIsValid error CNV script size %d SRUCT sizeof %d\n",
            foundSize, structSizeof);
        return MCD_FALSE;
    }
    return MCD_TRUE;
}

/* ----------------------------------------------- */
/* Conversion  Big Endian to Little Endian         */
/* is the same as Little Endian to Big Endian      */
/* Both are swap of bytes inside 16-bit fields     */
/* ----------------------------------------------- */

/* ----------------------------------------------- */
/* This function converts both                     */
/* Big Endian to Swapped Little Endian and         */
/* Little Endian to Swapped Big Endian             */
MCD_U32 mcdInternalIpcBeToSwappedLeConvert
(
    IN MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat,
    IN MCD_U32                       wordValue
)
{
    MCD_U8 b0 = (MCD_U8)((wordValue >> 24) & 0xFF);
    MCD_U8 b1 = (MCD_U8)((wordValue >> 16) & 0xFF);
    MCD_U8 b2 = (MCD_U8)((wordValue >>  8) & 0xFF);
    MCD_U8 b3 = (MCD_U8)( wordValue        & 0xFF);

    switch (wordFormat)
    {
        case MCD_IPC_CNV_WORD32_FORMAT_U32_E:
            return wordValue; /* no change needed */
        case MCD_IPC_CNV_WORD32_FORMAT_2U16_E:
            /* Big endian            f0_high f0_low f1_high f1_low */
            /* Little endian         f0_low f0_high f1_low f1_high */
            /* Swapped Little endian f1_high f1_low f0_high f0_low */
            return ((b2 << 24) | (b3 << 16) | (b0 << 8) | b1);
        case MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E:
            /* Big endian            f0_high f0_low f1 f2 */
            /* Little endian         f0_low f0_high f1 f2 */
            /* Swapped Little endian f2 f1 f0_high f0_low */
            return ((b3 << 24) | (b2 << 16) | (b0 << 8) | b1);
        case MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E:
            /* Big endian            f0 f1 f2_high f2_low */
            /* Little endian         f0 f1 f2_low f2_high */
            /* Swapped Little endian f2_high f2_low f1 f0 */
            return ((b2 << 24) | (b3 << 16) | (b1 << 8) | b0);
        case MCD_IPC_CNV_WORD32_FORMAT_4U8_E:
            /* back swap to restore byte order */
            return ((b3 << 24) | (b2 << 16) | (b1 << 8) | b0);
        default: break;
    }
    MCD_DBG_ERROR(
        "mcdInternalIpcBeToSwappedLeConvert wrong format %d\n",
        wordFormat);
    return 0; /* error case*/
}

/* ----------------------------------------------- */
/* This function converts both                     */
/* Swapped Little Endian to Big Endian and         */
/* Swapped Big Endian to Little Endian             */
MCD_U32 mcdInternalIpcSwappedLeToBeConvert
(
    IN MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat,
    IN MCD_U32                       wordValue
)
{
    MCD_U8 b0 = (MCD_U8)((wordValue >> 24) & 0xFF);
    MCD_U8 b1 = (MCD_U8)((wordValue >> 16) & 0xFF);
    MCD_U8 b2 = (MCD_U8)((wordValue >>  8) & 0xFF);
    MCD_U8 b3 = (MCD_U8)( wordValue        & 0xFF);

    switch (wordFormat)
    {
        case MCD_IPC_CNV_WORD32_FORMAT_U32_E:
            return wordValue; /* no change needed */
        case MCD_IPC_CNV_WORD32_FORMAT_2U16_E:
            /* Swapped Little endian f1_high f1_low f0_high f0_low */
            /* Little endian         f0_low f0_high f1_low f1_high */
            /* Big endian            f0_high f0_low f1_high f1_low */
            return ((b2 << 24) | (b3 << 16) | (b0 << 8) | b1);
        case MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E:
            /* Swapped Little endian f2 f1 f0_high f0_low */
            /* Little endian         f0_low f0_high f1 f2 */
            /* Big endian            f0_high f0_low f1 f2 */
            return ((b2 << 24) | (b3 << 16) | (b1 << 8) | b0);
        case MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E:
            /* Swapped Little endian f2_high f2_low f1 f0 */
            /* Little endian         f0 f1 f2_low f2_high */
            /* Big endian            f0 f1 f2_high f2_low */
            return ((b3 << 24) | (b2 << 16) | (b0 << 8) | b1);
        case MCD_IPC_CNV_WORD32_FORMAT_4U8_E:
            /* back swap to restore byte order */
            return ((b3 << 24) | (b2 << 16) | (b1 << 8) | b0);
        default: break;
    }

    MCD_DBG_ERROR(
        "mcdInternalIpcSwappedLeToBeConvert wrong format %d\n",
        wordFormat);
    return 0; /* error case*/
}

static MCD_STATUS mcdInternalIpcCnvSendPayloadInplaceConvert
(
    IN     MCD_IPC_CTRL_MSG_DEF_TYPE structType,
    INOUT  MCD_IPC_MSG_API_PARAMS    *msgPayloadPtr
)
{
    MCD_IPC_STRUCT_CNV_STC* pCnvData;
    MCD_BOOL valid;
    MCD_U32  *pData;
    MCD_U32  i, j;

    pCnvData = mcdInternalIpcCnvStructSendDataGet(structType);
    if (pCnvData == NULL)
    {
        MCD_DBG_ERROR(
            "MCD_IPC_CNV Not found conversion data for send message type %d\n",
            structType);
        return MCD_FAIL;
    }
    valid = mcdInternalIpcCnvStructDataIsValid(pCnvData);
    if (valid == MCD_FALSE)
    {
        MCD_DBG_ERROR(
            "MCD_IPC_CNV invalid conversion data for send message type %d\n",
            structType);
        return MCD_FAIL;
    }
    pData = (MCD_U32*)msgPayloadPtr;
    for (i = 0; (i < pCnvData->numOfWordEntries); i++)
    {
        for (j = 0; (j < pCnvData->wordEntriesPtr[i].numOfWords); j++)
        {
            *pData = mcdInternalIpcBeToSwappedLeConvert(
                pCnvData->wordEntriesPtr[i].wordFormat, *pData);
            pData++;
        }
    }
    return MCD_OK;
}

static MCD_STATUS mcdInternalIpcCnvReceivePayloadInplaceConvert
(
    IN     MCD_IPC_CTRL_MSG_DEF_TYPE     structType,
    INOUT  MCD_IPC_REPLY_MSG_DATA_TYPE   *replayPayloadPtr
)
{
    MCD_IPC_STRUCT_CNV_STC* pCnvData;
    MCD_BOOL valid;
    MCD_U32  *pData;
    MCD_U32  i, j;

    pCnvData = mcdInternalIpcCnvStructReceiveDataGet(structType);
    if (pCnvData == NULL)
    {
        MCD_DBG_ERROR(
            "MCD_IPC_CNV Not found conversion data for send message type %d\n",
            structType);
        return MCD_FAIL;
    }
    valid = mcdInternalIpcCnvStructDataIsValid(pCnvData);
    if (valid == MCD_FALSE)
    {
        MCD_DBG_ERROR(
            "MCD_IPC_CNV invalid conversion data for send message type %d\n",
            structType);
        return MCD_FAIL;
    }
    pData = (MCD_U32*)replayPayloadPtr;
    for (i = 0; (i < pCnvData->numOfWordEntries); i++)
    {
        for (j = 0; (j < pCnvData->wordEntriesPtr[i].numOfWords); j++)
        {
            *pData = mcdInternalIpcSwappedLeToBeConvert(
                pCnvData->wordEntriesPtr[i].wordFormat, *pData);
            pData++;
        }
    }
    return MCD_OK;
}

static MCD_STATUS mcdInternalIpcCnvSendDataInplaceConvert
(
    INOUT   MCD_IPC_CTRL_MSG_STRUCT   *msgStructPtr
)
{
    MCD_IPC_CTRL_MSG_DEF_TYPE structType;
    MCD_STATUS                rc;
    MCD_U32                   *prefixPtr;

    structType = (MCD_IPC_CTRL_MSG_DEF_TYPE)msgStructPtr->ctrlMsgType;
    rc = mcdInternalIpcCnvSendPayloadInplaceConvert(
        structType, &(msgStructPtr->msgData));
    if (rc != MCD_OK) return rc;

    /* convert own (not payload) part - see MCD_IPC_CTRL_MSG_STRUCT */
    prefixPtr = (MCD_U32*)msgStructPtr;
    *prefixPtr = mcdInternalIpcBeToSwappedLeConvert(
        MCD_IPC_CNV_WORD32_FORMAT_4U8_E, *prefixPtr);

    return MCD_OK;
}

static MCD_STATUS mcdInternalIpcCnvReceiveDataInplaceConvert
(
    INOUT  MCD_IPC_REPLY_MSG_STRUCT   *replayStructPtr
)
{
    MCD_IPC_CTRL_MSG_DEF_TYPE     structType;
    MCD_U32                       *prefixPtr;
    MCD_STATUS                    rc;

    /* convert own (not payload) part - see MCD_IPC_REPLY_MSG_STRUCT */
    prefixPtr = (MCD_U32*)replayStructPtr;
    prefixPtr[0] = mcdInternalIpcSwappedLeToBeConvert(
        MCD_IPC_CNV_WORD32_FORMAT_U32_E, prefixPtr[0]);
    prefixPtr[1] = mcdInternalIpcSwappedLeToBeConvert(
        MCD_IPC_CNV_WORD32_FORMAT_U32_E, prefixPtr[1]);

    structType = (MCD_IPC_CTRL_MSG_DEF_TYPE)replayStructPtr->replyTo;
    rc = mcdInternalIpcCnvReceivePayloadInplaceConvert(
        structType, &(replayStructPtr->readData));

    return rc;
}

#ifdef MCD_IPC_CNV_TEST

void mcdInternalIpcCnvTest()
{
    MCD_IPC_STRUCT_CNV_STC* cnvDatPtr;
    MCD_BOOL valid;
    MCD_U32 pattern, toSwLe, toBeSw, fromSwLe, fromBeSw;

    MCD_SHOW("sizeof(MCD_BOOL) %d\n", sizeof(MCD_BOOL));


    cnvDatPtr = mcdInternalIpcCnvStructSendDataGet(MCD_IPC_PORT_AP_ENABLE_MSG);
    if (cnvDatPtr == NULL)
    {
        MCD_SHOW("no data for MCD_IPC_PORT_AP_ENABLE_MSG\n");
    }
    else
    {
        valid = mcdInternalIpcCnvStructDataIsValid(cnvDatPtr);
        MCD_SHOW("data for MCD_IPC_PORT_AP_ENABLE_MSG valid = %d\n", valid);
    }


    cnvDatPtr = mcdInternalIpcCnvStructReceiveDataGet(MCD_IPC_PORT_AP_ENABLE_MSG);
    /*-----------------------------------------------------------------------*/
    pattern = 0x01020304;

    toSwLe   = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U16_E, pattern);
    fromSwLe = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U16_E, toSwLe);
    toBeSw   = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U16_E, pattern);
    fromBeSw = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U16_E, toBeSw);
    MCD_SHOW(
        "2U16 conversion pattern 0x%08X toSwLe 0x%08X fromSwLe 0x%08X toBeSw 0x%08X fromBeSw 0x%08X \n",
        pattern, toSwLe, fromSwLe, toBeSw, fromBeSw);

    toSwLe   = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E, pattern);
    fromSwLe = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E, toSwLe);
    toBeSw   = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E, pattern);
    fromBeSw = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E, toBeSw);
    MCD_SHOW(
        "U16_2U8 conversion pattern 0x%08X toSwLe 0x%08X fromSwLe 0x%08X toBeSw 0x%08X fromBeSw 0x%08X \n",
        pattern, toSwLe, fromSwLe, toBeSw, fromBeSw);

    toSwLe  = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E, pattern);
    fromSwLe = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E, toSwLe);
    toBeSw  = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E, pattern);
    fromBeSw = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E, toBeSw);
    MCD_SHOW(
        "2U8_U16 conversion pattern 0x%08X toSwLe 0x%08X fromSwLe 0x%08X toBeSw 0x%08X fromBeSw 0x%08X \n",
        pattern, toSwLe, fromSwLe, toBeSw, fromBeSw);

    toSwLe   = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_4U8_E, pattern);
    fromSwLe = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_4U8_E, toSwLe);
    toBeSw   = mcdInternalIpcSwappedLeToBeConvert(MCD_IPC_CNV_WORD32_FORMAT_4U8_E, pattern);
    fromBeSw = mcdInternalIpcBeToSwappedLeConvert(MCD_IPC_CNV_WORD32_FORMAT_4U8_E, toBeSw);
    MCD_SHOW(
        "4U8 conversion pattern 0x%08X toSwLe 0x%08X fromSwLe 0x%08X toBeSw 0x%08X fromBeSw 0x%08X \n",
        pattern, toSwLe, fromSwLe, toBeSw, fromBeSw);
}
#endif /*MCD_IPC_CNV_TEST*/

#endif /*MCD_IPC_CNV_ENABLE*/


/**************************** Pre-Declaration ********************************************/
MCD_STATUS mcdInternalSetIpcInfo( MCD_DEV_PTR pDev, MCD_IPC_CTRL_MSG_DEF_TYPE msgType, MCD_IPC_CTRL_MSG_STRUCT *msgDataPtr,
                          MCD_U32 msgLength);

MCD_STATUS mcdInternalIpcCtrlMsgTx(MCD_DEV_PTR pDev,
                           MCD_IPC_CTRL_MSG_STRUCT *txCtrlMsg);
MCD_STATUS mcdInternalIpcReplyMsgRx(MCD_DEV_PTR pDev, MCD_IPC_CTRL_MSG_DEF_TYPE msgId, MCD_U32 queueId,
                             MCD_IPC_REPLY_MSG_STRUCT *rxReplyData);

static MCD_STATUS mcdLogGetIpc(MCD_DEV_PTR pDev, MCD_FW_LOG                 *hwsLogPtr);


/**
* @internal mcdInternalServiceCpuMsgSend function
* @endinternal
*
* @brief   Send message to Service CPU via IPC channel
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalServiceCpuMsgSend
(
    IN MCD_DEV_PTR pDev,
    IN unsigned int channel,
    IN char* msg
)
{
#ifdef MCD_IPC_CNV_ENABLE
    /* convert from Big endian to Swapped Little Endian */
    if (MCD_OK != mcdInternalIpcCnvSendDataInplaceConvert(
        (MCD_IPC_CTRL_MSG_STRUCT*)msg))
    {
        return MCD_FAIL;
    }
#endif /*MCD_IPC_CNV_ENABLE*/

    if (mcdInternalShmIpcSend(
        &(pDev->shm), channel,
        msg, sizeof(MCD_IPC_CTRL_MSG_STRUCT)) != 0)
    {
        return MCD_FAIL;
    }
    return MCD_OK;
}


/**
* @internal mcdInternalServiceCpuMsgRecv function
* @endinternal
*
* @brief   Receive message from Service CPU via IPC channel
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalServiceCpuMsgRecv
(
    IN  MCD_DEV_PTR pDev,
    IN  unsigned int channel,
    OUT char* msg
)
{
    int     rc;
    int     size = 1024;

    rc = mcdInternalShmIpcRecv(&(pDev->shm), channel, msg, &size);
    if (rc < 0)
        return MCD_FAIL;
    if (rc == 0)
        return MCD_STATUS_NO_SUCH;

#ifdef MCD_IPC_CNV_ENABLE
    if (MCD_OK != mcdInternalIpcCnvReceiveDataInplaceConvert(
        (MCD_IPC_REPLY_MSG_STRUCT*)msg))
    {
        return MCD_FAIL;
    }
#endif /*MCD_IPC_CNV_ENABLE*/

    return MCD_OK;
}

/* functions for access to shared memory - shared memory not mapped to CPU address space */
static MCD_STATUS mcdIpcShmWrite(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, const void* dataPtr)
{
    MCD_U32    wordIdx;
    MCD_DEV_PTR pDev = (MCD_DEV_PTR)anchorPtr;
    for (wordIdx = 0; (wordIdx < numOfWords); wordIdx++)
    {
        ATTEMPT(mcdHwXmdioWrite32bit(
            pDev, 0                            /*mdioPort*/,
            (address + (4 * wordIdx))          /*reg*/,
            (((MCD_U32*)dataPtr)[wordIdx])     /*value*/
        ));
    }
    return MCD_OK;
}
static MCD_STATUS mcdIpcShmRead(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, void* dataPtr)
{
    MCD_U32    wordIdx;
    MCD_DEV_PTR pDev = (MCD_DEV_PTR)anchorPtr;
    for (wordIdx = 0; (wordIdx < numOfWords); wordIdx++)
    {
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, 0                            /*mdioPort*/,
            (address + (4 * wordIdx))          /*reg*/,
            &(((MCD_U32*)dataPtr)[wordIdx])    /*value*/
        ));
    }
    return MCD_OK;
}
/**
* @internal mcdInternalIpcDbInit function
* @endinternal
*
* @brief   IPC database initialization
*
* @param[in,out] pDev
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdInternalIpcDbInit
(
    INOUT MCD_DEV_PTR pDev
)
{
    int         shmApiRc; /* return code of SHM API */
    MCD_IPC_PTR cm3MemoryBase    = REG_ADDR_CM3_MEMORY_BASE;
    MCD_IPC_U32 cm3MemorySize    = 0x20000; /*128K*/
    MCD_IPC_U32 sharedMemorySize = 0x800; /*2K*/
    MCD_IPC_PTR sharedMemoryBase = (cm3MemoryBase + cm3MemorySize - sharedMemorySize);

    mcdMemSet(pDev->mcdIpcQueueIdPool,0 , (MCD_MAX_HOST2SCPU_REQ_MSG_NUM* sizeof (MCD_U32)));
    mcdMemSet(pDev->mcdIpcStatistics.mcdHostRxMsgCount, 0, (MCD_IPC_LAST_CTRL_MSG_TYPE * sizeof (MCD_U32)));
    mcdMemSet(pDev->mcdIpcStatistics.mcdHostTxMsgCount, 0, (MCD_IPC_LAST_CTRL_MSG_TYPE * sizeof(MCD_U32)));
    mcdMemSet(pDev->mcdIpcStatistics.mcdPortIpcFailureCount, 0 , (MCD_IPC_MAX_PORT_NUM * sizeof(MCD_U32)));

    shmApiRc = mcdInternalShmIpcInit(
        &(pDev->shm),
        pDev, mcdIpcShmWrite, mcdIpcShmRead,
        (MCD_IPC_PTR)sharedMemoryBase,
        sharedMemorySize, 1 /*master*/);
    if (shmApiRc != 0)
    {
        return MCD_FAIL;
    }

    shmApiRc = mcdInternalShmIpcRegWrite(&(pDev->shm), 0, sharedMemoryBase);
    if (shmApiRc != 0) return MCD_FAIL;

    /* configure channels */
    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 0, 0,  0, 4, 64);
    if (shmApiRc != 0) return MCD_FAIL;

    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 1, 0,  0, 4, 64);
    if (shmApiRc != 0) return MCD_FAIL;

    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 2, 1, 64, 0, 0);
    if (shmApiRc != 0) return MCD_FAIL;

    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 3, 1, 64, 0, 0);
    if (shmApiRc != 0) return MCD_FAIL;

    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 4, 1, 64, 0, 0);
    if (shmApiRc != 0) return MCD_FAIL;

    shmApiRc = mcdInternalShmIpcConfigChannel(&(pDev->shm), 5, 1, 64, 0, 0);
    if (shmApiRc != 0) return MCD_FAIL;

    return MCD_OK;
}
extern MCD_BOOT_MODE bootMode;
/**
* @internal mcdServiceCpuFwPostInit function
* @endinternal
*
* @brief   Init Serdes Configuration DB and Log support on service CPU.
*
* @param[in] pDev
*                                      phyPortNum  - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdServiceCpuFwPostInit
(
       IN MCD_DEV_PTR pDev
)
{
    MCD_U32       serviceCpuAvagoCfgAddr;
    MCD_U32       serviceCpuAvagoCfgSize;
#ifdef MCD_DEBUG
    unsigned int *hostAvagoCfgAddr = 0;
    unsigned int hostAvagoCfgSize = 0;
#endif

    MCD_FW_LOG mcdApDebug = {0,0,0,0,0,0};
    MCD_FW_LOG mcdHwsLog = {0,0,0,0,0,0};

    if (mcdSerdesCfgAddrGetIpc( pDev, &serviceCpuAvagoCfgAddr, &serviceCpuAvagoCfgSize) == MCD_OK)
    {
         MCD_DBG_INFO("mcdServiceCpuFwPostInit host adr = %x host size %x addr =%x, size = %x\n",hostAvagoCfgAddr,hostAvagoCfgSize,serviceCpuAvagoCfgAddr, serviceCpuAvagoCfgSize);

#ifndef MCD_IPC_CNV_ENABLE
         /* load AAPL DB to service CPU */
         if (bootMode == MCD_REGULAR_BOOT_MODE)
         {
             if (mcdServiceCpuWrite(pDev, (unsigned int)serviceCpuAvagoCfgAddr,
                                    (unsigned int *)((MCD_SER_DEV_PTR)pDev->serdesDev),
                                    serviceCpuAvagoCfgSize) != MCD_OK)
             {
                 MCD_DBG_ERROR(" mcdServiceCpuFwPostInit mcdServiceCpuWrite failed\n");
                 return MCD_FAIL;
             }
         }

#else /*MCD_IPC_CNV_ENABLE - swap */
         /* swap data for BIG ENDIAN CPU */
         {
#define OFFSET_AAPL(_member) ((MCD_U32)((MCD_UINTPTR)(&(((Aapl_t*)NULL)->_member))))
             unsigned int dstAddr = (unsigned int)serviceCpuAvagoCfgAddr;
             unsigned int *pSrc = (unsigned int *)pDev->serdesDev;
             unsigned int w, i;
             /* sizes in 32-bit words */
             struct
             {
                 MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat;
                 unsigned int upperBound;
             } formats[] =
             {
                 {MCD_IPC_CNV_WORD32_FORMAT_U32_E,  (OFFSET_AAPL(ip_rev) / 4)},
                 {MCD_IPC_CNV_WORD32_FORMAT_2U16_E, (OFFSET_AAPL(spico_running) / 4)},
                 {MCD_IPC_CNV_WORD32_FORMAT_4U8_E,  (OFFSET_AAPL(return_code) / 4)},
                 {MCD_IPC_CNV_WORD32_FORMAT_U32_E,  (OFFSET_AAPL(async_cancel) / 4)+1}
             };
             unsigned int numOfFormats = sizeof(formats) / sizeof(formats[0]);
             unsigned int formatIdx;

             for (i = 0, formatIdx = 0; (1); i++, pSrc++, dstAddr += 4)
             {
                 if (i >= formats[formatIdx].upperBound) formatIdx++;
                 if (formatIdx >= numOfFormats) break;
                 if (dstAddr >= serviceCpuAvagoCfgAddr + serviceCpuAvagoCfgSize)
                     break;
                 w = mcdInternalIpcBeToSwappedLeConvert(
                     formats[formatIdx].wordFormat, *pSrc);
                 if (mcdServiceCpuWrite(pDev, dstAddr, &w, 1) != MCD_OK)
                 {
                     MCD_DBG_ERROR(" mcdServiceCpuFwPostInit mcdServiceCpuWrite failed\n");
                     return MCD_FAIL;
                 }
             }
#undef OFFSET_AAPL
         }

#endif /*MCD_IPC_CNV_ENABLE*/

         if (bootMode == MCD_REGULAR_BOOT_MODE)
         {
             if (mcdSerdesAaplInitIpc(pDev) != MCD_OK) 
                 {
                     MCD_DBG_ERROR(" mcdServiceCpuFwPostInit Failed to init Avago AAPL\n");
                     return MCD_FAIL;
                 }
         }


        /* In order provide access to Service CPU real-time log (AP and HWS)
        ** The Host is required to receive the LOGs parameters addresses.
        ** after that the LOGs can be access from Host
        */
        /* Service CPU AP Log */
        if (mcdApPortCtrlDebugGet(pDev, &mcdApDebug) == MCD_OK)
        {
            mcdApPortCtrlDebugParamsSet(mcdApDebug.fwLogBaseAddr    - mcdApDebug.fwBaseAddr,
                                        mcdApDebug.fwLogCountAddr   - mcdApDebug.fwBaseAddr,
                                        mcdApDebug.fwLogPointerAddr - mcdApDebug.fwBaseAddr,
                                        mcdApDebug.fwLogResetAddr   - mcdApDebug.fwBaseAddr);

        }
        else
        {
             MCD_DBG_ERROR(" mcdServiceCpuFwPostInit Failed to retrive FW AP LOG parameters\n");
             return MCD_FAIL;
        }
        /* Service CPU Hws Log */
        if (mcdLogGetIpc(pDev, &mcdHwsLog) == MCD_OK)
        {
            mcdLogParamsSet(mcdHwsLog.fwLogBaseAddr    - mcdHwsLog.fwBaseAddr,
                            mcdHwsLog.fwLogCountAddr   - mcdHwsLog.fwBaseAddr,
                            mcdHwsLog.fwLogPointerAddr - mcdHwsLog.fwBaseAddr,
                            mcdHwsLog.fwLogResetAddr   - mcdHwsLog.fwBaseAddr,
                            mcdHwsLog.fwPollingDbAddr  - mcdHwsLog.fwBaseAddr);
        }
        else
        {
             MCD_DBG_ERROR(" mcdServiceCpuFwPostIni Failed to retrive FW HWS LOG parameters\n");
             return MCD_FAIL;
        }
    }
    else
    {
        MCD_DBG_ERROR(" mcdServiceCpuFwPostInit Failed to load Avago AAPL\n");
        return MCD_FAIL;
    }

    return MCD_OK;
}

/**
* @internal mcdInternalGetQueueId function
* @endinternal
*
* @brief   finds free queue for Host 2 FW connection
*
* @param[in] pDev
* @param[in] queueId                  - pointer to queue ID
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_U32 mcdInternalGetQueueId
(
    IN  MCD_DEV_PTR pDev,
    OUT MCD_U32 * queueId
)
{
    MCD_U32   i;

    for (i = MCD_IPC_TX_0_CH_ID; i < MCD_MAX_HOST2SCPU_REQ_MSG_NUM; i++)
    {
        if (pDev->mcdIpcQueueIdPool[i] == MCD_IPC_FREE_QUEUE)
        {
            *queueId = i;
            pDev->mcdIpcQueueIdPool[i] = MCD_IPC_QUEUE_BUSY;
            return MCD_OK;
        }
    }

    if (i == MCD_MAX_HOST2SCPU_REQ_MSG_NUM)
    {
        pDev->mcdIpcStatistics.mcdIpcGenFailureCount++;
        MCD_DBG_ERROR("No free Host2SCPU TX message\n");
        return MCD_STATUS_NO_RESOURCES;
    }

    return MCD_OK;
}

/**
* @internal mcdInternalReturnQueueId function
* @endinternal
*
* @brief   returns queue Id to the pool
*
* @param[in] pDev
* @param[in] queueId                  - queue Id
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalReturnQueueId
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32 queueId
)
{
    if (queueId >= MCD_MAX_HOST2SCPU_REQ_MSG_NUM)
    {
        pDev->mcdIpcStatistics.mcdIpcGenFailureCount++;
        MCD_DBG_ERROR("mcdInternalReturnQueueId queue ID %d doesn't exist \n", queueId);
        return MCD_STATUS_BAD_PARAM;
    }

    pDev->mcdIpcQueueIdPool[queueId] = MCD_IPC_FREE_QUEUE;

    return MCD_OK;

}

/**
* @internal mcdInternalIpcCtrlMsgTx function
* @endinternal
*
* @brief   Send IPC message from Host to FW
*
* @param[in] txCtrlMsg                - pointer to the message
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalIpcCtrlMsgTx
(
    IN MCD_DEV_PTR pDev,
    IN MCD_IPC_CTRL_MSG_STRUCT *txCtrlMsg
)
{
    /* Check that the message is valid: msg type and queueId are in the defined range */
    if ((txCtrlMsg->ctrlMsgType >= MCD_IPC_LAST_CTRL_MSG_TYPE ) ||
         (txCtrlMsg->msgQueueId >= MCD_MAX_SCPU2HOST_REPLY_QUEUE_NUM))
    {
        pDev->mcdIpcStatistics.mcdPortIpcFailureCount[txCtrlMsg->msgData.portGeneral.phyPortNum]++;
        MCD_DBG_ERROR ("mcdInternalIpcCtrlMsgTx wrong parameter msg type %d queue ID %d",txCtrlMsg->ctrlMsgType,txCtrlMsg->msgQueueId);
        return MCD_STATUS_BAD_PARAM;
    }

    /* Update counter */
    pDev->mcdIpcStatistics.mcdHostTxMsgCount[txCtrlMsg->ctrlMsgType]++;

    /* Send msg to Service CPU*/
    if (txCtrlMsg->ctrlMsgType != MCD_IPC_PORT_AP_SYS_CFG_VALID_MSG)
    {
        ATTEMPT(mcdInternalServiceCpuMsgSend(pDev, MCD_IPC_LOW_PRI_QUEUE, (char*)txCtrlMsg));
    }
    else /* MCD_IPC_PORT_SYS_CFG_VALID_MSG */
    {
        ATTEMPT(mcdInternalServiceCpuMsgSend(pDev, MCD_IPC_HIGH_PRI_QUEUE, (char*)txCtrlMsg));
    }

    return MCD_OK;
}

/**
* @internal mcdInternalSetIpcInfo function
* @endinternal
*
* @brief   writes IPC data to message structure
*
* @param[in] pDev
* @param[in] msgDataPtr               - pointer to message data
* @param[in] msgLength                - message length
* @param[in] msgType                  - message type
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalSetIpcInfo
(
    IN  MCD_DEV_PTR                 pDev,
    IN  MCD_IPC_CTRL_MSG_DEF_TYPE   msgType,
    OUT MCD_IPC_CTRL_MSG_STRUCT     *msgDataPtr,
    IN  MCD_U32                     msgLength
)
{
    MCD_U32 queueId;

    msgDataPtr->devNum      = 0; /*devNum;*/
    msgDataPtr->msgLength   = (MCD_U8)msgLength;
    msgDataPtr->ctrlMsgType = (MCD_U8)msgType;
    ATTEMPT(mcdInternalGetQueueId(pDev, &queueId));
    msgDataPtr->msgQueueId  = (MCD_U8)queueId;

    return MCD_OK;
}

/**
* @internal mcdInternalIpcReplyMsgRx function
* @endinternal
*
* @brief   Gets reply from HW Services to the Host
*
* @param[in] pDev
* @param[in] queueId                  - queue ID
* @param[in] msgId                    - message ID
* @param[in] rxReplyData              - pointer to message
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalIpcReplyMsgRx
(
    IN  MCD_DEV_PTR                 pDev,
    IN  MCD_IPC_CTRL_MSG_DEF_TYPE   msgId,
    IN  MCD_U32                     queueId,
    OUT MCD_IPC_REPLY_MSG_STRUCT    *rxReplyData
)
{
    MCD_STATUS rcode;
    MCD_U32 replyTimeout = 100;

    /* Wait for message from Service CPU */
    do
    {
        rcode = mcdInternalServiceCpuMsgRecv(pDev, queueId, (char*)rxReplyData);
        if (rcode == MCD_OK)
        {
            break;
        }
        else
        {
            mcdWait(pDev,1);
            replyTimeout--;
        }
    } while (replyTimeout > 0);

    /* Free the queue */
    ATTEMPT(mcdInternalReturnQueueId(pDev, queueId));

    if (rcode != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInternalIpcReplyMsgRx: Failed to read from channel %d\n", queueId);
        return (MCD_FAIL);
    }

    if (rxReplyData->replyTo != (MCD_U32)msgId)
    {
        pDev->mcdIpcStatistics.mcdIpcGenFailureCount++;
        MCD_DBG_ERROR ("mcdInternalIpcReplyMsgRx wrong msg ID %d Expected %d queue ID %d\n",rxReplyData->replyTo, msgId,queueId);
        return MCD_STATUS_BAD_PARAM;
    }

    /* Updte statistics*/
    pDev->mcdIpcStatistics.mcdHostRxMsgCount[msgId]++;

    return MCD_OK;
}


/**
* @internal mcdInternalIpcSendRequestAndGetReply function
* @endinternal
*
* @brief   Gets reply from FW to the Host
*
* @param[in] pDev
* @param[in] requestMsg               - pointer to request message
* @param[in] replyData                - pointer to reply message
* @param[in] msgId                    - message ID
*
* @retval 0                        - on success
* @retval 1                        - on errorMCD_U8 devNum,
*                                       MCD_IPC_CTRL_MSG_STRUCT msgDataPtr,
*                                       MCD_U32 msgLength,
*/
MCD_STATUS mcdInternalIpcSendRequestAndGetReply
(
    IN  MCD_DEV_PTR                 pDev,
    IN  MCD_IPC_CTRL_MSG_STRUCT     *requestMsg,
    OUT MCD_IPC_REPLY_MSG_STRUCT    *replyData,
    IN  MCD_U32                     msgLength,
    IN  MCD_IPC_CTRL_MSG_DEF_TYPE   msgId
)
{
    MCD_U32 msgQueueId;
    MCD_U8 revert = 0;
    MCD_STATUS rc;

    if (pDev->highAvailabilityMode)
    {
        revert = 1;
        /* need to enable Mdio Write during HighAvailability at this phase */
        pDev->highAvailabilityMode = MCD_FALSE;
    }
    /* Set IPC info */
    rc = mcdInternalSetIpcInfo (pDev, msgId, requestMsg, msgLength);
    if (rc != MCD_OK)
    {
        if (revert)
        {
            pDev->highAvailabilityMode = MCD_TRUE;
        }
        MCD_DBG_ERROR("mcdInternalSetIpcInfo error, return value %d \n", rc);
        return rc;
    }
    msgQueueId = requestMsg->msgQueueId;

    /* Send IPC message */
    rc = mcdInternalIpcCtrlMsgTx(pDev, requestMsg);
    if (rc != MCD_OK)
    {
        if (revert)
        {
            pDev->highAvailabilityMode = MCD_TRUE;
        }
        MCD_DBG_ERROR("mcdInternalIpcCtrlMsgTx error, return value %d \n", rc);
        return rc;
    }

    /* Wait for reply */
    rc = mcdInternalIpcReplyMsgRx(pDev, msgId, msgQueueId, replyData);
    if (rc != MCD_OK)
    {
        if (revert)
        {
            pDev->highAvailabilityMode = MCD_TRUE;
        }
        MCD_DBG_ERROR("mcdInternalIpcReplyMsgRx error, return value %d \n", rc);
        return rc;
    }

    if (revert)
    {
        pDev->highAvailabilityMode = MCD_TRUE;
    }

    return MCD_OK;
}

MCD_U16 mcdInternalPortApGetOption
(
    MCD_DEV_PTR                 pDev,
    MCD_U16                     phyPortNum
)
{
    MCD_U16 option = 0;
    MCD_U16 supFec = 0;
    MCD_U16  reqFec = 0;
    MCD_U16 reqAdvFec = 0;
    MCD_U16 consFecAbil = 0;
    MCD_U16 consFecReq = 0;
    MCD_U16 ctleBiasValue = 0;
    MCD_U8  noPpmMode = 0;

    ctleBiasValue = (MCD_U16)pDev->apCfg[phyPortNum].ctleBiasVal;
    noPpmMode = pDev->apCfg[phyPortNum].noPpmMode;
    if (pDev->apCfg[phyPortNum].modesVector & (MCD_AN_100GBASE_KR4 | MCD_AN_100GBASE_CR4 ))
    {
        reqFec = 1;
        supFec = 1;
    }

    if (pDev->apCfg[phyPortNum].modesVector & (MCD_AN_10GBase_KR | MCD_AN_40GBASE_KR4 | MCD_AN_40GBASE_CR4 ))
    {
        if (pDev->apCfg[phyPortNum].fecSup)
        {
            supFec = 1;
        }
        if (pDev->apCfg[phyPortNum].fecReq == MCD_FC_FEC)
        {
            reqFec = 1;
        }
    }

    if ((pDev->apCfg[phyPortNum].modesVector ==  MCD_AN_25GBase_KR1S ) && (pDev->apCfg[phyPortNum].fecReq))
        reqAdvFec = MCD_FC_FEC;
    else if((pDev->apCfg[phyPortNum].modesVector & 0x400)  && (pDev->apCfg[phyPortNum].fecReq == MCD_FC_FEC))
        reqAdvFec = MCD_FC_FEC;
    else if ((pDev->apCfg[phyPortNum].modesVector & 0x400 ) && (pDev->apCfg[phyPortNum].fecReq == MCD_RS_FEC))
        reqAdvFec = MCD_RS_FEC;
    /** [10:10]consortium (RS-FEC) ability (F1)
    ** [11:11]consortium (BASE-R FEC) ability (F2)
    ** [12:12]consortium (RS-FEC) request (F3)
    ** [13:13]consortium (BASE-R FEC) request (F4)*/

    else if((pDev->apCfg[phyPortNum].modesVector & ( MCD_AN_25GBase_KR1_CONSORTIUM | MCD_AN_25GBase_CR1_CONSORTIUM | \
                                                    MCD_AN_50GBase_KR2_CONSORTIUM | MCD_AN_50GBase_CR2_CONSORTIUM )) && (pDev->apCfg[phyPortNum].fecReq == MCD_FC_FEC))
    {

        consFecAbil = MCD_FC_FEC | MCD_RS_FEC;
        consFecReq  = MCD_FC_FEC;

    }
    else if ((pDev->apCfg[phyPortNum].modesVector & (MCD_AN_25GBase_KR1_CONSORTIUM | MCD_AN_25GBase_CR1_CONSORTIUM | \
                                                     MCD_AN_50GBase_KR2_CONSORTIUM | MCD_AN_50GBase_CR2_CONSORTIUM)) && (pDev->apCfg[phyPortNum].fecReq == MCD_RS_FEC))
    {
        consFecAbil = MCD_FC_FEC | MCD_RS_FEC;
        consFecReq  = MCD_RS_FEC;
   }
    option = (MCD_U16)pDev->apCfg[phyPortNum].fcPause       |
                       (MCD_U16)pDev->apCfg[phyPortNum].fcAsmDir << 1 |
                        supFec      << 4 |
                        reqFec      << 5 |
                        reqAdvFec   << 7 |
                        ctleBiasValue << 8 |
                        (MCD_BOOL)pDev->apCfg[phyPortNum].nonceDis << 9 |
                        consFecAbil << 10 |
                        consFecReq  << 12 |
                        noPpmMode   << 14;
    return option;
}

MCD_STATUS mcdInternalPortApStartIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U16                     phyPortNum,
    MCD_BOOL                    retimerMode
)
{
    MCD_IPC_CTRL_MSG_STRUCT     requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT    replyData;
    MCD_IPC_PORT_AP_DATA_STRUCT apCfgIpc;

/*

 MCD_AN_1000BASE_KX                            0x0001
 MCD_AN_10GBase_KX4                            0x0002
 MCD_AN_10GBase_KR                             0x0004
 MCD_AN_40GBASE_KR4                            0x0008
 MCD_AN_40GBASE_CR4                            0x0010
 MCD_AN_100GBASE_CR10                          0x0020
 MCD_AN_100GBASE_KP4                           0x0040
 MCD_AN_100GBASE_KR4                           0x0080
 MCD_AN_100GBASE_CR4                           0x0100
 MCD_AN_25GBase_KR1S                           0x0200
 MCD_AN_25GBASE_KCR                            0x0400
 MCD_AN_25GBase_KR1_CONSORTIUM                 0x0800
 MCD_AN_25GBase_CR1_CONSORTIUM                 0x1000
 MCD_AN_50GBase_KR2_CONSORTIUM                 0x2000
 MCD_AN_50GBase_CR2_CONSORTIUM                 0x4000

*/
    MCD_U16 slice = phyPortNum / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    MCD_U16 lineRxRemapVector = 0;
    MCD_U16 lineTxRemapVector = 0;
    apCfgIpc.retimerMode = retimerMode;
    apCfgIpc.phyPortNum = phyPortNum;
    apCfgIpc.laneNum = (MCD_U8)pDev->apCfg[phyPortNum].apLaneNum;
    apCfgIpc.pcsNum  = (MCD_U8)pDev->apCfg[phyPortNum].apLaneNum;
    apCfgIpc.macNum  = (MCD_U8)phyPortNum;
    apCfgIpc.advMode = pDev->apCfg[phyPortNum].modesVector;
    apCfgIpc.enSdTuningApRes = pDev->apCfg[phyPortNum].enSdTuningApRes;
    apCfgIpc.options = mcdInternalPortApGetOption(pDev,phyPortNum);
    apCfgIpc.polarityVector = (MCD_U8)pDev->apCfg[phyPortNum].polarityVector;
    apCfgIpc.portGroup = 0;

    if (pDev->laneRemapCfg[slice].lineRemapMode == MCD_LANE_REMAP_ENABLE)
    {
        lineRxRemapVector = pDev->laneRemapCfg[slice].lineRxRemapVector;;
        lineTxRemapVector = pDev->laneRemapCfg[slice].lineTxRemapVector;
    }
    apCfgIpc.rxRemapVector  = lineRxRemapVector;
    apCfgIpc.txRemapVector  = lineTxRemapVector;

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apConfig = apCfgIpc;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_AP_DATA_STRUCT),
                                                MCD_IPC_PORT_AP_ENABLE_MSG));

    return (replyData.returnCode);
}

MCD_STATUS mcdApSerdesRxParametersManualSetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U16                     phyPortNum,
    MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE  *rxCfgPtr
)
{
    MCD_IPC_CTRL_MSG_STRUCT     requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT    replyData;
    MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT rxCfgOverride;

    if (rxCfgPtr == NULL)
    {
        return MCD_FAIL;
    }

    rxCfgOverride.phyPortNum = phyPortNum;
    rxCfgOverride.portGroup = 0;
    rxCfgOverride.serdesSpeed = rxCfgPtr->serdesSpeed;
    rxCfgOverride.bandLoopWidth = (MCD_U8) ((rxCfgPtr->ctleParams.bandWidth & 0xF) |
        ((rxCfgPtr->ctleParams.loopBandwidth & 0xF) << MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE_LOOPWIDTH_SHIFT));
    rxCfgOverride.dcGain = (MCD_U8)(rxCfgPtr->ctleParams.dcGain & 0xFF);
    rxCfgOverride.lfHf = (MCD_U8)((rxCfgPtr->ctleParams.lowFrequency & 0xF) |
        ((rxCfgPtr->ctleParams.highFrequency & 0xF) << MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE_HF_SHIFT));
    rxCfgOverride.squelch = (MCD_U16)(rxCfgPtr->ctleParams.squelch & 0xFFFF);
    rxCfgOverride.fieldOverrideBmp = (MCD_U16)(rxCfgPtr->fieldOverrideBmp & 0xFFFF);
    rxCfgOverride.etlMinDelay = (MCD_U8)(rxCfgPtr->etlParams.etlMinDelay & 0xFF);
    rxCfgOverride.etlMaxDelay = (MCD_U8)((rxCfgPtr->etlParams.etlMaxDelay & 0x7F) |
        ((rxCfgPtr->etlParams.etlEnableOverride & 0x1) << MCD_MAN_TUNE_ETL_CONFIG_OVERRIDE_ENABLE_SHIFT));


        /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.portSerdesRxConfigOverride = rxCfgOverride;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
        /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT),
                                                MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_MSG));

    return (replyData.returnCode);

}

MCD_STATUS mcdApSerdesTxParametersManualSetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U16                     phyPortNum,
    MCD_PORT_AP_SERDES_TX_CONFIG  *txCfgPtr
)
{
    MCD_IPC_CTRL_MSG_STRUCT     requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT    replyData;
    MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT txCfgOverride;

    if (txCfgPtr == NULL)
    {
        return MCD_FAIL;
    }

    txCfgOverride.phyPortNum = phyPortNum;
    txCfgOverride.portGroup = 0;
    txCfgOverride.serdesSpeed = txCfgPtr->serdesSpeed;
    txCfgOverride.serdesTxParams = ((txCfgPtr->txAmp & 0x1F) |
                                    ((txCfgPtr->emph0 & 0x1F) << MCD_MAN_TX_TUNE_EMPH0_OVERRIDE_ENABLE_SHIFT) |
                                    ((txCfgPtr->emph1 & 0x1F) << MCD_MAN_TX_TUNE_EMPH1_OVERRIDE_ENABLE_SHIFT));
    txCfgOverride.txOverrideBmp = txCfgPtr->txOverrideBmp;

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.portSerdesTxConfigOverride = txCfgOverride;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
        /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT),
                                                MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_MSG));

    return (replyData.returnCode);

}


MCD_STATUS mcdInternalPortApStopIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U16                     phyPortNum
)
{
    MCD_IPC_CTRL_MSG_STRUCT     requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT    replyData;

    MCD_IPC_PORT_AP_DATA_STRUCT apCfgIpc = {0, phyPortNum, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apConfig = apCfgIpc;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_AP_DATA_STRUCT),
                                                MCD_IPC_PORT_AP_DISABLE_MSG));

    return (replyData.returnCode);
}

/**
* @internal mcdSerdesCfgAddrGetIpc function
* @endinternal
*
* @brief   Return Avago Serdes Configuration structure address
*
* @param[in] pDev
*                                      phyPortNum   - physical port number
*
* @param[out] avagoCfgAddr             - Serdes Configuration structure address
* @param[out] avagoCfgSize             - Serdes Configuration structure size
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSerdesCfgAddrGetIpc
(
   MCD_DEV_PTR                 pDev,
   MCD_U32                     *avagoCfgAddr,
   MCD_U32                     *avagoCfgSize
)
{
    MCD_IPC_CTRL_MSG_STRUCT   requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT  replyData;
    MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET *avagoAddrIpc;
    MCD_IPC_PORT_INFO_STRUCT  avagoAddr = {0, 0, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.avagoAddrGet = avagoAddr;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AVAGO_SERDES_INIT_MSG));

    avagoAddrIpc = &(replyData.readData.portAvagoAaplGet);

    /* Update reply parameters */
    *avagoCfgAddr = avagoAddrIpc->addr;
    *avagoCfgSize = avagoAddrIpc->size;

    return (replyData.returnCode);
}

/**
* @internal mcdSerdesAaplInitIpc function
* @endinternal
*
* @brief   Init Serdes Configuration structure pointers parameters, on service CPU, with NULL values.
*
* @param[in] pDev
*                                      phyPortNum  - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSerdesAaplInitIpc
(
    MCD_DEV_PTR                 pDev
)
{
    MCD_IPC_CTRL_MSG_STRUCT  requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;
    MCD_IPC_PORT_INFO_STRUCT avagoAaplInitIpc = {0, 0, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.avagoAaplInit = avagoAaplInitIpc;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AVAGO_SERDES_RESET_DATA_MSG));

    return (replyData.returnCode);
}

/**
* @internal mcdSetSquelchRxClockControlIpc function
* @endinternal
*
* @brief   Sends to Service CPU Squelch parameters
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] clckCtrl                 -
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSetSquelchRxClockControlIpc
(
   MCD_DEV_PTR                 pDev,
   MCD_U32                     phyPortNum,
   MCD_RX_CLOCK_CTRL_TYPE      clckCtrl
)
{

    MCD_IPC_CTRL_MSG_STRUCT requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.rxClockControl.phyPortNum = phyPortNum;
    requestMsg.msgData.rxClockControl.clckCtrlPin = clckCtrl;
    requestMsg.msgData.rxClockControl.portMode = pDev->portConfig[phyPortNum].portMode;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
     /* Send request to Service CPU and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT),
                                                MCD_IPC_RX_CLOCK_CTRL_PIN_SET_MSG));

    return (replyData.returnCode);
}

/**
* @internal mcdPortApStatsGetIpc function
* @endinternal
*
* @brief   Send message to retrive AP port stats parameters
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] apStats                  - AP Stats parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortApStatsGetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U32                     phyPortNum,
    MCD_U32                     *apStats
)
{
    MCD_IPC_CTRL_MSG_STRUCT  requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;
    MCD_IPC_PORT_REPLY_AP_STATS_GET *apStatsIpc;
    MCD_AP_PORT_STATS               *apStatsReply = (MCD_AP_PORT_STATS*)apStats;
    MCD_IPC_PORT_INFO_STRUCT         apPortStats = {0, phyPortNum, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apStatsGet = apPortStats;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AP_STATS_MSG));

    apStatsIpc = &(replyData.readData.portApStatsGet);

    /* Update reply parameters */
    apStatsReply->txDisCnt          = apStatsIpc->txDisCnt;
    apStatsReply->abilityCnt        = apStatsIpc->abilityCnt;
    apStatsReply->abilitySuccessCnt = apStatsIpc->abilitySuccessCnt;
    apStatsReply->linkFailCnt       = apStatsIpc->linkFailCnt;
    apStatsReply->linkSuccessCnt    = apStatsIpc->linkSuccessCnt;
    apStatsReply->hcdResoultionTime = apStatsIpc->hcdResoultionTime;
    apStatsReply->linkUpTime        = apStatsIpc->linkUpTime;

    return (replyData.returnCode);
}

/**
* @internal mcdPortApDebugGetIpc function
* @endinternal
*
* @brief   Return AP debug information
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] apDebug                  - AP debug parameters
*
* @param[out] apDebug                  - AP debug parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortApDebugGetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U32                     phyPortNum,
    MCD_U32                     *apDebug
)
{
    MCD_IPC_CTRL_MSG_STRUCT   requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT  replyData;
    MCD_IPC_LOG_GET           *apDebugIpc;
    MCD_FW_LOG                *apDebugReply = (MCD_FW_LOG*)apDebug;
    MCD_IPC_PORT_INFO_STRUCT  apPortDebug = {0, phyPortNum, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.logGet = apPortDebug;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AP_DEBUG_GET_MSG));

    apDebugIpc = &(replyData.readData.logGet);

    /* Update reply parameters */
    apDebugReply->fwBaseAddr       = apDebugIpc->fwBaseAddr;
    apDebugReply->fwLogBaseAddr    = apDebugIpc->logBaseAddr;
    apDebugReply->fwLogCountAddr   = apDebugIpc->logCountAddr;
    apDebugReply->fwLogPointerAddr = apDebugIpc->logPointerAddr;
    apDebugReply->fwLogResetAddr   = apDebugIpc->logResetAddr;

    return (replyData.returnCode);
}

/**
* @internal mcdLogGetIpc function
* @endinternal
*
* @brief   Return FW Hws log information
*
* @param[in] pDev
*
* @param[out] hwsLogPtr                - hws log parameters pointer
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
static MCD_STATUS mcdLogGetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_FW_LOG                 *hwsLogPtr
)
{
    MCD_IPC_CTRL_MSG_STRUCT    requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT   replyData;
    MCD_IPC_LOG_GET            *ipcReplay;
    MCD_FW_LOG                 *debugReply = hwsLogPtr;
    MCD_IPC_PORT_INFO_STRUCT   hwsPortDebug = {0, 0, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.logGet = hwsPortDebug;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_HWS_LOG_GET_MSG));

    ipcReplay = &(replyData.readData.logGet);

    /* Update reply parameters */
    debugReply->fwBaseAddr       = ipcReplay->fwBaseAddr;
    debugReply->fwLogBaseAddr    = ipcReplay->logBaseAddr;
    debugReply->fwLogCountAddr   = ipcReplay->logCountAddr;
    debugReply->fwLogPointerAddr = ipcReplay->logPointerAddr;
    debugReply->fwLogResetAddr   = ipcReplay->logResetAddr;
    debugReply->fwPollingDbAddr  = ipcReplay->pollingDbAddr;

    return (replyData.returnCode);
}

/**
* @internal mcdApPortCtrlDebugGet function
* @endinternal
*
* @brief   Return AP debug information
*
* @param[in] pDev
*                                      phyPortNum - physical port number
*
* @param[out] apDebug                  - AP debug parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlDebugGet
(
    MCD_DEV_PTR                 pDev,
    MCD_FW_LOG                  *apDebug
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApPortCtrlDebugGet: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }


    ATTEMPT(mcdPortApDebugGetIpc(pDev, 0, (MCD_U32*)apDebug));

    return MCD_OK;
}

MCD_STATUS mcdAutoNegPortCtrlStart
(
    MCD_DEV_PTR             pDev,
    MCD_U16                 phyPortNum,
    MCD_BOOL                retimerMode
)
{
    MCD_STATUS rc;
    MCD_U32    loopCount = 100;

    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdAutiNegPortCtrlStart: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }


    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    /* Sometimes, the FW is busy with other tasks and the enable
       command might be reply with "GT_NO_RESOURCE";
       Adding mcdWait and looping the request for 100 times
       will ensure the command will be execute once the resource
       will be available */
    do {
        rc = mcdInternalPortApStartIpc(pDev, phyPortNum, retimerMode);
        /* If succeed ... that will be the reply most of the times */
        if (rc == MCD_OK) {
            break;
        }
        /* In case real ERROR happens - goes out with ATTEMPT */
        if (rc == MCD_CREATE_ERROR) {
            ATTEMPT(rc);
        }
        /* If still not success - sleep 10 msec */
        mcdWait(pDev,10);

    }  while (loopCount--);
    /* If still fails after the loopCount was expired - print ATTEMPT */
    ATTEMPT(rc);

    return MCD_OK;
}

MCD_STATUS mcdApSerdesRxParametersManualSetStart
(
    MCD_DEV_PTR                         pDev,
    MCD_U16                             phyPortNum,
    MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE   *rxCfgPtr
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApSerdesRxParametersManualSetStart: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    if ((rxCfgPtr->serdesSpeed != MCD_10_3125G) && (rxCfgPtr->serdesSpeed != MCD_25_78125G))
    {
        MCD_DBG_ERROR("mcdApSerdesRxParametersManualSetStart: invalid serdes speed.\n");
        return MCD_FAIL;
    }

    ATTEMPT(mcdApSerdesRxParametersManualSetIpc(pDev, phyPortNum, rxCfgPtr));

    return MCD_OK;
}

MCD_STATUS mcdApSerdesTxParametersManualSetStart
(
    MCD_DEV_PTR                         pDev,
    MCD_U16                             phyPortNum,
    MCD_PORT_AP_SERDES_TX_CONFIG        *txCfgPtr
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApSerdesTxParametersManualSetStart: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    if ((txCfgPtr->serdesSpeed != MCD_10_3125G) && (txCfgPtr->serdesSpeed != MCD_25_78125G))
    {
        MCD_DBG_ERROR("mcdApSerdesTxParametersManualSetStart: invalid serdes speed.\n");
        return MCD_FAIL;
    }

    ATTEMPT(mcdApSerdesTxParametersManualSetIpc(pDev, phyPortNum, txCfgPtr));

    return MCD_OK;
}

MCD_STATUS mcdAutoNegPortCtrlStop
(
    MCD_DEV_PTR             pDev,
    MCD_U16                 phyPortNum
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("%s: MCD_DEV pointer is NULL.\n", __func__);
        return MCD_STATUS_ERR_DEV;
    }

    if(phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    if(mcdInternalPortApStopIpc(pDev, phyPortNum) != MCD_OK)
    {
        MCD_DBG_INFO("INFO: %s: AP port stop on PortNum %d is already disabled\n", __func__, phyPortNum);
    }

    return MCD_OK;
}

/**
* @internal mcdInternalPortApStatusGetIpc function
* @endinternal
*
* @brief   Returns the AP port resolution info.
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStatusGetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U32 phyPortNum,
    MCD_U32 *apStatus
)
{
    MCD_IPC_CTRL_MSG_STRUCT          requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT         replyData;
    MCD_IPC_PORT_REPLY_AP_STATUS_GET *apStatusIpc;
    MCD_AP_PORT_STATUS               *apStatusReply = (MCD_AP_PORT_STATUS*)apStatus;
    MCD_IPC_PORT_INFO_STRUCT          apPortStatus = {0, phyPortNum, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apStatusGet = apPortStatus;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AP_STATUS_MSG));

    apStatusIpc = &(replyData.readData.portApStatusGet);

    /* Update reply parameters */
    apStatusReply->apLaneNum                = apStatusIpc->laneNum;
    apStatusReply->smState                  = apStatusIpc->state;
    apStatusReply->smStatus                 = apStatusIpc->status;
    apStatusReply->arbStatus                = apStatusIpc->ARMSmStatus;
    apStatusReply->hcdResult.hcdFound       = MCD_AP_ST_HCD_FOUND_GET(apStatusIpc->hcdStatus);
    apStatusReply->hcdResult.hcdLinkStatus  = MCD_AP_ST_HCD_LINK_GET(apStatusIpc->hcdStatus);
    apStatusReply->hcdResult.hcdResult      = MCD_AP_ST_HCD_TYPE_GET(apStatusIpc->hcdStatus);
    apStatusReply->postApPortMode           = MCD_AP_ST_HCD_TYPE_GET(apStatusIpc->hcdStatus);
    apStatusReply->hcdResult.hcdFec         = MCD_AP_ST_HCD_FEC_RES_GET(apStatusIpc->hcdStatus);
    apStatusReply->hcdResult.hcdFcRxPauseEn = MCD_AP_ST_HCD_FC_RX_RES_GET(apStatusIpc->hcdStatus);
    apStatusReply->hcdResult.hcdFcTxPauseEn = MCD_AP_ST_HCD_FC_TX_RES_GET(apStatusIpc->hcdStatus);

    return (replyData.returnCode);
}
/**
* @internal mcdPortApIntropGetIpc function
* @endinternal
*
* @brief   Return AP port introp information
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortApIntropGetIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U32 phyPortNum,
    MCD_U32 *apIntrop
)
{
    MCD_IPC_CTRL_MSG_STRUCT          requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT         replyData;
    MCD_IPC_PORT_REPLY_AP_INTROP_GET *apIntropIpc;
    MCD_AP_PORT_INTROP               *apIntropReply = (MCD_AP_PORT_INTROP*)apIntrop;
    MCD_IPC_PORT_INFO_STRUCT         apPortIntrop = {0, phyPortNum, 0};

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apIntropGet = apPortIntrop;

    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_INFO_STRUCT),
                                                MCD_IPC_PORT_AP_INTROP_GET_MSG));

    apIntropIpc = &(replyData.readData.portApIntropGet);

    /* Update reply parameters */
    apIntropReply->txDisDuration          = apIntropIpc->txDisDuration;
    apIntropReply->abilityDuration        = apIntropIpc->abilityDuration;
    apIntropReply->abilityMaxInterval     = apIntropIpc->abilityMaxInterval;
    apIntropReply->abilityFailMaxInterval = apIntropIpc->abilityFailMaxInterval;
    apIntropReply->apLinkDuration         = apIntropIpc->apLinkDuration;
    apIntropReply->apLinkMaxInterval      = apIntropIpc->apLinkMaxInterval;
    apIntropReply->pdLinkDuration         = apIntropIpc->pdLinkDuration;
    apIntropReply->pdLinkMaxInterval      = apIntropIpc->pdLinkMaxInterval;

    return (replyData.returnCode);
}

/**
* @internal mcdPortApIntropSetIpc function
* @endinternal
*
* @brief   Set AP port introp 
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortApIntropSetIpc
(
    MCD_DEV_PTR  pDev,
    MCD_U32      phyPortNum,
    MCD_U32    * apIntrop
)
{
    MCD_IPC_CTRL_MSG_STRUCT  requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;
    MCD_IPC_PORT_AP_INTROP_STRUCT       *localApIntropCfg = (MCD_IPC_PORT_AP_INTROP_STRUCT*)apIntrop;

    MCD_IPC_PORT_AP_INTROP_STRUCT apIntropIpc =
    {
        (MCD_U16)0,
        (MCD_U16)phyPortNum,
        MCD_MODE_NUM,
        localApIntropCfg->attrBitMask,
        localApIntropCfg->txDisDuration,
        localApIntropCfg->abilityDuration,
        localApIntropCfg->abilityMaxInterval,
        localApIntropCfg->abilityFailMaxInterval,
        localApIntropCfg->apLinkDuration,
        localApIntropCfg->apLinkMaxInterval,
        localApIntropCfg->pdLinkDuration,
        localApIntropCfg->pdLinkMaxInterval
    };

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.apIntropSet = apIntropIpc;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to CM3 and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(pDev,&requestMsg,&replyData,
                                                sizeof(MCD_IPC_PORT_AP_INTROP_STRUCT),
                                                MCD_IPC_PORT_AP_INTROP_SET_MSG));

    return (replyData.returnCode);
}


/**
* @internal mcdApPortCtrlStatusGet function
* @endinternal
*
* @brief   Returns the AP port resolution information
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] apStatus                 - AP status parameters
*
* @param[out] apStatus                 - AP/HCD results
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatusGet
(
    MCD_DEV_PTR          pDev,
    MCD_U32              phyPortNum,
    MCD_AP_PORT_STATUS   *apStatus
)
{
    MCD_STATUS rcode;

    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApPortCtrlStatusGet: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }


    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    apStatus->preApPortNum  = phyPortNum;
    apStatus->postApPortNum = phyPortNum;

    rcode = mcdInternalPortApStatusGetIpc(pDev, phyPortNum, (MCD_U32*)apStatus);
    if (rcode == MCD_OK)
    {
        pDev->apRes[phyPortNum].hcdResult = apStatus->hcdResult.hcdResult;
        if (apStatus->hcdResult.hcdFec == 1)
        {
            pDev->apRes[phyPortNum].hcdFec = 2;
        }
        else if (apStatus->hcdResult.hcdFec == 2)
        {
            pDev->apRes[phyPortNum].hcdFec = 1;
        }
        else
            pDev->apRes[phyPortNum].hcdFec = 0;
        pDev->apRes[phyPortNum].hcdFcRxPauseEn = apStatus->hcdResult.hcdFcRxPauseEn;
        pDev->apRes[phyPortNum].hcdFcTxPauseEn = apStatus->hcdResult.hcdFcTxPauseEn;
    }

    return rcode;
}

/**
* @internal mcdApPortCtrlStatsGet function
* @endinternal
*
* @brief   Returns the AP port statistics information
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatsGet
(
    MCD_DEV_PTR             pDev,
    MCD_U32                 phyPortNum,
    MCD_AP_PORT_STATS       *apStats
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApPortCtrlStatsGet: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }


    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }


    ATTEMPT(mcdPortApStatsGetIpc(pDev, phyPortNum, (MCD_U32*)apStats));

    return MCD_OK;
}

/**
* @internal mcdApPortCtrlIntropGet function
* @endinternal
*
* @brief   Return AP port introp information
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlIntropGet
(
    MCD_DEV_PTR             pDev,
    MCD_U32                phyPortNum,
    MCD_AP_PORT_INTROP *apIntrop
)
{
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdApPortCtrlIntropGet: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }


    if (phyPortNum >= 8)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    ATTEMPT(mcdPortApIntropGetIpc(pDev, phyPortNum, (MCD_U32*)apIntrop));

    return MCD_OK;
}

/**
* @internal mcdPortPollingLinkStatusStartIpc function
* @endinternal
*
* @brief   Start Port link status polling.
*
* @param[in] pDev
* @param[in] mdioPort                 - physical port number
* @param[in] retimerMode              - 1 - retimer mode, 0 -PCS mode
*                                      lineSerdesSpeed  - line Serdes Speed
*                                      hostSerdesSpeed  - host Serdes Speed
* @param[in] lineSerdesBitmap         - line Serdes Bitmap (bits 0-7)
* @param[in] hostSerdesBitmap         - host Serdes Bitmap (bits 0-7)
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortPollingLinkStatusStartIpc
(
    MCD_DEV_PTR                   pDev,
    MCD_U16                       mdioPort,
    MCD_BOOL                      retimerMode,
    MCD_BOOL                      retimerWithAP,
    MCD_U16 /*MCD_SERDES_SPEED*/  lineSerdesSpeed,
    MCD_U16 /*MCD_SERDES_SPEED*/  hostSerdesSpeed,
    MCD_U16                       lineSerdesBitmap,
    MCD_U16                       hostSerdesBitmap,
    MCD_U16                       noPpmMode,
    MCD_U8                        calMode,
    MCD_CALIBRATION_ALGO_E        calibrationAlgo,
    MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE  *confidenceInterval,
    MCD_LINE_SIDE_EO_TH_OVERRIDE  *eoThreshold
)
{
    MCD_IPC_CTRL_MSG_STRUCT  requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;
    MCD_U16 slice;
    MCD_U16 hostRxRemapVector = 0;
    MCD_U16 hostTxRemapVector = 0;
    MCD_U16 lineRxRemapVector = 0;
    MCD_U16 lineTxRemapVector = 0;

    mcdMemSet(&requestMsg, 0, sizeof(MCD_IPC_CTRL_MSG_STRUCT));

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdPortPollingLinkStatusStartIpc: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    /* Construct the msg */
    requestMsg.msgData.pollingPortLinkStatusStart.mdioPort          = mdioPort;
    requestMsg.msgData.pollingPortLinkStatusStart.retimerMode       = retimerMode;
    requestMsg.msgData.pollingPortLinkStatusStart.lineSerdesSpeed   = lineSerdesSpeed;
    requestMsg.msgData.pollingPortLinkStatusStart.hostSerdesSpeed   = hostSerdesSpeed;
    requestMsg.msgData.pollingPortLinkStatusStart.lineSerdesBitmap  = lineSerdesBitmap;
    requestMsg.msgData.pollingPortLinkStatusStart.hostSerdesBitmap  = hostSerdesBitmap;
    requestMsg.msgData.pollingPortLinkStatusStart.noPpmMode         = noPpmMode;
    requestMsg.msgData.pollingPortLinkStatusStart.calibrationMode   = calMode;
    requestMsg.msgData.pollingPortLinkStatusStart.calibrationAlgo   = (MCD_U8)calibrationAlgo;
    requestMsg.msgData.pollingPortLinkStatusStart.minEyeThreshold   = eoThreshold->minEyeThreshold;
    requestMsg.msgData.pollingPortLinkStatusStart.maxEyeThreshold   = eoThreshold->maxEyeThreshold;
    requestMsg.msgData.pollingPortLinkStatusStart.lfLowThreshold    = confidenceInterval->lfLowThreshold;
    requestMsg.msgData.pollingPortLinkStatusStart.lfHighThreshold   = (MCD_U32)confidenceInterval->lfHighThreshold;
    requestMsg.msgData.pollingPortLinkStatusStart.hfThreshold       = (MCD_U32)confidenceInterval->hfThreshold;
    if (retimerWithAP) {
        requestMsg.msgData.pollingPortLinkStatusStart.laneNum = (MCD_U16)pDev->apCfg[mdioPort].apLaneNum;
        requestMsg.msgData.pollingPortLinkStatusStart.advMode = pDev->apCfg[mdioPort].modesVector;
        requestMsg.msgData.pollingPortLinkStatusStart.options = mcdInternalPortApGetOption(pDev,mdioPort);
        requestMsg.msgData.pollingPortLinkStatusStart.polarityVector = pDev->apCfg[mdioPort].polarityVector;
        requestMsg.msgData.pollingPortLinkStatusStart.retimerWithAp = MCD_TRUE;
    }

    if (pDev->laneRemapCfg[slice].hostRemapMode == MCD_LANE_REMAP_ENABLE)
    {
        hostRxRemapVector = pDev->laneRemapCfg[slice].hostRxRemapVector;
        hostTxRemapVector = pDev->laneRemapCfg[slice].hostTxRemapVector;
    }
    if (pDev->laneRemapCfg[slice].lineRemapMode == MCD_LANE_REMAP_ENABLE)
    {
        lineRxRemapVector = pDev->laneRemapCfg[slice].lineRxRemapVector;;
        lineTxRemapVector = pDev->laneRemapCfg[slice].lineTxRemapVector;
    }
    requestMsg.msgData.pollingPortLinkStatusStart.hostRxRemapVector  = hostRxRemapVector;
    requestMsg.msgData.pollingPortLinkStatusStart.hostTxRemapVector  = hostTxRemapVector;
    requestMsg.msgData.pollingPortLinkStatusStart.lineRxRemapVector  = lineRxRemapVector;
    requestMsg.msgData.pollingPortLinkStatusStart.lineTxRemapVector  = lineTxRemapVector;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(
        pDev, &requestMsg, &replyData,
        sizeof(MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC),
        MCD_IPC_PORT_POLLING_START_MSG));

    return (replyData.returnCode);
}

/**
* @internal mcdPortPollingLinkStatusStopIpc function
* @endinternal
*
* @brief   Stop Port link status polling.
*
* @param[in] pDev
* @param[in] mdioPort                 - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortPollingLinkStatusStopIpc
(
    MCD_DEV_PTR                   pDev,
    MCD_U16                       mdioPort
)
{
    MCD_IPC_CTRL_MSG_STRUCT  requestMsg;
    MCD_IPC_REPLY_MSG_STRUCT replyData;

    /* initialize replyData */
    mcdMemSet(&replyData, 0, sizeof(MCD_IPC_REPLY_MSG_STRUCT));

    /* Construct the msg */
    requestMsg.msgData.pollingPortLinkStatusStop.mdioPort = mdioPort;

    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
    /* Send request to HWS and wait for the reply */
    ATTEMPT(mcdInternalIpcSendRequestAndGetReply(
        pDev, &requestMsg, &replyData,
        sizeof(MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC),
        MCD_IPC_PORT_POLLING_STOP_MSG));

    return (replyData.returnCode);
}






