#include "kpa_134.h"

EntryList Entrances = {
    [kpa_134_ENTRY_0]   { -370.0,    0.0,  115.0,   90.0 },
    [kpa_134_ENTRY_1]   {  730.0,    0.0,  115.0,  270.0 },
    [kpa_134_ENTRY_2]   { -370.0,  100.0,  128.0,   90.0 },
    [kpa_134_ENTRY_3]   { -365.0,  240.0,  -22.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_134 },
    .songVariation = 1,
    .sfxReverb = 3,
};
