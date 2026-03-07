#include "omo_15.h"

EntryList N(Entrances) = {
    [omo_15_ENTRY_0]    { -290.0,    0.0,    0.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_15 },
    .songVariation = 1,
    .sfxReverb = 2,
};
