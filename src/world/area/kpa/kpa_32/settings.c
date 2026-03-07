#include "kpa_32.h"

EntryList N(Entrances) = {
    [kpa_32_ENTRY_0]    { -575.0,  -50.0,   -5.0,   90.0 },
    [kpa_32_ENTRY_1]    {  545.0,  -50.0,   -5.0,  270.0 },
    [kpa_32_ENTRY_2]    {  535.0,  140.0,    0.0,  270.0 },
    [kpa_32_ENTRY_3]    { -535.0,  140.0,    0.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kpa_32 },
    .songVariation = 1,
    .sfxReverb = 3,
};
