#include "kpa_121.h"

EntryList Entrances = {
    [kpa_121_ENTRY_0]   { -373.0, -240.0,  100.0,   90.0 },
    [kpa_121_ENTRY_1]   {  465.0,    0.0,   95.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_121 },
    .songVariation = 1,
    .sfxReverb = 2,
};
