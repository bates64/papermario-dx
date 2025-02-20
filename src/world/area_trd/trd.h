#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AF_TRD01_RaiseStairs        = AreaFlag(1),
    AF_TRD02_LowerStairs        = AreaFlag(2),
    AF_TRD04_LowerStairs        = AreaFlag(4),
    AF_TRD_MetPrisoner1         = AreaFlag(6),
    AF_TRD_MetPrisoner2         = AreaFlag(7),
    AF_TRD_MetPrisoner3         = AreaFlag(8),
    AF_TRD_MetPrisoner4         = AreaFlag(9),
    AF_TRD08_FireBar1_Coins     = AreaFlag(11),
    AF_TRD08_FireBar2_Coins     = AreaFlag(12),
    AF_TRD_FakeBowserRevealed   = AreaFlag(13),
};

extern MapSettings trd_00_settings;
extern MapSettings trd_01_settings;
extern MapSettings trd_02_settings;
extern MapSettings trd_03_settings;
extern MapSettings trd_04_settings;
extern MapSettings trd_05_settings;
extern MapSettings trd_06_settings;
extern MapSettings trd_07_settings;
extern MapSettings trd_08_settings;
extern MapSettings trd_09_settings;
extern MapSettings trd_10_settings;
