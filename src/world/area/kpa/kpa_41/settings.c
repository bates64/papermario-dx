#include "kpa_41.h"

EntryList Entrances = {
    [kpa_41_ENTRY_0]    { -340.0,    0.0,  -70.0,   90.0 },
    [kpa_41_ENTRY_1]    {  340.0,    0.0,  -70.0,  270.0 },
    [kpa_41_ENTRY_2]    {  340.0,  119.0, -230.0,  270.0 },
    [kpa_41_ENTRY_3]    { -340.0,  119.0, -230.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_41 },
    .songVariation = 1,
    .sfxReverb = 2,
};
