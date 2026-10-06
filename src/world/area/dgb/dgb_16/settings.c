#include "dgb_16.h"

EntryList Entrances = {
    [dgb_16_ENTRY_0]    {  450.0,    0.0,  -40.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_16 },
    .songVariation = 1,
    .sfxReverb = 2,
};
