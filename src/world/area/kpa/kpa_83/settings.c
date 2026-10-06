#include "kpa_83.h"

EntryList Entrances = {
    [kpa_83_ENTRY_0]    { -210.0,    0.0,  150.0,   90.0 },
    [kpa_83_ENTRY_1]    {  150.0,    0.0,  150.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_83 },
    .songVariation = 1,
    .sfxReverb = 2,
};
