#include "jan_15.h"

EntryList N(Entrances) = {
    [jan_15_ENTRY_0]    { -300.0,    0.0,  120.0,    0.0 },
    [jan_15_ENTRY_1]    {  380.0,    0.0,    0.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_15 },
    .songVariation = 1,
    .sfxReverb = 1,
};
