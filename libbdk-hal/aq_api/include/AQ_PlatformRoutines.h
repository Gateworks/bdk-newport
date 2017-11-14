/*AQ_PlatformRoutines.h*/

/************************************************************************************
*                    Copyright Aquantia Corporation
*                              Freeware
*
* Description:
*
*   Declares the platform interface functions that will be called by AQ_API 
*   functions.  The platform integrator must provide the implementation of 
*   these functions.
*
************************************************************************************/

/*! \file 
 * Declares the platform interface functions that will be called by AQ_API 
 * functions.  The platform integrator must provide the implementation of 
 * these functions. */


#ifndef AQ_PHY_PLATFORMROUTINES_TOKEN
#define AQ_PHY_PLATFORMROUTINES_TOKEN

#include <stdint.h>

#include "AQ_API.h"
#include "AQ_User.h"
#include "AQ_ReturnCodes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************
                         Time Delay
*******************************************************************/

/*! \defgroup delay Time Delay
  @{
*/

/*! Returns after at least milliseconds have elapsed.  This must be implemented
 * in a platform-approriate way. AQ_API functions will call this function to 
 * block for the specified period of time. If necessary, PHY register reads
 * may be performed on port to busy-wait. */
void AQ_API_Wait
(
  uint32_t milliseconds,     /*!< The delay in milliseconds */
  AQ_API_Port* port          /*!< The PHY to use if delay reads are necessary*/
);

/*@}*/


#ifdef __cplusplus
}
#endif

#endif
