#include "kzn_22.h"

EntryList Entrances = {
    [kzn_22_ENTRY_0]    { -390.0,    0.0,  210.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kzn_22 },
    .songVariation = 1,
    .sfxReverb = 2,
};
