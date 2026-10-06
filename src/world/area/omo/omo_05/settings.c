#include "omo_05.h"

EntryList Entrances = {
    [omo_05_ENTRY_0]    {  590.0,    0.0,  135.0,  270.0 },
    [omo_05_ENTRY_1]    {  590.0,   10.0, -140.0,  270.0 },
    [omo_05_ENTRY_2]    { -600.0,   10.0,    0.0,   90.0 },
    [omo_05_ENTRY_3]    {  600.0,   10.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
