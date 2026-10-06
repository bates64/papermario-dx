#include "dgb_06.h"

EntryList Entrances = {
    [dgb_06_ENTRY_0]    { -575.0,    0.0,  175.0,   90.0 },
    [dgb_06_ENTRY_1]    { -150.0,  100.0, -250.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_06 },
    .songVariation = 1,
    .sfxReverb = 2,
};
