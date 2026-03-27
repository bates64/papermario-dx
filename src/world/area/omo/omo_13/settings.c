#include "omo_13.h"

EntryList N(Entrances) = {
    [omo_13_ENTRY_0]    { -480.0,    0.0,    0.0,   90.0 },
    [omo_13_ENTRY_1]    {  565.0,    0.0,    0.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_13 },
    .songVariation = 1,
    .sfxReverb = 2,
};
