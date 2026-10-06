#include "dgb_05.h"

EntryList Entrances = {
    [dgb_05_ENTRY_0]    {  515.0,    0.0,  310.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
