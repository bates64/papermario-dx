#include "omo_04.h"

EntryList N(Entrances) = {
    [omo_04_ENTRY_0]    { -965.0,    0.0,    0.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
