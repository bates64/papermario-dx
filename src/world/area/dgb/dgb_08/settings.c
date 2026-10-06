#include "dgb_08.h"

EntryList Entrances = {
    [dgb_08_ENTRY_0]    { -575.0,    0.0,  180.0,   90.0 },
    [dgb_08_ENTRY_1]    { -575.0,  210.0,  180.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
