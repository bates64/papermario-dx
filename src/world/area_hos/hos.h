#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AB_HOS_StatcAmt_Eldstar     = AreaByte(0),
    AB_HOS_StatcAmt_Mamar       = AreaByte(1),
    AB_HOS_StatcAmt_Skolar      = AreaByte(2),
    AB_HOS_StatcAmt_Muskular    = AreaByte(3),
    AB_HOS_StatcAmt_Misstar     = AreaByte(4),
    AB_HOS_StatcAmt_Klevar      = AreaByte(5),
    AB_HOS_StatcAmt_Kalmar      = AreaByte(6),
};

enum {
    AF_HOS06_BadgeHints         = AreaFlag(3),
    AF_HOS06_SuperBlocksHints   = AreaFlag(100),
    AF_HOS06_StarPieceHints     = AreaFlag(116),
    AF_HOS_B4                   = AreaFlag(180),
    AF_HOS_B5                   = AreaFlag(181),
    AF_HOS06_SpokeWithMerluvlee = AreaFlag(182),
};

extern MapSettings hos_00_settings;
extern MapSettings hos_01_settings;
extern MapSettings hos_02_settings;
extern MapSettings hos_03_settings;
extern MapSettings hos_04_settings;
extern MapSettings hos_05_settings;
extern MapSettings hos_06_settings;
extern MapSettings hos_10_settings;
extern MapSettings hos_20_settings;

s32 hos_00_map_init(void);
s32 hos_10_map_init(void);
