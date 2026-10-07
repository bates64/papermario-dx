#include "kpa_10.h"

EntryList Entrances = {
    [kpa_10_ENTRY_0]    {   25.0,  100.0, -140.0,   90.0 },
    [kpa_10_ENTRY_1]    { 1402.0,   30.0, -1082.0,  180.0 },
    [kpa_10_ENTRY_2]    { 1378.0,   30.0, -724.0,   90.0 },
    [kpa_10_ENTRY_3]    {   15.0,  -20.0,  -20.0,   90.0 },
    [kpa_10_ENTRY_4]    { 1529.0,  -20.0, -1082.0,  180.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_10 },
    .songVariation = 1,
    .sfxReverb = 3,
};
