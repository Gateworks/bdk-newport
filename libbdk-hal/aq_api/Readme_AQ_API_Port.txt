2016-11-11
This file describes the port of AQ_API reference code from Aquantia.

Directory structure:

aq_api
|---Readme_AQ_API_Port.txt   This file
|---bdk-aqr-support.[ch]     Interface between Aquantia provided functions and bdk
|                            Implements both cavuim.aqr107 in LUA as well
|---bdk-AQ_PlatformRoutines.c Platform specific routines adapted to bdk per
|                             Aquantia API spec.
|---bdk-AQ_PhyInterface.c     Platform specific register read and write
|                             routines adapted to bdk Aquantia API Spec.
|---include
    |---AQ_User.h             Adapted to bdk per Aquantia API Spec
    |                         I note that I set low debug verbosity because flash
    |                         compare takes forever with it on mismatch.
    |---AQ_PlatformRoutines.h Adapted to bdk per Aquantia API Spec
    |---AQ_PhyInterface.h     Adapted to bdk per Aquantia API Spec
      All other files in that directory and subdirectories belong to
      reference code
|---src          All files in this subtree are Aquantia reference code.
                 There are some compile warnings, which I have purposely
                 did not touch.
