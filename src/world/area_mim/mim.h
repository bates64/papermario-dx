#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AB_MIM_1            = AreaByte(1),
    AB_MIM_2            = AreaByte(2),
};

enum {
    AF_MIM_01                       = AreaFlag(1),
    AF_MIM03_Oaklie_DialogueToggle  = AreaFlag(2),
    AF_MIM04_Bubulb_DialogueToggle  = AreaFlag(4),
    AF_MIM12_BackgroundLitUp        = AreaFlag(3),
};

extern MapSettings mim_01_settings;
extern MapSettings mim_02_settings;
extern MapSettings mim_03_settings;
extern MapSettings mim_04_settings;
extern MapSettings mim_05_settings;
extern MapSettings mim_06_settings;
extern MapSettings mim_07_settings;
extern MapSettings mim_08_settings;
extern MapSettings mim_09_settings;
extern MapSettings mim_10_settings;
extern MapSettings mim_11_settings;
extern MapSettings mim_12_settings;
