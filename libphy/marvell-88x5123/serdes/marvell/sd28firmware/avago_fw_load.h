#ifndef AVAGO_FW_LOAD__H_
#define AVAGO_FW_LOAD_H_

#ifdef FW_DOWNLOAD_FROM_SERVER
const char *serdesFileName = "/usr/bin/serdes.0x2464_0245.rom";
const char *sbusMasterFileName = "/usr/bin/sbus_master.0x1015_0001.rom";
const char *serdesSwapFileName = NULL;
#else

#include "serdes.0x2464_0245.h"
#include "sbus_master.0x101A_0001.h"

#define AVAGO_FW_SWAP_IMAGE_EXIST
#ifdef AVAGO_FW_SWAP_IMAGE_EXIST
#include "serdes.0x2464_0245swap.h"
#endif /*AVAGO_FW_SWAP_IMAGE_EXIST*/

#endif /*FW_DOWNLOAD_FROM_SERVER*/
#endif /*AVAGO_FW_Data_H_H_*/


