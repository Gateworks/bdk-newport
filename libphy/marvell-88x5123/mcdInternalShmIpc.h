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
* @file mcdInternalShmIpc.h
*
* @brief Low-level IPC implementation
*
* @version   1
********************************************************************************
*/
#ifndef __mcdInternalShmIpc_h__
#define __mcdInternalShmIpc_h__

/* define CM3 IPC Types  */

/* MCD_IPC_U32 - must be 32 bits */
#define  MCD_IPC_U32 MCD_U32
/* MCD_IPC_PTR - must be 32 bits to
   hold pointers for 32 Bits CPUs */
#define  MCD_IPC_PTR MCD_U32

/* common types */
#define  MCD_IPC_UINT       MCD_UINT
#define  MCD_IPC_STATUS     MCD_U32

/*
 * CONSTRAINTS:
 * 1. Only one thread on master or slave side can access one channel
 * 2. Only one thread can configure channels on master side
 *
 * 3. a successfull mcdInternalShmIpcGetTxBuffer(chn) must follow mcdInternalShmIpcSend(chn)
 *    without trying to access this channed from another thread
 *
 * 4. a successfull mcdInternalShmIpcRecv(chn) should follow mcdInternalShmIpcReleaseRxBuffer()
 *    without trying to access this channed from another thread
 */

#define MCD_IPC_SHM_MAGIC          0x17354628
#define MCD_IPC_SHM_CHANNELS       6
#define MCD_IPC_SHM_NUM_REGS       32
#define MCD_IPC_SHM_RESVD_MAGIC    0x5a5b5c5d

/* functions for access to shared memory - shared memory not mapped to CPU address space */
typedef MCD_IPC_STATUS (*MCD_IPC_SHM_WRITE_FUNC)(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, const void* dataPtr);
typedef MCD_IPC_STATUS (*MCD_IPC_SHM_READ_FUNC)(
     void* anchorPtr, MCD_IPC_PTR address, MCD_IPC_U32 numOfWords, void* dataPtr);

/*
 * typedef: struct MCD_IPC_SHM_STC
 *
 * Description: A control structure for low-level IPC
 *
 * Fields:
 *
 *   shmIoAnchorPtr - pointer to anchor for Write and Read functions
 *   shmWriteFunc   - function to write data to shared memory
 *   shmReadFunc    - function to read data from shared memory
 *   shm            - virtual address IPC shared memory block
 *   shmLen         - length of IPC shared memory block
 *   master         - role (master/slave).
 *                    Each channel is a pair of FIFOs
 *                    For master the FIFOs are Rx,Tx
 *                    For slave - Tx, Rx
 *
 * Comments:
 *
 */
typedef struct MCD_IPC_SHM_STCT {
    void*                   shmIoAnchorPtr;
    MCD_IPC_SHM_WRITE_FUNC  shmWriteFunc;
    MCD_IPC_SHM_READ_FUNC   shmReadFunc;
    MCD_IPC_PTR             shm;
    MCD_IPC_U32             shmLen;
    int                     master;
} MCD_IPC_SHM_STC;

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
);

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
*                                      txsize      - max message size in Tx FIFO
*
* @retval 0                        - on success
*                                       -1     - already configured\
*                                       -2     - can't configure (no memory left)
*                                       -3     - bad parameter
*/
int mcdInternalShmIpcConfigChannel(
    IN  MCD_IPC_SHM_STC *shm,
    IN  int             chn,
    IN  int             maxrx,
    IN  int             rxsize,
    IN  int             maxtx,
    IN  int             txsixe
);

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
);

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
);

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
int mcdInternalShmIpcRxReady(MCD_IPC_SHM_STC* shm); /* returns bitmask */

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
int mcdInternalShmIpcRxChnReady(MCD_IPC_SHM_STC* shm, int chn);

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
);

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
*                                      reg         - Register number. The registers are enumerated
*                                      from the end of SRAM. For example on CM3
*                                      register 0 will have address 0x1fffc
*                                      register 1 will have address 0x1fff8
*                                      register 2 will have address 0x1fff4
* @param[in] data                     -  to write (host byte order)
*
* @retval 0                        - on success
*                                       -1       - on failure
*/
int mcdInternalShmIpcRegWrite(
    IN  MCD_IPC_SHM_STC* shm, int reg,
    IN  MCD_IPC_U32 data
);

#endif /* __mcdInternalShmIpc_h__ */


