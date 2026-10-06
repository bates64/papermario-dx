#include "kpa_09.h"

EntryList Entrances = {
    [kpa_09_ENTRY_0]    { -483.0,  100.0,  -17.0,   90.0 },
    [kpa_09_ENTRY_1]    {  202.0,    0.0,  -16.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
