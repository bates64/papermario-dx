#include "jan_12.h"

EntryList N(Entrances) = {
    [jan_12_ENTRY_0]    { -300.0,    0.0,  120.0,    0.0 },
    [jan_12_ENTRY_1]    {  250.0,    0.0, -120.0,  180.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_12 },
    .songVariation = 1,
    .sfxReverb = 1,
};
