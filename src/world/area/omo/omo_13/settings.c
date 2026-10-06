#include "omo_13.h"

EntryList Entrances = {
    [omo_13_ENTRY_0]    { -480.0,    0.0,    0.0,   90.0 },
    [omo_13_ENTRY_1]    {  565.0,    0.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_13 },
    .songVariation = 1,
    .sfxReverb = 2,
};
