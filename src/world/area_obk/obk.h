#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AF_OBK01_CabinetMoved           = AreaFlag(1),
    AF_OBK01_IsPlayerNearPortrait   = AreaFlag(3),
    AF_OBK01_WasPlayerNearPortrait  = AreaFlag(4),
    AF_OBK03_HitFirstSwitch         = AreaFlag(5),
    AF_OBK03_HitSecondSwitch        = AreaFlag(6),
    AF_OBK03_HitThirdSwitch         = AreaFlag(7),
    AF_OBK08_KeepAwayStarted        = AreaFlag(8),
};

extern MapSettings obk_01_settings;
extern MapSettings obk_02_settings;
extern MapSettings obk_03_settings;
extern MapSettings obk_04_settings;
extern MapSettings obk_05_settings;
extern MapSettings obk_06_settings;
extern MapSettings obk_07_settings;
extern MapSettings obk_08_settings;
extern MapSettings obk_09_settings;
