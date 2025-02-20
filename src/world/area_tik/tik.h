#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AF_TIK_02       = AreaFlag(2),
    AF_TIK_03       = AreaFlag(3),
    AF_TIK_04       = AreaFlag(4),
    AF_TIK_05       = AreaFlag(5),
};

extern MapSettings tik_01_settings;
extern MapSettings tik_02_settings;
extern MapSettings tik_03_settings;
extern MapSettings tik_04_settings;
extern MapSettings tik_05_settings;
extern MapSettings tik_06_settings;
extern MapSettings tik_07_settings;
extern MapSettings tik_08_settings;
extern MapSettings tik_09_settings;
extern MapSettings tik_10_settings;
extern MapSettings tik_12_settings;
extern MapSettings tik_14_settings;
extern MapSettings tik_15_settings;
extern MapSettings tik_17_settings;
extern MapSettings tik_18_settings;
extern MapSettings tik_19_settings;
extern MapSettings tik_20_settings;
extern MapSettings tik_21_settings;
extern MapSettings tik_22_settings;
extern MapSettings tik_23_settings;
extern MapSettings tik_24_settings;
extern MapSettings tik_25_settings;

s32 tik_24_map_init(void);
