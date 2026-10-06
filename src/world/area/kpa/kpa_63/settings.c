#include "kpa_63.h"

EntryList Entrances = {
    [kpa_63_ENTRY_0]    {  160.0,    0.0,  240.0,    0.0 },
    [kpa_63_ENTRY_1]    {  -40.0,    0.0,  225.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_63 },
    .songVariation = 1,
    .sfxReverb = 2,
};
