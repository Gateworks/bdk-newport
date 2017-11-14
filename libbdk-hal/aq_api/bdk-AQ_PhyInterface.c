/* AQ_PhyInterface.h */

/***********************************************************************
*                 Copyright Aquantia Corporation
*                             Freeware
*
* Description:
*
*   Declares the base PHY register read and write functions that are
*   called by the API functions. The platform integrator must provide
*   the implementation of these routines.
*
***********************************************************************/


/*! \file
 * Declares the base PHY register read and write functions that are
 * called by the API functions. The platform integrator must provide
 * the implementation of these routines. */


#include <bdk.h>
#include "AQ_API.h"
#include "AQ_User.h"


#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************
                        MDIO Access Functions
*******************************************************************/

/*! \defgroup mdioAccessFunctions MDIO Access Functions
The MDIO access functions are required by the API to access the register space
of each Aquantia PHY deployed in a system. The body of these functions needs to
be written by the system designer, as the method of accessing the PHY will
be unique to the target system. They are designed to be generic read and
write access functions, as the MDIO addressing scheme relies on each
MMD to maintain a 16 bit address pointer that determines the register where
the next read or write is coming from. Consequently, various levels of
optimization of the MDIO interface are possible: from re-writing the MMD
address pointer on every transaction, to storing shadow copies of the MMD
address pointers and only updating the MMD address pointer as necessary.
Thus these functions leave the MDIO optimization to the system engineer.
 */
/*@{*/


/*! Provides generic synchronous PHY register write functionality. It is the
 * responsibility of the system designer to provide the specific MDIO address
 * pointer updates, etc. in order to accomplish this write operation.
 * It will be assumed that the write has been completed by the time this
 * function returns.*/
void AQ_API_MDIO_Write
(
    /*! Uniquely identifies the port within the system. AQ_Port must be
     * defined to a whatever data type is suitable for the platform.*/
  AQ_Port PHY_ID,
    /*! The address of the MMD within the target PHY. */
  unsigned int MMD,
    /*! The 16-bit address of the PHY register being written. */
  unsigned int address,
    /*! The 16-bits of data to write to the specified PHY register. */
  unsigned int data
)
{
#if defined(BDK_TRACE_ENABLE_AQR)
    int rc = bdk_mdio_45_write(PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
                      MMD, address, data);
    BDK_TRACE(AQR, "AQR@n%d.%d.%02d Write mmd 0x%02x reg 0x%04x data %04x rc %d\n",
              PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
              MMD, address, data, rc);
#else
    bdk_mdio_45_write(PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
                      MMD, address, data);
#endif
}

/*! Provides generic synchronous PHY register read functionality. It is the
 * responsibility of the system designer to provide the specific MDIO address
 * pointer updates, etc. in order to accomplish this read operation.*/
unsigned int AQ_API_MDIO_Read
(
    /*! Uniquely identifies the port within the system. AQ_Port must be
     * defined to a whatever data type is suitable for the platform.*/
  AQ_Port PHY_ID,
    /*! The address of the MMD within the target PHY. */
  unsigned int MMD,
    /*! The 16-bit address of the PHY register being read. */
  unsigned int address
)
{
#if defined(BDK_TRACE_ENABLE_AQR)
    unsigned int data = bdk_mdio_45_read(PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
                                         MMD, address);
    BDK_TRACE(AQR, "AQR@n%d.%d.%02d Read mmd 0x%02x reg 0x%04x data %04x\n",
              PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
              MMD, address, data);
    return data;
#else
    return (unsigned int) bdk_mdio_45_read(PHY_ID.node, PHY_ID.mdio_bus, PHY_ID.mdio_phy,
                            MMD, address);
#endif
}

#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE

/*! Provides generic asynchronous/buffered PHY register write functionality.
 * It is the responsibility of the system designer to provide the specific
 * MDIO address pointer updates, etc. in order to accomplish this write
 * operation.  The write need not necessarily have been completed by the time
 * this function returns.  All register reads and writes to a particular PHY_ID
 * that are requested by calling AQ_API_MDIO_BlockWrite or AQ_API_MDIO_BlockRead
 * MUST be performed in the order that the calls are made. */
void AQ_API_MDIO_BlockWrite
(
    /*! Uniquely identifies the port within the system. AQ_Port must be
     * defined to a whatever data type is suitable for the platform.*/
  AQ_Port PHY_ID,
    /*! The address of the MMD within the target PHY. */
  unsigned int MMD,
    /*! The 16-bit address of the PHY register being written. */
  unsigned int address,
    /*! The 16-bits of data to write to the specified PHY register. */
  unsigned int data
)
{
#	error " AQ_API_MDIO_BlockWrite has no body"
}

/*! Provides generic asynchronous/buffered PHY register read functionality.
 * It is the responsibility of the system designer to provide the specific
 * MDIO address pointer updates, etc. in order to accomplish this read
 * operation.  All register reads and writes to a particular PHY_ID that
 * are requested by calling AQ_API_MDIO_BlockWrite or AQ_API_MDIO_BlockRead
 * MUST be performed in the order that the calls are made. The register value
 * may subsequently be fetched by calling AQ_API_MDIO_BlockOperationExecute.*/
void AQ_API_MDIO_BlockRead
(
    /*! Uniquely identifies the port within the system. AQ_Port must be
     * defined to a whatever data type is suitable for the platform.*/
  AQ_Port PHY_ID,
    /*! The address of the MMD within the target PHY. */
  unsigned int MMD,
    /*! The 16-bit address of the PHY register being read. */
  unsigned int address
)
{
#	error " AQ_API_MDIO_BlockRead has no body"
}

/* Retrieve the results of all PHY register reads to PHY_ID previously
 * requested via calls to AQ_API_MDIO_BlockRead.  The read and write
 * operations previously performed by calls to AQ_API_MDIO_BlockRead and
 * AQ_API_MDIO_BlockRead must have all been completed by the time this
 * function returns, in the order that the calls were performed. The
 * return value is an array representing the fetched results of all
 * pending calls to AQ_API_MDIO_BlockRead, in the order that the calls
 * were performed.  Callers should track the number of pending block
 * reads to determine the size of the returned array. */
unsigned int * AQ_API_MDIO_BlockOperationExecute
(
    /*! Uniquely identifies the port within the system. AQ_Port must be
     * defined to a whatever data type is suitable for the platform.*/
  AQ_Port PHY_ID
);

/* Returns the maximum number of asynchronous/buffered PHY register
 * read/write operations.  Callers will call AQ_API_MDIO_BlockOperationExecute
 * before issuing additional calls to AQ_API_MDIO_BlockWrite or
 * AQ_API_MDIO_BlockRead to avoid a buffer overflow. */
unsigned int AQ_API_MDIO_MaxBlockOperations
(
)
{
#	error " AQ_API_MDIO_MaxBlockOperations has no body"
}

#endif

/*@}*/


