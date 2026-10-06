#include "kkj_24.h"

EntryList Entrances = {
    [kkj_24_ENTRY_0]    {  145.0,    0.0,  -10.0,  270.0 },
    [kkj_24_ENTRY_1]    {  145.0,  420.0,  -20.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_24 },
    .songVariation = 1,
    .sfxReverb = 2,
};
