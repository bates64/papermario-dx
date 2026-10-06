#include "dgb_18.h"

EntryList Entrances = {
    [dgb_18_ENTRY_0]    { -120.0,    0.0,  180.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_18 },
    .songVariation = 1,
    .sfxReverb = 2,
};
