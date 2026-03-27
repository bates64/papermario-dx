#include "jan_22.h"

EntryList N(Entrances) = {
    [jan_22_ENTRY_0]    { -480.0,    0.0,    0.0,   90.0 },
    [jan_22_ENTRY_1]    { -190.0,    0.0, -130.0,  180.0 },
    [jan_22_ENTRY_2]    { 1200.0,   90.0,    0.0,  270.0 },
    [jan_22_ENTRY_3]    { 1200.0,   90.0,    0.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_22 },
    .songVariation = 1,
    .sfxReverb = 1,
};
