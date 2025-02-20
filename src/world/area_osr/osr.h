#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AF_OSR_01       = AreaFlag(1),
};

extern MapSettings osr_00_settings;
extern MapSettings osr_01_settings;
extern MapSettings osr_02_settings;
extern MapSettings osr_03_settings;
extern MapSettings osr_04_settings;

s32 osr_01_map_init(void);
s32 osr_02_map_init(void);
s32 osr_03_map_init(void);
s32 osr_04_map_init(void);
