#include "omo_02.h"

EntryList N(Entrances) = {
    [omo_02_ENTRY_0]    { -970.0,    0.0,    0.0,   90.0 },
    [omo_02_ENTRY_1]    {  360.0,    0.0,   20.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
