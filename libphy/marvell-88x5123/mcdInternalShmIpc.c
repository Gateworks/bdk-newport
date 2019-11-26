/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/
/**
********************************************************************************
* @file mcdInternalShmIpc.c
*
* @brief Low-level IPC implementation
*
* @version   1
********************************************************************************
*/
#include "mcdApiTypes.h"
#include "mcdInternalShmIpc.h"
#include "mcdUtils.h"
#include "mcdAPI.h"

#define MCD_IPC_DEBUG

#ifdef MCD_IPC_DEBUG
int mcdInternalShmIpcTraceEnable = 0;
void mcdInternalShmIpcTraceEnableSet(int enable)
{
    mcdInternalShmIpcTraceEnable = enable;
}
extern int   printf (const char *, ...);
#define DBG_TRACE(x) if (mcdInternalShmIpcTraceEnable) {printf x;}
#else
#define DBG_TRACE(x)
#endif

#ifndef NULL
#define NULL ((void*)0L)
#endif

/* This code can be uses both on Big Endian and Little Endian CPU  */
/* It uses only 32-bit data for both values and IPC-pointers       */
/* IPC-poiners are just offsets from shared memory base address    */
/* IPC-poiners never used in this code as C-laguage pointers       */
/* This code supposes that displascement of structure members from */
/* the beginning of the structue is the same for comilers of both  */
/* Host and Service CPUs and byte swappin inside 32-bit words done */
/* (if needed) inside shmWriteFunc and shmReadFunc functions.      */
/* If payload data structures contain not 32-bit fields caller     */
/* should prepare it in format matching Service CPU format after   */
/* 32-bit words swapping (see upper)                               */

#define IPC_SHM_ALIGN(_size)     (((_size)+3)&(~3))

/* Synchronzation primitives */
#define IPC_OFFSETOF(_type,_member) ((MCD_IPC_U32)((MCD_UINTPTR)&(((_type*)NULL)->_member)))

typedef struct IPC_SHM_MSG_STCT {
    MCD_IPC_U32      ready;
    MCD_IPC_U32      length;
    MCD_IPC_U32      data[1];
} IPC_SHM_MSG_STC;
typedef struct IPC_SHM_FIFO_STCT {
    MCD_IPC_U32      msgSize;
    MCD_IPC_U32      size;
    MCD_IPC_U32      head;
    MCD_IPC_U32      tail;
    MCD_IPC_U32      buffer[1];
} IPC_SHM_FIFO_STC;
/* shared data header */
typedef struct IPC_SHM_DATA_STCT {
    MCD_IPC_U32      bootChnHdr; /* bit 31: owner, bits 30..18 - size, 0 == free */
    MCD_IPC_U32      bootChnData[63]; /* data[0] == opcode */
    MCD_IPC_U32      magic;
    MCD_IPC_U32      size;
    MCD_IPC_U32      registers[MCD_IPC_SHM_NUM_REGS];
    MCD_IPC_PTR      heap;
    MCD_IPC_U32      rxReady[2]; /* slave/master */
    MCD_IPC_PTR      fifos[MCD_IPC_SHM_CHANNELS*2];
} IPC_SHM_DATA_STC;

#define RXFIFO(_shm,_chn)            ((_chn)*2 + ((_shm)->master ^ 1))
#define TXFIFO(_shm,_chn)            ((_chn)*2 + (_shm)->master)

/**
* @internal mcdInternalShmIpcInit function
* @endinternal
*
* @brief   Initialize SHM.
*         Master side also initialize SHM data block (reset SHM, set magick, etc)
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm_virt_addr            - virtual address of shared memory block
* @param[in] shmIoAnchorPtr           - anchor parameter to pass to memory read and write functions
* @param[in] shmWriteFunc             - (pointer to)shared memory write function
* @param[in] shmReadFunc              - (pointer to)shared memory read function
* @param[in] size                     - the  of SHM block
* @param[in] master                   - role: 1 - master, 0 - slave
*
* @param[out] shm                      - SHM control structure
*
* @retval 0                        - on success
*                                       -1       - on failure
*/
int mcdInternalShmIpcInit(
    OUT MCD_IPC_SHM_STC         *shm,
    IN  void                    *shmIoAnchorPtr,
    IN  MCD_IPC_SHM_WRITE_FUNC  shmWriteFunc,
    IN  MCD_IPC_SHM_READ_FUNC   shmReadFunc,
    IN  MCD_IPC_PTR             shm_virt_addr,
    IN  int                     size,
    IN  int                     master
)
{
    IPC_SHM_DATA_STC data;
    MCD_IPC_U32      magic_pos = IPC_OFFSETOF(IPC_SHM_DATA_STC, magic);
    MCD_IPC_STATUS   rc;

    mcdMemSet(shm, 0, sizeof(*shm));
    shm->shmIoAnchorPtr = shmIoAnchorPtr;
    shm->shmWriteFunc   = shmWriteFunc;
    shm->shmReadFunc    = shmReadFunc;
    shm->shm = (MCD_IPC_PTR)shm_virt_addr;
    shm->shmLen = size;
    shm->master = master ? 1 : 0;
    if (master)
    {
        mcdMemSet(&data, 0, sizeof(data));
        data.magic = MCD_IPC_SHM_MAGIC;
        data.size = shm->shmLen;
        data.heap = IPC_SHM_ALIGN(sizeof(IPC_SHM_DATA_STC));
        rc = shm->shmWriteFunc(shm->shmIoAnchorPtr, shm->shm, (sizeof(data) / 4), &data);
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("shmWriteFunc failed at %s:%u\n",__FUNCTION__,__LINE__);
            return -1;
        }

        DBG_TRACE((
            "mcdInternalShmIpcInit stored magic 0x%X size 0x%X heap 0x%X\n",
            (MCD_IPC_UINT)data.magic, (MCD_IPC_UINT)data.size,
            (MCD_IPC_UINT)data.heap));
    }
    else
    {
        /* check magic */
        rc = shm->shmReadFunc(shm->shmIoAnchorPtr, (shm->shm + magic_pos), 1, &data.magic);
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("shmReadFunc failed at %s:%u\n",__FUNCTION__,__LINE__);
            return -1;
        }

        if (data.magic == MCD_IPC_SHM_MAGIC)
        {
            data.magic = MCD_IPC_SHM_MAGIC + 1;
            rc = shm->shmWriteFunc(shm->shmIoAnchorPtr, (shm->shm + magic_pos), 1, &data.magic);
            if (rc != MCD_OK)
            {
                MCD_DBG_ERROR("shmWriteFunc failed at %s:%u\n",__FUNCTION__,__LINE__);
                return -1;
            }
        }
    }
    return 0;
}

static MCD_IPC_PTR mcdInternalShmIpcAlloc(MCD_IPC_SHM_STC *shm, int size)
{
    MCD_IPC_PTR ptr = (MCD_IPC_PTR)0;
    MCD_IPC_PTR heap;
    MCD_IPC_PTR heap_pos;
    MCD_IPC_U32 shm_size;
    MCD_IPC_PTR shm_size_pos;
    MCD_IPC_U32 w_u32;
    MCD_IPC_U32 zero = 0;
    int i;

    heap_pos     = shm->shm + IPC_OFFSETOF(IPC_SHM_DATA_STC, heap);
    shm->shmReadFunc(shm->shmIoAnchorPtr, heap_pos, 1, &w_u32);
    heap     = w_u32;
    shm_size_pos = shm->shm + IPC_OFFSETOF(IPC_SHM_DATA_STC, size);
    shm->shmReadFunc(shm->shmIoAnchorPtr, shm_size_pos, 1, &w_u32);
    shm_size = w_u32;

    size = IPC_SHM_ALIGN(size);
    if ((heap + size) > shm_size)
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcAlloc failed alg_size 0x%X heap 0x%X shm_size 0x%X\n",
             size, heap, shm_size);
        return 0;
    }
    ptr = heap;
    w_u32 = (heap + size);
    shm->shmWriteFunc(shm->shmIoAnchorPtr, heap_pos, 1, &w_u32);
    for (i = 0; (i < size); i += 4)
    {
        shm->shmWriteFunc(shm->shmIoAnchorPtr, (shm->shm + ptr + i) , 1, &zero);
    }
    DBG_TRACE((
        "mcdInternalShmIpcAlloc allocated 0x%X alg_size 0x%X heap 0x%X \n",
        (MCD_IPC_UINT)ptr, (MCD_IPC_UINT)size, (MCD_IPC_UINT)heap));
    return ptr;
}

static MCD_IPC_PTR mcdInternalShmIpcAllocFifo(MCD_IPC_SHM_STC *shm, int size, int msgsize)
{
    int allocsize;
    MCD_IPC_PTR fifoPos;
    IPC_SHM_FIFO_STC fifo;
    MCD_IPC_U32 fifo_hdr_size = IPC_OFFSETOF(IPC_SHM_FIFO_STC, buffer);

    if (size == 0 || msgsize == 0)
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcAllocFifo bad param size 0x%X msgsize 0x%X \n",
            size, msgsize);
        return (MCD_IPC_PTR)0;
    }
    msgsize += IPC_OFFSETOF(IPC_SHM_MSG_STC,data);
    msgsize = IPC_SHM_ALIGN(msgsize);
    allocsize = fifo_hdr_size + (size * msgsize);
    fifoPos = mcdInternalShmIpcAlloc(shm, allocsize);
    if (!fifoPos)
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcAllocFifo not allocated 0x%X bytes \n", allocsize);
        return 0;
    }
    mcdMemSet(&fifo, 0, sizeof(fifo));
    fifo.size = size;
    fifo.msgSize = msgsize;
    shm->shmWriteFunc(shm->shmIoAnchorPtr, (shm->shm + fifoPos), (fifo_hdr_size / 4), &fifo);
    DBG_TRACE((
        "mcdInternalShmIpcAllocFifo allocated fifoPos 0x%X size 0x%X msgsize 0x%X \n",
        (MCD_IPC_UINT)fifoPos, (MCD_IPC_UINT)size, (MCD_IPC_UINT)msgsize));
    return fifoPos;
}

/**
* @internal mcdInternalShmIpcConfigChannel function
* @endinternal
*
* @brief   Configure IPC channel
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number to configure
* @param[in] maxrx                    - max number of messages in Rx FIFO
*                                      must be power of 2
* @param[in] rxsize                   - max message size in Rx FIFO
* @param[in] maxtx                    - max number of messages in Tx FIFO
*                                      must be power of 2
* @param[in] txsize                   - max message size in Tx FIFO
*
* @retval 0                        - on success
*                                       -1     - already configured
*                                       -2     - can't configure (no memory left)
*                                       -3     - bad parameter
*/
int mcdInternalShmIpcConfigChannel(
    IN  MCD_IPC_SHM_STC *shm,
    IN  int             chn,
    IN  int             maxrx,
    IN  int             rxsize,
    IN  int             maxtx,
    IN  int             txsize
)
{
    /* TODO: chheck chn range */
    MCD_IPC_PTR base_fifo_pos;
    MCD_IPC_PTR rx_fifo;
    MCD_IPC_PTR rx_fifo_pos;
    MCD_IPC_PTR tx_fifo;
    MCD_IPC_PTR tx_fifo_pos;
    /* check num of fifo items */

    base_fifo_pos = shm->shm + IPC_OFFSETOF(IPC_SHM_DATA_STC,fifos);
    rx_fifo_pos = base_fifo_pos + (sizeof(MCD_IPC_PTR) * RXFIFO(shm,chn));
    tx_fifo_pos = base_fifo_pos + (sizeof(MCD_IPC_PTR) * TXFIFO(shm,chn));

    ATTEMPT(shm->shmReadFunc(shm->shmIoAnchorPtr, rx_fifo_pos, 1, &rx_fifo));
    ATTEMPT(shm->shmReadFunc(shm->shmIoAnchorPtr, tx_fifo_pos, 1, &tx_fifo));

    if (rx_fifo || tx_fifo)
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcConfigChannel found rx_fifo 0x%X tx_fifo 0x%X \n",
             rx_fifo, tx_fifo);
        return -1; /* already configured */
    }

    if (maxrx != 0)
    {
        rx_fifo = mcdInternalShmIpcAllocFifo(shm, maxrx, rxsize);
        if (rx_fifo == 0)
        {
            MCD_DBG_ERROR("mcdInternalShmIpcConfigChannel rx_fifo allocation error\n");
            return -2; /* no memory */
        }
        ATTEMPT(shm->shmWriteFunc(shm->shmIoAnchorPtr, rx_fifo_pos, 1, &rx_fifo));
    }
    if (maxtx != 0)
    {
        tx_fifo = mcdInternalShmIpcAllocFifo(shm, maxtx, txsize);
        if (tx_fifo == 0)
        {
            MCD_DBG_ERROR("mcdInternalShmIpcConfigChannel tx_fifo allocation error\n");
            return -2; /* no memory */
        }
        ATTEMPT(shm->shmWriteFunc(shm->shmIoAnchorPtr, tx_fifo_pos, 1, &tx_fifo));
    }

    return 0;
}

/**
* @internal mcdInternalShmIpcSend function
* @endinternal
*
* @brief   Send message to IPC channel
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number
* @param[in] data                     -  to send
* @param[in] size                     - data size
*
* @retval 0                        - on success
*                                       -1     - Tx fifo not configured (zero size)
*                                       -2     - full
*                                       -3     - bad parameter: message too long
*                                       -4     - fifo not initialized
*/
int mcdInternalShmIpcSend(
    IN  MCD_IPC_SHM_STC *shm,
    IN  int             chn,
    IN  const void      *data,
    IN  int             size
)
{
    MCD_IPC_PTR base_fifo_pos;
    MCD_IPC_PTR fifo_pos;
    MCD_IPC_PTR w_ptr;
    MCD_IPC_U32 w_u32;
    MCD_IPC_PTR fifo_ptr;
    IPC_SHM_FIFO_STC fifo;
    MCD_IPC_U32 msgNo;
    MCD_IPC_U32 fifo_hdr_size = IPC_OFFSETOF(IPC_SHM_FIFO_STC, buffer);
    MCD_IPC_U32 msg_hdr_size  = IPC_OFFSETOF(IPC_SHM_MSG_STC, data);
    MCD_IPC_U32 msg_hdr_ready_off   = IPC_OFFSETOF(IPC_SHM_MSG_STC, ready);
    MCD_IPC_U32 msg_hdr_length_off  = IPC_OFFSETOF(IPC_SHM_MSG_STC, length);
    MCD_IPC_U32 fifo_hdr_tail_off = IPC_OFFSETOF(IPC_SHM_FIFO_STC, tail);
    MCD_IPC_PTR msg_hdr_ptr;
    IPC_SHM_MSG_STC  msgHdr = {0, 0, {0}};
    MCD_IPC_U32 chn_read_ready_off;
    MCD_IPC_U32 bit;

    if (chn >= MCD_IPC_SHM_CHANNELS)
    {
        MCD_DBG_ERROR("mcdInternalShmIpcSend wrong channel 0x%X \n",chn);
        return -1;
    }

    base_fifo_pos = shm->shm + IPC_OFFSETOF(IPC_SHM_DATA_STC,fifos);
    fifo_pos = base_fifo_pos + (sizeof(MCD_IPC_PTR) * TXFIFO(shm,chn));
    shm->shmReadFunc(shm->shmIoAnchorPtr, fifo_pos, 1, &w_ptr);
    if (w_ptr == 0)
    {
        MCD_DBG_ERROR("mcdInternalShmIpcSend not allocated fifo 0x%X \n",chn);
        return -4; /* fifo not initialized */
    }
    fifo_ptr = shm->shm + w_ptr;
    shm->shmReadFunc(shm->shmIoAnchorPtr, fifo_ptr, (fifo_hdr_size / 4), &fifo);
    if ((fifo.size == 0) || (fifo.msgSize == 0))
    {
        MCD_DBG_ERROR("mcdInternalShmIpcSend wrong fifo header fifo 0x%X \n",chn);
        return -4; /* 0-size */
    }

    if (fifo.msgSize < (size + IPC_OFFSETOF(IPC_SHM_MSG_STC,data)))
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcSend message too long msg_payload_size 0x%X fifo.msgSize 0x%X \n",
             size, fifo.msgSize);
        return -3; /* bad parameter: message too long */
    }

    msgNo = fifo.tail;
    msg_hdr_ptr = fifo_ptr + fifo_hdr_size + (msgNo * fifo.msgSize);

    shm->shmReadFunc(shm->shmIoAnchorPtr, (msg_hdr_ptr + msg_hdr_ready_off), 1, &w_u32);
    if (w_u32/*msgBuffer->ready*/ != 0)
    {
        MCD_DBG_ERROR(
            "mcdInternalShmIpcSend message found ready_flag  0x%X\n", w_u32);
        return -2; /* full */
    }

    /* increment fifo.tail */
    w_u32 = (msgNo + 1) % fifo.size;
    fifo.tail = w_u32;
    shm->shmWriteFunc(shm->shmIoAnchorPtr, (fifo_ptr + fifo_hdr_tail_off), 1, &(fifo.tail));

    /*message body*/
    shm->shmWriteFunc(shm->shmIoAnchorPtr, (msg_hdr_ptr + msg_hdr_size), ((size + 3) / 4), data);
    {
        const MCD_IPC_U32* p = data;
        DBG_TRACE((
            "mcdInternalShmIpcSend message to channel 0x%X size 0x%X data 0x%X 0x%X 0x%X 0x%X\n",
            (MCD_IPC_UINT)chn, (MCD_IPC_UINT)size,
            (MCD_IPC_UINT)p[0], (MCD_IPC_UINT)p[1], (MCD_IPC_UINT)p[2], (MCD_IPC_UINT)p[3]));
    }
    /* message header - ready written last */
    msgHdr.length = size;
    shm->shmWriteFunc(
        shm->shmIoAnchorPtr,
        (msg_hdr_ptr + msg_hdr_length_off), 1, &msgHdr.length);
    msgHdr.ready  = 1;
    shm->shmWriteFunc(
        shm->shmIoAnchorPtr,
        (msg_hdr_ptr + msg_hdr_ready_off), 1, &msgHdr.ready);

    /* raise rxReady bit */
    chn_read_ready_off  = IPC_OFFSETOF(IPC_SHM_DATA_STC, rxReady[shm->master]);
    shm->shmReadFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);
    bit = (1 << chn);
    w_u32 |= bit;
    shm->shmWriteFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);

    return 0;
}

/**
* @internal mcdInternalShmIpcRecv function
* @endinternal
*
* @brief   Receive message from IPC channel
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number
* @param[in,out] size                     - data buffer
*
* @param[out] data                     -  buffer
* @param[in,out] size                     - received data
*
* @retval 1                        - Received
* @retval 0                        - No data (FIFO empty)
*                                       -1     - Rx fifo not configured (zero size)
*/
int mcdInternalShmIpcRecv(
    IN    MCD_IPC_SHM_STC *shm,
    IN    int             chn,
    OUT   void            *data,
    INOUT int             *size
)
{
    MCD_IPC_PTR base_fifo_pos;
    MCD_IPC_PTR fifo_pos;
    MCD_IPC_PTR w_ptr;
    MCD_IPC_U32 w_u32;
    MCD_IPC_PTR fifo_ptr;
    MCD_IPC_U32 fifo_hdr_size = IPC_OFFSETOF(IPC_SHM_FIFO_STC, buffer);
    MCD_IPC_U32 msg_hdr_size  = IPC_OFFSETOF(IPC_SHM_MSG_STC, data);
    MCD_IPC_U32 msg_hdr_ready_off  = IPC_OFFSETOF(IPC_SHM_MSG_STC, ready);
    MCD_IPC_U32 fifo_hdr_head_off = IPC_OFFSETOF(IPC_SHM_FIFO_STC, head);
    MCD_IPC_PTR msg_hdr_ptr;
    IPC_SHM_FIFO_STC fifo;
    IPC_SHM_MSG_STC msgBuffer;
    MCD_IPC_U32 msgNo;
    int dataSize;
    MCD_IPC_U32 bit;
    MCD_IPC_U32 chn_read_ready_off;

    if (chn >= MCD_IPC_SHM_CHANNELS)
    {
        MCD_DBG_ERROR("mcdInternalShmIpcRecv wrong channel 0x%X \n",chn);
        return -1;
    }

    base_fifo_pos = shm->shm + IPC_OFFSETOF(IPC_SHM_DATA_STC,fifos);
    fifo_pos = base_fifo_pos + (sizeof(MCD_IPC_PTR) * RXFIFO(shm,chn));
    shm->shmReadFunc(shm->shmIoAnchorPtr, fifo_pos, 1, &w_ptr);
    if (w_ptr == 0)
    {
        MCD_DBG_ERROR("mcdInternalShmIpcRecv not allocated fifo 0x%X \n",chn);
        return -1; /* fifo not initialized */
    }
    fifo_ptr = shm->shm + w_ptr;
    shm->shmReadFunc(shm->shmIoAnchorPtr, fifo_ptr, (fifo_hdr_size / 4), &fifo);
    if ((fifo.size == 0) || (fifo.msgSize == 0))
    {
        MCD_DBG_ERROR("mcdInternalShmIpcRecv wrong fifo header fifo 0x%X \n",chn);
        return -1; /* 0-size */
    }
    msgNo = fifo.head;
    msg_hdr_ptr = fifo_ptr + fifo_hdr_size + (msgNo * fifo.msgSize);

    /* check if message ready */
    shm->shmReadFunc(
        shm->shmIoAnchorPtr,
        msg_hdr_ptr, (msg_hdr_size / 4), &msgBuffer);
    if (msgBuffer.ready == 0)
    {
        MCD_DBG_INFO(
            "mcdInternalShmIpcRecv message found ready_flag  0x%X\n",
            msgBuffer.ready);
        return 0; /* not message ready */
    }

    /* read message */
    dataSize = msgBuffer.length;
    if (size != NULL)
    {
        if (*size < dataSize)
            dataSize = *size;
    }
    shm->shmReadFunc(
        shm->shmIoAnchorPtr,
        (msg_hdr_ptr + msg_hdr_size), ((dataSize + 3) / 4), data);
    if (size != NULL)
        *size = dataSize;
    {
        const MCD_IPC_U32* p = data;
        DBG_TRACE((
            "mcdInternalShmIpcRecv message from channel 0x%X size 0x%X data 0x%X 0x%X 0x%X 0x%X \n",
            (MCD_IPC_UINT)chn, (MCD_IPC_UINT)dataSize,
            (MCD_IPC_UINT)p[0], (MCD_IPC_UINT)p[1], (MCD_IPC_UINT)p[2], (MCD_IPC_UINT)p[3]));
    }

    /* move head to the next message */
    msgNo = (msgNo + 1) % fifo.size;
    fifo.head = msgNo;
    shm->shmWriteFunc(shm->shmIoAnchorPtr, (fifo_ptr + fifo_hdr_head_off), 1, &fifo.head);

    /* mark the read message not ready */
    msgBuffer.ready = 0;
    shm->shmWriteFunc(
        shm->shmIoAnchorPtr,
        (msg_hdr_ptr + msg_hdr_ready_off), 1, &(msgBuffer.ready));

    /* check if the next message ready */
    msg_hdr_ptr = fifo_ptr + fifo_hdr_size + (msgNo * fifo.msgSize);
    shm->shmReadFunc(
        shm->shmIoAnchorPtr,
        (msg_hdr_ptr + msg_hdr_ready_off), 1, &(msgBuffer.ready));
    if (msgBuffer.ready == 0)
    {
        /* drop rxReady bit */
        chn_read_ready_off  = IPC_OFFSETOF(IPC_SHM_DATA_STC, rxReady[shm->master]);
        shm->shmReadFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);
        bit = ~ (1 << chn);
        w_u32 &= bit;
        shm->shmWriteFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);
    }

    return 1;
}
/**
* @internal mcdInternalShmIpcRxReady function
* @endinternal
*
* @brief   Check if RX data available in any channel
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int mcdInternalShmIpcRxReady(MCD_IPC_SHM_STC* shm) /* returns bitmask */
{
    MCD_IPC_U32 w_u32;
    MCD_IPC_U32 chn_read_ready_off;

    chn_read_ready_off  = IPC_OFFSETOF(IPC_SHM_DATA_STC, rxReady[shm->master]);
    shm->shmReadFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);
    return w_u32;
}

/**
* @internal mcdInternalShmIpcRxChnReady function
* @endinternal
*
* @brief   Check if RX data available in the channel
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int mcdInternalShmIpcRxChnReady(MCD_IPC_SHM_STC* shm, int chn)
{
    MCD_IPC_U32 w_u32;
    MCD_IPC_U32 chn_read_ready_off;

    chn_read_ready_off  = IPC_OFFSETOF(IPC_SHM_DATA_STC, rxReady[shm->master]);
    shm->shmReadFunc(shm->shmIoAnchorPtr, (shm->shm + chn_read_ready_off), 1, &w_u32);
    return (w_u32 & (1 << chn));
}

/**
* @internal mcdInternalShmIpcRegRead function
* @endinternal
*
* @brief   Read IPC 32bit register
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm                      - SHM control structure
* @param[in] reg                      - Register number. The registers are enumerated
*                                      from the end of SRAM. For example on CM3
* @param[in] reg                      0 will have address 0x1fffc
* @param[in] reg                      1 will have address 0x1fff8
* @param[in] reg                      2 will have address 0x1fff4
*                                       Register value (converted from Little Endian to host byte order)
*/
MCD_IPC_U32 mcdInternalShmIpcRegRead(
    IN  MCD_IPC_SHM_STC* shm,
    IN  int reg
)
{
    MCD_IPC_U32 w_u32;
    MCD_IPC_U32 reg_base_pos = IPC_OFFSETOF(IPC_SHM_DATA_STC, registers);

    if (reg >= MCD_IPC_SHM_NUM_REGS) /* wrong register */
        return 0;
    shm->shmReadFunc(
        shm->shmIoAnchorPtr,
        (shm->shm + reg_base_pos + (reg * sizeof(MCD_IPC_U32))), 1, &w_u32);
    return w_u32;
}

/**
* @internal mcdInternalShmIpcRegWrite function
* @endinternal
*
* @brief   Write IPC 32bit register to SHM
*         Convert from host byte order to Little Endian.
*
* @note   APPLICABLE DEVICES:      Any
* @note   NOT APPLICABLE DEVICES:  None
*
* @param[in] shm                      - SHM control structure
* @param[in] reg                      - Register number. The registers are enumerated
*                                      from the end of SRAM. For example on CM3
* @param[in] reg                      0 will have address 0x1fffc
* @param[in] reg                      1 will have address 0x1fff8
* @param[in] reg                      2 will have address 0x1fff4
* @param[in] data                     -  to write (host byte order)
*
* @retval 0                        - on success
*                                       -1       - on failure
*/
int mcdInternalShmIpcRegWrite(
    IN  MCD_IPC_SHM_STC* shm,
    IN  int reg,
    IN  MCD_IPC_U32 data
)
{
    MCD_IPC_U32 w_u32;
    MCD_IPC_U32 reg_base_pos = IPC_OFFSETOF(IPC_SHM_DATA_STC, registers);
    MCD_IPC_STATUS   rc;

    if (reg >= MCD_IPC_SHM_NUM_REGS) /* wrong register */
    {
        MCD_DBG_ERROR("mcdInternalShmIpcRegWrite: register %d out of range\n",reg);
        return -1;
    }
    w_u32 = data;
    rc = shm->shmWriteFunc(
        shm->shmIoAnchorPtr,
        (shm->shm + reg_base_pos + (reg * sizeof(MCD_IPC_U32))), 1, &w_u32);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("shmWriteFunc failed at %s:%u\n",__FUNCTION__,__LINE__);
        return -1;
    }

    return 0;
}

/*#define SHM_DEBUG_TEST*/
#ifdef SHM_DEBUG_TEST

#define SHM_DEBUG_TEST_MEMORY_SIZE 0x400
struct
{
    unsigned char memo[SHM_DEBUG_TEST_MEMORY_SIZE];
} mcdInternalShmIpcTestMemory;

MCD_IPC_PTR mcdInternalShmIpcTestMemoryOffset = 0;

MCD_IPC_STATUS mcdInternalShmIpcTestWrite(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, const void* dataPtr)
{
    MCD_IPC_U32 wordIndex;
    for (wordIndex = 0; (wordIndex < numOfWords); wordIndex++)
    {
        ((MCD_IPC_U32*)&(((char*)anchorPtr)[address]))[wordIndex] =
            ((MCD_IPC_U32*)dataPtr)[wordIndex];
    }
    return 0;
}
MCD_IPC_STATUS mcdInternalShmIpcTestRead(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, void* dataPtr)
{
    MCD_IPC_U32 wordIndex;
    for (wordIndex = 0; (wordIndex < numOfWords); wordIndex++)
    {
        ((MCD_IPC_U32*)dataPtr)[wordIndex] =
            ((MCD_IPC_U32*)&(((char*)anchorPtr)[address]))[wordIndex];
    }
    return 0;
}

MCD_IPC_SHM_STC mcdInternalShmIpcTestMasterShm;
MCD_IPC_SHM_STC mcdInternalShmIpcTestSlaveShm;

int mcdInternalShmIpcTestInit()
{
    mcdInternalShmIpcInit(
        &mcdInternalShmIpcTestMasterShm,
        &(mcdInternalShmIpcTestMemory.memo[0]),
        mcdInternalShmIpcTestWrite,
        mcdInternalShmIpcTestRead,
        (MCD_IPC_PTR)mcdInternalShmIpcTestMemoryOffset,
        SHM_DEBUG_TEST_MEMORY_SIZE, 1 /*master*/);
    mcdInternalShmIpcInit(
        &mcdInternalShmIpcTestSlaveShm,
        &(mcdInternalShmIpcTestMemory.memo[0]),
        mcdInternalShmIpcTestWrite,
        mcdInternalShmIpcTestRead,
        (MCD_IPC_PTR)mcdInternalShmIpcTestMemoryOffset,
        SHM_DEBUG_TEST_MEMORY_SIZE, 0 /*master*/);
    return 0;
}

int mcdInternalShmIpcTestConfigChannel
(
    IN  int             chn,
    IN  int             maxrx,
    IN  int             rxsize,
    IN  int             maxtx,
    IN  int             txsize
)
{
    return mcdInternalShmIpcConfigChannel(
        &mcdInternalShmIpcTestMasterShm,
        chn, maxrx, rxsize, maxtx, txsize);
}

int mcdInternalShmIpcTestSendNumber
(
    IN  int             master,
    IN  int             chn,
    IN  int             msgNumber
)
{
    MCD_IPC_SHM_STC *shm =
        (master
            ? &mcdInternalShmIpcTestMasterShm
            : &mcdInternalShmIpcTestSlaveShm);
    return mcdInternalShmIpcSend(
        shm, chn, &msgNumber, sizeof(msgNumber));
}

int mcdInternalShmIpcTestReceiveNumber
(
    IN  int             master,
    IN  int             chn
)
{
    MCD_IPC_SHM_STC *shm =
        (master
            ? &mcdInternalShmIpcTestMasterShm
            : &mcdInternalShmIpcTestSlaveShm);
    int msgNumber = 0;
    int msgSize = sizeof(msgNumber);
    int rc = mcdInternalShmIpcRecv(
        shm, chn, &msgNumber, &msgSize);
    if (rc < 0) return rc;
    if (rc == 0) return -10;
    if (msgSize != sizeof(msgNumber)) return -20;
    return msgNumber;
}

int mcdInternalShmIpcTest()
{
    int i, snd, rcv, rc;
    mcdInternalShmIpcTestInit();
    rc = mcdInternalShmIpcTestConfigChannel(0, 0, 0, 4, 8); /*tx*/
    if (rc != 0) return (rc - 1000);
    rc = mcdInternalShmIpcTestConfigChannel(1, 4, 8, 0, 0); /*rx*/
    if (rc != 0) return (rc - 1100);
    /* chech that nothing to receive, send and immeditely receive the sent */
    for (i = 0; (i < 16); i++)
    {
        snd = (10000 + i);
        rcv = mcdInternalShmIpcTestReceiveNumber(
            0 /*master*/, 0 /*chn*/);
        if (rcv != -10 /*no message*/) return (rcv - 1200);
        rc = mcdInternalShmIpcTestSendNumber(
            1 /*master*/, 0 /*chn*/, snd);
        if (rc != 0) return (rc - 1300);
        rcv = mcdInternalShmIpcTestReceiveNumber(
            0 /*master*/, 0 /*chn*/);
        if (rcv != snd) return (rcv - 1400);
        snd = (20000 + i);
        rcv = mcdInternalShmIpcTestReceiveNumber(
            1 /*master*/, 1 /*chn*/);
        if (rcv != -10 /*no message*/) return (rcv - 1500);
        rc = mcdInternalShmIpcTestSendNumber(
            0 /*master*/, 1 /*chn*/, snd);
        if (rc != 0) return (rc - 1600);
        rcv = mcdInternalShmIpcTestReceiveNumber(
            1 /*master*/, 1 /*chn*/);
        if (rcv != snd) return (rcv - 1700);
    }
    return 0;
}
#endif /*SHM_DEBUG_TEST*/



