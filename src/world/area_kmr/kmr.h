#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AB_KMR_0            = AreaByte(0),
    AB_KMR_Unused_1     = AreaByte(1),
    AB_KMR_2            = AreaByte(2),
};

enum {
    AF_KMR_04       = AreaFlag(4),
    AF_KMR_06       = AreaFlag(6),
    AF_KMR_07       = AreaFlag(7),
    AF_KMR_08       = AreaFlag(8),
    AF_KMR_09       = AreaFlag(9),
    AF_KMR_0B       = AreaFlag(11),
    AF_KMR_0C       = AreaFlag(12),
    AF_KMR_0D       = AreaFlag(13),
};

extern MapSettings kmr_00_settings;
extern MapSettings kmr_02_settings;
extern MapSettings kmr_03_settings;
extern MapSettings kmr_04_settings;
extern MapSettings kmr_05_settings;
extern MapSettings kmr_06_settings;
extern MapSettings kmr_07_settings;
extern MapSettings kmr_09_settings;
extern MapSettings kmr_10_settings;
extern MapSettings kmr_11_settings;
extern MapSettings kmr_12_settings;
extern MapSettings kmr_20_settings;
extern MapSettings kmr_21_settings;
extern MapSettings kmr_22_settings;
extern MapSettings kmr_23_settings;
extern MapSettings kmr_24_settings;
extern MapSettings kmr_30_settings;

s32 kmr_21_map_init(void);
s32 kmr_22_map_init(void);
s32 kmr_23_map_init(void);
s32 kmr_24_map_init(void);
