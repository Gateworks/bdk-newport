#include <bdk.h>

#include <stdint.h>

#include "AQ_API.h"
#include "AQ_User.h"
#include "AQ_ReturnCodes.h"



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
)
{
    bdk_wait_usec( 1000U * milliseconds);
}

