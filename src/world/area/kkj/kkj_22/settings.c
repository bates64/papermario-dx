#include "kkj_22.h"

EntryList N(Entrances) = {
    [kkj_22_ENTRY_0]    { -225.0,    0.0,  -45.0,   90.0 },
    [kkj_22_ENTRY_1]    { -395.0,  300.0, -115.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_22 },
    .songVariation = 1,
    .sfxReverb = 2,
};
