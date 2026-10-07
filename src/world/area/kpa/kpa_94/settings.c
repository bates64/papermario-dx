#include "kpa_94.h"

EntryList Entrances = {
    [kpa_94_ENTRY_0]    { -270.0, -240.0,  100.0,   90.0 },
    [kpa_94_ENTRY_1]    {  470.0,    0.0,  100.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_94 },
    .songVariation = 1,
    .sfxReverb = 2,
};
