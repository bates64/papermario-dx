#include "kpa_33.h"

EntryList Entrances = {
    [kpa_33_ENTRY_0]    { -547.0,  -50.0,   -5.0,   90.0 },
    [kpa_33_ENTRY_1]    {  547.0,  -50.0,   -5.0,  270.0 },
    [kpa_33_ENTRY_2]    {  550.0,  140.0,    0.0,  270.0 },
    [kpa_33_ENTRY_3]    { -550.0,  140.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kpa_33 },
    .songVariation = 1,
    .sfxReverb = 3,
};
